// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DR_GameModeBase.h"
#include "DR_GameStateBase.h"
#include "GameFramework/PlayerController.h"
#include "DR_PlayerController.generated.h"

class ADR_WeaponBase;
class ADR_GameModeBase;
class UDR_GameInstance;
class ADR_Player;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdatePlayerScore);

UCLASS()
class DUNGEONRUN_API ADR_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/// -- Properties -- ///
	UPROPERTY(VisibleAnywhere)
	ADR_Player* CharacterRef;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> PlayerToSpawn = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 PlayerScore = 0;

	UPROPERTY(EditAnywhere)
	UUserWidget* HUDWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDR_WidgetHUD> HUDClass;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FUpdatePlayerScore OnUpdateScore;

	/// -- Functions -- ///
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void ReceivedPlayer() override;

	UFUNCTION()
	void SpawnNewPlayer();

	UFUNCTION()
	void SetPlayerRef();

	UFUNCTION(BlueprintCallable)
	void IncrementPlayerScore();

	UFUNCTION()
	void RequestDefeat(ADR_PlayerController* OtherController);

	UFUNCTION()
	void RequestDestroyCharacter();

	UFUNCTION(BlueprintCallable)
	void ServerResetPlayer(ADR_PlayerController* Controller);

	UFUNCTION(Server, Reliable)
	void MulticastResetPlayer(ADR_PlayerController* Controller);
	
protected:
	/// -- Vars -- ///
	UPROPERTY(BlueprintReadOnly)
	ADR_GameStateBase* GameStateRef;

	UPROPERTY(BlueprintReadOnly)
	ADR_GameModeBase* GameModeRef;

	//Base lookup rate - deg/sec. Other scaling may affect the final lookup rate.
	UPROPERTY(EditAnywhere, Category = "Look")
	float BaseLookUpRate = 90.0f;

	//Base lookright rate - deg/sec. Other scaling may affect the final lookup rate.
	UPROPERTY(EditAnywhere, Category = "Look")
	float BaseLookRightRate = 90.0f;

	UPROPERTY(EditAnywhere, Category = "Look")
	float BaseRotationSpeed = 100.0f;
	
	//ToDo - Sound jump cue to be declared here
	
	/// -- Functions -- ///
	void SetupInputComponent() override;
	
	void RequestMoveForward(float AxisValue);
	void RequestMoveRight(float AxisValue);
	void RequestLookUp();
	void RequestLookRight();
	void RequestAttack();
	void RequestPickupWeapon();

	UFUNCTION(Server, Reliable)
	void ServerPlayerDefeated(ADR_PlayerController* OtherController);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastPlayerDefeated(ADR_PlayerController* OtherController);
};
