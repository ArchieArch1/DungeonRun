// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DR_WeaponBase.generated.h"

class ADR_Player;
class UBoxComponent;

//Base class for the weapons.
UCLASS()
class DUNGEONRUN_API ADR_WeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ADR_WeaponBase();
	
	virtual void Tick(float DeltaTime) override;

	void SetEquipped(ADR_Player* Player);
	void SetUnEquipped();

	//Use weapon base function,the child classes decide what this means.
	UFUNCTION()
	virtual void UseWeapon();
	
	virtual void ActivateMeleeCollision();
	
	virtual void DeactivateMeleeCollision();

protected:
	//Reference to the player (currently the first found player)
	UPROPERTY(BlueprintReadOnly)
	ADR_Player* PlayerRef;

	UPROPERTY(EditAnywhere, Category = "Weapon Interact")
	UBoxComponent* InteractBox;
	
	UPROPERTY(EditAnywhere, Category = "Weapon")
	bool bIsEquipped = false;

	//Used to detect if the weapon is available for pickup. Used to prevent AvailableWeapon pointer from constantly being assigned.
	UPROPERTY(EditAnywhere, Category = "Weapon")
	bool bCanBeEquipped = false;
	
	/* //The mesh of the weapon, mesh applied in SetupWeapon.
	*  UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	*  UStaticMeshComponent* WeaponMesh; */

	virtual void BeginPlay() override;

	//Interaction overlaps (could of used an interaction component instead)
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	//vars - anim, cooldown, bstopmovement
};
