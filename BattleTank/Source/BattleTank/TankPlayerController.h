// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:
	ATank* GetControlledTank() const;
	void AimAtCrosshair();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection,FVector& OutHitLocation) const;
	UPROPERTY(EditAnywhere)
		int32 CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
		int32 LineTraceRange = 1000000;
	UPROPERTY(EditAnywhere)
		int32 CrosshairYLocation = 0.333333;
};
