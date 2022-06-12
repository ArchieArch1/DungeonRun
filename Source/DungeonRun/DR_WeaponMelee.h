// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DR_WeaponBase.h"
#include "Components/CapsuleComponent.h"
#include "DR_WeaponMelee.generated.h"

class ADR_WeaponAxe;

UCLASS()
class DUNGEONRUN_API ADR_WeaponMelee : public ADR_WeaponBase
{
	GENERATED_BODY()

public:
	
	//Can't get this to work in ADR_WeaponMelee
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UCapsuleComponent* MeleeCollision;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	UStaticMeshComponent* WeaponMesh;
	
	ADR_WeaponMelee();

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void ActivateMeleeCollision() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void DeactivateMeleeCollision() override;
	
	void UseWeapon() override;
};
