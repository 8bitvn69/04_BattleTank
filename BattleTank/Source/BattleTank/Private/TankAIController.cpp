// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h" // So we can implement OnDeath
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

}

void ATankAIController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);

	if (InPawn) {
		ATank* PossessedTank = Cast<ATank>(InPawn);

		if (!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddDynamic(this, &ATankAIController::OnPossedTankDeath); // Can use AddUniqueDynamic instead
	}
}

void ATankAIController::OnPossedTankDeath() {
	if (!(GetPawn())) { return; }

	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	APawn* ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) {
		return;
	}

	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm

	UTankAimingComponent* AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	// Aim towards the player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::Locked) {
		AimingComponent->Fire(); // TODO limit firing rate
	}
}
