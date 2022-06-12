// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DR_GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "DR_WidgetHUD.generated.h"

class ADR_PlayerController;

UCLASS()
class DUNGEONRUN_API UDR_WidgetHUD : public UUserWidget
{
	GENERATED_BODY()
public:

	UDR_WidgetHUD(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY()
	ADR_GameModeBase* GameModeRef;

	UFUNCTION()
	void TestFunction();
	
	UFUNCTION(BlueprintNativeEvent)
	void UpdateCountdown(int Time);
};
