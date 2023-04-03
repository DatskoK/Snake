// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Apple.h"
#include "MySnake.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class SNAKE_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	UPROPERTY(EditAnywhere) class UBoxComponent* MyRootComponent;
	UPROPERTY(EditAnywhere) class USpringArmComponent* CameraSpring;
	UPROPERTY(EditAnywhere) class UCameraComponent* MyCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Pawn)
	class AMySnake* MySnakePlayer;

	UFUNCTION(BlueprintCallable,Category=Pawn)
	void AddSnakeToMap();

	void FMove(float ButtonVal);

	UFUNCTION(BlueprintCallable,Category=Pawn)
	void AddApple();
	
	FVector2D WSAD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Pawn)
	int32 GameMode = 0;

	UFUNCTION(BlueprintCallable,Category=Pawn)
	int32 GetGameMode() const {return GameMode;}

	UFUNCTION(BlueprintCallable,Category=Pawn)
	int32 GetScore();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
