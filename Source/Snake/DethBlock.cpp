// Fill out your copyright notice in the Description page of Project Settings.

#include "MySnake.h"
#include "DethBlock.h"
#include "Components/BoxComponent.h"

// Sets default values
ADethBlock::ADethBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	class UStaticMesh* WallMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;
	WallColor = ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/Block_Inst.Block_Inst'")).Get();

	class UStaticMeshComponent* WallChank;

	WallChank = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL"));
	WallChank->SetStaticMesh(WallMesh);
	WallChank->SetRelativeLocation(FVector(0,0,0));
	WallChank->SetMaterial(0, WallColor);
	WallChank->SetCastShadow(false);
	
}

// Called when the game starts or when spawned
void ADethBlock::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADethBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CollideWall();
}

void ADethBlock::CollideWall()
{
	TArray<AActor*> CollectedActors;
	GetOverlappingActors(CollectedActors);

	for (int32 i=0; i < CollectedActors.Num(); i++)
	{
		CollectedActors[i]->Destroy(true,true);
	}
}


