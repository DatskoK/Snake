// Fill out your copyright notice in the Description page of Project Settings.

#include "Apple.h"
#include "MySnake.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"

// Sets default values
AMySnake::AMySnake()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyRootComponent = CreateDefaultSubobject<USphereComponent>("MyRoot");
	RootComponent = MyRootComponent;
	FVector Location = GetActorLocation();
	MyRootComponent->SetRelativeLocation(Location);
	CreateSnakeBody();
	
}

// Called when the game starts or when spawned
void AMySnake::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMySnake::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetVisibleChank();
	BuferTime += DeltaTime;
	if(BuferTime > StepDeley)
	{
		MoveSnake();
		if(Score>=3)
		{
			StepDeley = 0.01f;
		}
		BuferTime=0;
	}
}

void AMySnake::CreateSnakeBody()
{
	class UStaticMesh* SnakeChankMesh;
	SnakeChankMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'")).Object;
	class UMaterialInstance* BodyColor;
	BodyColor = ConstructorHelpers::FObjectFinder<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/Body_Inst.Body_Inst'")).Object;
	class UMaterialInstance* HeadColor;
	HeadColor = ConstructorHelpers::FObjectFinder<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/Head_Inst.Head_Inst'")).Object;
	FVector NextPoint = GetActorLocation();
	FName NameChank;
	FString TheString;
	for(int32 i=0; i < SnakeSize; i++)
	{
		TheString = "Chanks" + FString::FromInt(i);
		NameChank = FName(*TheString);
		UStaticMeshComponent* BodyChank = CreateDefaultSubobject<UStaticMeshComponent>(NameChank);
		BodyChank->SetStaticMesh(SnakeChankMesh);
		BodyChank->SetRelativeLocation(NextPoint);
		SnakeBody.Add(BodyChank);
		NextPoint.X-=StepSnake;
		BodyChank->AttachTo(MyRootComponent);
		BodyChank->SetMaterial(0,BodyColor);
		BodyChank->SetCastShadow(false);
		if(i==0)
		{
			BodyChank->SetMaterial(0,HeadColor);
			BodyChank->SetWorldScale3D(FVector(1.1,1.1,1.1));
		}
		else
		{
			BodyChank->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
	SetVisibleChank();
}
void AMySnake::SetVisibleChank()
{
	for(int32 IndexShow = 0; IndexShow<SnakeBody.Num(); IndexShow++)
	{
		if(IndexShow<VisibleBodyChank)
		{
			SnakeBody[IndexShow]->SetVisibility(true, true);
		}
		else
		{
			SnakeBody[IndexShow]->SetVisibility(false, true);
		}
	}
}
void AMySnake::MoveSnake()
{
	if((DirectionMoveSnake.X != 0)||(DirectionMoveSnake.Y != 0))
	{
		for (int Chank = SnakeBody.Num()-1; Chank>0; Chank--)
		{
			FVector V = SnakeBody [Chank-1]->GetRelativeLocation();
			SnakeBody[Chank]->SetRelativeLocation(V);
		}
		FVector StartPoint = SnakeBody[0] -> GetRelativeLocation();
		if (DirectionMoveSnake.X>0) StartPoint.X -= StepSnake;
		if (DirectionMoveSnake.X<0) StartPoint.X += StepSnake;

		if(DirectionMoveSnake.Y>0) StartPoint.Y += StepSnake;
		if(DirectionMoveSnake.Y<0) StartPoint.Y -= StepSnake;

		SnakeBody[0]->SetRelativeLocation(StartPoint);
		for(int Chank = 1; Chank < SnakeBody.Num(); Chank++)
		{
			if(SnakeBody[Chank]->IsVisible())
			{
				if(SnakeBody[0]->GetComponentLocation().Equals(SnakeBody[Chank]->GetComponentLocation(), 0.1f))
				{
					Destroy();
					
					break;
				}
			}
		}
	}
}


