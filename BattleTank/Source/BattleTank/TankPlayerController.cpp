// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("PlayerController Tank not Possessed"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Tank Possessed : %s"),*ControlledTank->GetName());
	}
}
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshair();
	
}
ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		GetControlledTank()->AimAt(HitLocation);
	}
}
 
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector LookDirection, HitLocation;
	FVector2D ScreenLocation = FVector2D(CrosshairXLocation * ViewportSizeX,CrosshairYLocation * ViewportSizeY);
	GetLookDirection(ScreenLocation, LookDirection);
	if (GetLookVectorHitLocation(LookDirection, HitLocation)) {
		OutHitLocation = HitLocation;
		return true;
	}
	else {
		return false;
	}
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		OutLookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		(StartLocation + LookDirection * LineTraceRange),
		ECollisionChannel::ECC_Visibility)) 
	{	
		OutHitLocation = HitResult.Location;
		return true;
	}
	else {
		return false;
	}
}
