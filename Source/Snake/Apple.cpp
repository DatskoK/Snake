// Fill out your copyright notice in the Description page of Project Settings.


#include "Apple.h"
#include "MySnake.h"
#include "Components/SphereComponent.h"

// Sets default values
AApple::AApple()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyRootComponent = CreateDefaultSubobject<USphereComponent>("RootEat");
	RootComponent = MyRootComponent;
	SnakeEatMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'")).Object;
	class UMaterialInstance* SnakeEatMeshColor = ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/Apple_Inst.Apple_Inst'")).Get();
	FVector Size = FVector(0.8f,0.8f,0.8f);
	class UStaticMeshComponent* EatChank = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Eat"));

	EatChank->SetStaticMesh(SnakeEatMesh);
	EatChank->SetMaterial(0, SnakeEatMeshColor); 
	EatChank->SetRelativeScale3D(Size);
	EatChank->SetRelativeLocation(FVector(0,0,0));
	EatChank->AttachTo(MyRootComponent);
	EatChank->SetCastShadow(false);
	
}

// Called when the game starts or when spawned
void AApple::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AApple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CollectEat();
}

void AApple::CollectEat()
{
	TArray<AActor*> CollectedActors;

	GetOverlappingActors(CollectedActors);

	for(int32 i=0; i<CollectedActors.Num(); i++)
	{
		AMySnake* const Test = Cast<AMySnake>(CollectedActors[i]);
		if (Test)
		{
			Test->VisibleBodyChank++;
			Test->Score++;
			Destroy(true, true);
			AddRandomApple();
			break;
		}
	}
}
void AApple::AddRandomApple()
{
	FRotator StartPointRotation = FRotator (0,0,0);
	float SpawnX = FMath::FRandRange(MinX, MaxX);
	float SpawnY = FMath::FRandRange(MinY, MaxY);

	FVector StartPoint = FVector(SpawnX, SpawnY, SpawnZ);
	GetWorld()-> SpawnActor<AApple>(StartPoint, StartPointRotation);
}