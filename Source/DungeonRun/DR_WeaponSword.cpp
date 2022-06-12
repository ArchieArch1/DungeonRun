// Fill out your copyright notice in the Description page of Project Settings.


#include "DR_WeaponSword.h"

#include "DR_Player.h"

ADR_WeaponSword::ADR_WeaponSword()
{
	
}

void ADR_WeaponSword::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Sword BeginPlay"));
}

//Add axe swing functionality - UseWeapon on ADR_WeaponMelee is called from Super::UseWeapon();
void ADR_WeaponSword::UseWeapon()
{
	Super::UseWeapon();

	//This could be done somewhere else so it doesn't need to be set everytime the player uses weapon
	//Constructor?? Seems risky...
	PlayerRef->AttackMontage->RateScale = SwingSpeedMultiplier;
}