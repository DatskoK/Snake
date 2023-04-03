// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySnake.generated.h"

UCLASS()
class SNAKE_API AMySnake : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySnake();
	
	int32 SnakeSize = 150;
	float StepSnake = 70.f;
	
	UPROPERTY(EditAnywhere)
	UStaticMesh* SnakeBodyMesh;
	
	TArray<UStaticMeshComponent*> SnakeBody;
	class USphereComponent* MyRootComponent;
	void CreateSnakeBody();
	UPROPERTY(EditAnywhere)
	int32 VisibleBodyChank = 5;
	void SetVisibleChank();
	UPROPERTY(EditAnywhere)
	FVector2D DirectionMoveSnake ;
	void MoveSnake();
	float StepDeley = 0.2f;
	float BuferTime = 0;
	int32 Score = 0;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
