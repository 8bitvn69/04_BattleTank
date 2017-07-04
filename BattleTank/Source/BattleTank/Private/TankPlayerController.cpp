// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto* ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()))
	}

}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("Player controller ticking"))
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) {
		return;
	}

	FVector HitLocation; // Out Parameter
	if (bGetSightRayHitLocation(HitLocation)) { // Has "side-effect", is going to line trace
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *(HitLocation.ToString()))
		// TODO Tell controlled tank to aim at this point
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::bGetSightRayHitLocation(FVector& OutHitLocation) const {
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (bGetLookDirection(ScreenLocation, LookDirection)) {
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *(LookDirection.ToString()))
		bGetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return true;
}

bool ATankPlayerController::bGetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	)) {
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0.0F);
	return false; // Line-trace didn't succeed
}

bool ATankPlayerController::bGetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}