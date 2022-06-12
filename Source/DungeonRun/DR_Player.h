// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DR_WeaponMelee.h"
#include "GameFramework/Character.h"
#include "DR_Player.generated.h"

class ADR_GameStateBase;
class ADR_PlayerController;

UCLASS()
class DUNGEONRUN_API ADR_Player : public ACharacter
{
	GENERATED_BODY()

public:
	/// -- Properties -- //
	ADR_PlayerController* PlayerControllerRef;
    ADR_GameStateBase* GameStateRef;
	
	UPROPERTY(BlueprintReadWrite)
	bool bIsSwinging = false;

	//UPROPERTY(BlueprintReadWrite)
	//bool bHasWeapon = false;

	UPROPERTY(EditAnywhere)
	int PlayerScore = 0;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* DefeatMontage;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	ADR_WeaponBase* AvailableWeapon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	ADR_WeaponBase* EquippedWeapon = nullptr;

	USkeletalMeshComponent* SkeletalMesh;
	FName WeaponSocketName = TEXT("handSlotRightSocket");

	/// --- Functions --- ///
	// Sets default values for this character's properties
	ADR_Player();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void Defeat(ADR_PlayerController* OtherController);

	//A Server function is called on the client but executed om the server/
	UFUNCTION(Server, Reliable)
	void ServerRequestDefeat();

	//A NetMulticast function is called from the server and executed on the server, as well as all connected clients.
	UFUNCTION(NetMulticast, Reliable)
	void MulticastDefeat();

	UFUNCTION(Server, Reliable)
	void ServerRequestAttack();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRequestAttack();

	UFUNCTION()
	void PlayMeleeAttackMontage();

	UFUNCTION()
	void EquipWeapon();
	
	UFUNCTION(Server, Reliable)
	void ServerRequestEquipWeapon();
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRequestEquipWeapon();

	UFUNCTION()
	void UnEquipWeapon();

	UFUNCTION(Server, Reliable)
	void ServerRequestUnequipWeapon();
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRequestUnequipWeapon();
	
	UFUNCTION()
	void SetAvailableWeapon(ADR_WeaponBase* Weapon);

	UFUNCTION()
	void ClearAvailableWeapon();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
