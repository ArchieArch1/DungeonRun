// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DR_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONRUN_API ADR_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(ReplicatedUsing = OnRep_UpdateScore)
	int32 PlayerScore = 0;
	
	ADR_PlayerState();

	UFUNCTION(BlueprintCallable)
	int32 UpdateScore();

	UFUNCTION()
	void OnRep_UpdateScore();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
