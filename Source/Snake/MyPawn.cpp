// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "MySnake.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyRootComponent = CreateDefaultSubobject<UBoxComponent>("RootModel");
	RootComponent = MyRootComponent;

	CameraSpring = CreateDefaultSubobject<USpringArmComponent>("Spring");
	CameraSpring->SetRelativeLocation(FVector(0,0,0));
	CameraSpring->AttachTo(MyRootComponent);

	MyCamera=CreateDefaultSubobject<UCameraComponent>("Camera");
	MyCamera->AttachTo(CameraSpring, USpringArmComponent::SocketName);

	CameraSpring->SetRelativeRotation(FRotator(-90.f, 0,0));
	CameraSpring->TargetArmLength = 2700.f;
	CameraSpring->bDoCollisionTest = false;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{

}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("KeyMapMove", this, &AMyPawn::FMove);
	
}

void AMyPawn::AddSnakeToMap()
{
	FVector StartPoint = GetActorLocation();
	FRotator StartPointRotator = GetActorRotation();

	if(GetWorld())
	{
		MySnakePlayer=GetWorld()->SpawnActor<AMySnake>(StartPoint, StartPointRotator);
		GameMode = 1;
	}
}

void AMyPawn::FMove(float ButtonVal)
{
	int32 Key = ButtonVal;
		switch (Key)
		{
		case 1:
			if(WSAD.X != 1)
			{
				WSAD = FVector2D(0,0);
				WSAD.X = -1;
			}
			break;
		case 2:
			if(WSAD.X != -1)
			{
				WSAD = FVector2D(0,0);
				WSAD.X = 1;
			}
			break;
		case 3:
			if(WSAD.Y != -1)
			{
				WSAD = FVector2D(0,0);
				WSAD.Y = 1;
			}
			break;
		case 4:
			if(WSAD.Y != 1)
			{
				WSAD = FVector2D(0,0);
				WSAD.Y = -1;
			}
			break;
		}
		if(MySnakePlayer)
		{
			MySnakePlayer->DirectionMoveSnake = WSAD;
		}
}
 void AMyPawn::AddApple()
 {
	AApple* NewApple = GetWorld()->SpawnActor<AApple>();
	NewApple->AddRandomApple();
 }

int32 AMyPawn::GetScore()
{
	if (MySnakePlayer)
	{
		return MySnakePlayer->Score;
	}
	return 0;
}



