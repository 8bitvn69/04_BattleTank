// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	// How close can the AI tank get
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 8000.0F;

private:
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION() // Must have this !!!
	void OnPossedTankDeath();

};
