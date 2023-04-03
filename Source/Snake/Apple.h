// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Apple.generated.h"

UCLASS()
class SNAKE_API AApple : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AApple();

	class USphereComponent* MyRootComponent;

	class UStaticMesh* SnakeEatMesh;

	void CollectEat();

	void AddRandomApple();

	float MinY = -1550.f;
	float MaxY = 1550.f;
	float MinX = -1200.f;
	float MaxX = 1200.f;
	float SpawnZ = 70.f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
