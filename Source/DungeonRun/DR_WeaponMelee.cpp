// Fill out your copyright notice in the Description page of Project Settings.


#include "DR_WeaponMelee.h"
#include "DR_Player.h"
#include "Components/BoxComponent.h"

ADR_WeaponMelee::ADR_WeaponMelee()
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(InteractBox);
	
	MeleeCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MeleeCollision"));
	MeleeCollision->SetupAttachment(WeaponMesh);
	MeleeCollision->SetCollisionProfileName("NoCollision");
}

void ADR_WeaponMelee::BeginPlay()
{
	Super::BeginPlay();
}

//UseWeapon in the melee class will execute the swing, so the weapon derived classes need to Super() to this one
//This function starts the melee attack anim and broadcasts it to the clients, the anim notify class handles the collision profile
void ADR_WeaponMelee::UseWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("ADR_WeaponMelee::UseWeapon"));
	PlayerRef->PlayMeleeAttackMontage();
	PlayerRef->ServerRequestAttack(); 
}

//Called when attack starts
void ADR_WeaponMelee::ActivateMeleeCollision()
{
	MeleeCollision->SetCollisionProfileName("OverlapAll");
	UE_LOG(LogTemp, Warning, TEXT("ADR_WeaponMelee::ActivateMeleeCollision"));
}

//Called when attack ends
void ADR_WeaponMelee::DeactivateMeleeCollision()
{
	MeleeCollision->SetCollisionProfileName("NoCollision");
	UE_LOG(LogTemp, Warning, TEXT("ADR_WeaponMelee::DeactivateMeleeCollision"));
}

