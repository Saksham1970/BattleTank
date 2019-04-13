// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"
class UTankTrack;
/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), ClassGroup = (Tank))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Movement Component")
	void IntendMoveForward(float Throw);
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);
private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
