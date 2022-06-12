// Fill out your copyright notice in the Description page of Project Settings.


#include "DR_Player.h"
#include "Engine.h"
#include "DR_PlayerController.h"

// Sets default values
ADR_Player::ADR_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

// Called when the game starts or when spawned
void ADR_Player::BeginPlay()
{
	Super::BeginPlay();
	SetReplicateMovement(true);
	
	if(IsLocallyControlled())
	{
		GameStateRef = Cast<ADR_GameStateBase>(GetWorld()->GetGameState());
	}
	
	PlayerControllerRef = Cast<ADR_PlayerController>(GetController());

	SkeletalMesh = GetMesh();
}

// Called every frame
void ADR_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADR_Player::Defeat(ADR_PlayerController* OtherController)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Orange, __FUNCTION__);
	
	PlayerControllerRef->ServerRestartPlayer();
}

void ADR_Player::ServerRequestDefeat_Implementation()
{
	MulticastDefeat();
}

void ADR_Player::MulticastDefeat_Implementation()
{
	Destroy();
	GetWorld()->GetAuthGameMode()->RestartPlayer(PlayerControllerRef);
	PlayerControllerRef->SetPlayerRef();
}

void ADR_Player::ServerRequestAttack_Implementation()
{
	//Server needs to call the multicast so it can be broadcasted to each client machine
	MulticastRequestAttack();
}

void ADR_Player::MulticastRequestAttack_Implementation()
{
	//Locally controlled machine has already played the montage so ignore
	if(IsLocallyControlled()){ return; }

	PlayAnimMontage(AttackMontage);
}

void ADR_Player::PlayMeleeAttackMontage()
{
	//Play first on local machine for responsive feel
	if(IsLocallyControlled())
	{
		PlayAnimMontage(AttackMontage);
	}
}

//Temp reference for an available weapon to pickup. Not sure what happens if you leave immediately into another weapon range
void ADR_Player::SetAvailableWeapon(ADR_WeaponBase* Weapon)
{
	//If available weapon isn't currently set (prevent pointer from being constantly set)...
	if(AvailableWeapon)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Orange, __FUNCTION__);
		UE_LOG(LogTemp, Warning, TEXT("Weapon already set"));
	}

	//...and the player doesn not currently have a weapon
	else if(EquippedWeapon == nullptr)
	{
		AvailableWeapon = Weapon;
		GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Orange, __FUNCTION__);
		UE_LOG(LogTemp, Warning, TEXT("Available Weapon reference set"));
	}

	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Orange, __FUNCTION__);
	}
}

void ADR_Player::ClearAvailableWeapon()
{
	AvailableWeapon = nullptr;
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Orange, __FUNCTION__);
}

void ADR_Player::EquipWeapon()
{
	if(AvailableWeapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon is available"));
		AvailableWeapon->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocketName);
		//bHasWeapon = true;
		AvailableWeapon->SetEquipped(this);
		EquippedWeapon = AvailableWeapon;
		AvailableWeapon = nullptr;
		ServerRequestEquipWeapon();
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No weapon found"));
	}
}

void ADR_Player::ServerRequestEquipWeapon_Implementation()
{
	MulticastRequestEquipWeapon();
}

void ADR_Player::MulticastRequestEquipWeapon_Implementation()
{
	if(IsLocallyControlled()) { return; }

	if(AvailableWeapon)
	{
		AvailableWeapon->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocketName);
		//bHasWeapon = true;
		AvailableWeapon->SetEquipped(this);
		EquippedWeapon = AvailableWeapon;
		AvailableWeapon = nullptr;	
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Weapon not avaialble - ADR_Player::MulticastRequestEquipWeapon_Implementation()"));
	}
}

void ADR_Player::UnEquipWeapon()
{
	EquippedWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	EquippedWeapon->SetUnEquipped();
	//EquippedWeapon = nullptr;
	//bHasWeapon = false;
	ServerRequestUnequipWeapon();
}

void ADR_Player::ServerRequestUnequipWeapon_Implementation()
{
	MulticastRequestUnequipWeapon();
}

void ADR_Player::MulticastRequestUnequipWeapon_Implementation()
{
	EquippedWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	EquippedWeapon->SetUnEquipped();
	EquippedWeapon = nullptr;
	//bHasWeapon = false;
}




