// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DR_GameModeBase.generated.h"

class ADR_GameStateBase;
class UDR_GameInstance;
class UDR_WidgetHUD;
class ADR_PlayerController;

UCLASS()
class DUNGEONRUN_API ADR_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumExpectedPlayers;

	UPROPERTY()
	ADR_GameStateBase* GameStateRef;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void ReceivePlayer(APlayerController* PlayerController);

	UFUNCTION()
	void SetNumExpectedPlayers(int expectedPlayers);

	UFUNCTION(Server, Reliable)
	void ServerRequestResetPlayer(ADR_PlayerController* Controller);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastResetPlayer(ADR_PlayerController* Controller);
	
};
