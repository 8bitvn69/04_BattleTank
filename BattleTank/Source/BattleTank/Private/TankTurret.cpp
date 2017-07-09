// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"



void UTankTurret::Rotate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0F, 1.0F);
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	float Rotation = this->RelativeRotation.Yaw + RotationChange;

	this->SetRelativeRotation(FRotator(0.0F, Rotation, 0.0F));
}