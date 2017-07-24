// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BP BeginPlay to run!

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) {
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("DamageAmount: %f | DamageToApply: %d | CurrentHealth: %d"), DamageAmount, DamageToApply, CurrentHealth)

	if (CurrentHealth <= 0) {
		OnDeath.Broadcast();
	}
	
	DamageToApply = FPlatformMath::RoundToFloat(DamageToApply);
	return DamageToApply;
}

float ATank::GetHealthPercent() const {
	return (float)CurrentHealth / StartingHealth;
}