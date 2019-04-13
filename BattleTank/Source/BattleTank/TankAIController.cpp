// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	
	
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank) {
		MoveToActor(PlayerTank, AcceptanceRadius);
		auto TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		if (!ensure(TankAimingComponent)) { return; }
		TankAimingComponent->AimAt(PlayerTank->GetTransform().GetLocation());
		ControlledTank->Fire(); // TODO limit firing rate

	}
}