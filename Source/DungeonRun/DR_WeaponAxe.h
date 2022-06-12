// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DR_WeaponMelee.h"
#include "DR_WeaponAxe.generated.h"

UCLASS()
class DUNGEONRUN_API ADR_WeaponAxe : public ADR_WeaponMelee
{
	GENERATED_BODY()

public:
	ADR_WeaponAxe();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStats")
	float SwingDamage = 100.f;

	//Swing cooldown timer
	UPROPERTY(BlueprintReadWrite, Category = "WeaponStats")
	float SwingCoolDownTimer = 1.f;

	//Swing cooldown speed
	UPROPERTY(BlueprintReadWrite, Category = "WeaponStats")
	float SwingCoolDownSpeed = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStats")
	float SwingSpeedMultiplier = .5f;

	UFUNCTION()
	virtual void BeginPlay() override;
	
	void UseWeapon() override;
};
