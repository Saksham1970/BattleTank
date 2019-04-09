// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	ATank* ControlledTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("AIController Tank not Possessed"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController Tank Enemy : %s"), *PlayerTank->GetName());
	}
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetControlledTank()->AimAt(GetPlayerTank()->GetTransform().GetLocation());
}
ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerTank) {
		return Cast<ATank>(PlayerTank);
	}
	else {
		return nullptr;
	}
}
