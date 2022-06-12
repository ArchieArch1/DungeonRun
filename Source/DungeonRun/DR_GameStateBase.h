// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Blueprint/UserWidget.h"
#include "DR_GameStateBase.generated.h"

class ADR_GameModeBase;
class UDR_WidgetHUD;
class ADR_PlayerController;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartTimerWidgetDisplay);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameTimerWidgetDisplay);

UENUM(BlueprintType)
enum class EGameState : uint8
{
	NONE UMETA(DisplayName = "NONE"),
	Waiting UMETA(DisplayName = "Waiting"),
	Playing UMETA(DisplayName = "Playing"),
	Paused UMETA(DisplayName = "Paused"),
	GameOver UMETA(DisplayName = "GameOver")
};

UCLASS()
class DUNGEONRUN_API ADR_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	/// -- Properties -- ///
	
	UPROPERTY()
	ADR_GameModeBase* GameModeRef;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> PlayerToSpawn;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "States", meta = (AllowPrivateAccess = "true"), Replicated)
	EGameState CurrentGameState = EGameState::NONE;

	//UPROPERTY(BlueprintReadOnly, Category = "GameDetails")
	//TMap<APlayerController*, UDR_WidgetHUD*> PlayerControllers;

	UPROPERTY(BlueprintReadOnly, Category = "GameDetails")
	TArray<APlayerController*> PlayerControllers;

	//UPROPERTY(EditAnywhere)
	//TSubclassOf<UDR_WidgetHUD> HUDWidgetClass;
	
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "GameDetails")
	int RemainingRoundTime = 60;

	UPROPERTY(Replicated, BlueprintReadOnly)
	int StartCountdownDuration = 4;

	UPROPERTY(Replicated, BlueprintReadOnly)
	int PlayerOneScore = 0;

	UPROPERTY(Replicated, BlueprintReadOnly)
	int PlayerTwoScore = 0;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FStartTimerWidgetDisplay FOnUpdateStartTimerWidget;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FGameTimerWidgetDisplay FOnUpdateRoundTimerWidget;

	/// -- Functions -- ///
	ADR_GameStateBase();

	UFUNCTION()
	void AttemptStartGame();

	UFUNCTION()
	void AttemptRestartPlayer(ADR_PlayerController* Controller);

	UFUNCTION(Server, Reliable)
	void ServerResetPlayer(ADR_PlayerController* Controller);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastResetPlayer(ADR_PlayerController* Controller);
	
	UFUNCTION()
	EGameState GetCurrentGameState();

private:
	/// -- Properties -- ///
	FTimerHandle StartCountdownTimerHandle;
	FTimerHandle RoundCountdownTimerHandle;

	/// -- Functions -- ///
	void BeginPlay() override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void IncrementPlayerScore(ADR_PlayerController* Controller);
	
	UFUNCTION(Server, Reliable)
	void ServerRequestStartCountdownTick();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastStartCountdownTick();

	UFUNCTION(Server, Reliable)
	void ServerRequestStartGame();

	UFUNCTION(Server, Reliable)
	void MulticastStartGame();

	UFUNCTION(Server, Reliable)
	void ServerRequestRoundCountdown();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRoundCountdown();

	UFUNCTION(Server, Reliable)
	void ServerRequestGameover();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastGameOver();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
