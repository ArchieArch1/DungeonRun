// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DR_GameInstance.generated.h"

class ADR_GameStateBase;
class UDR_WidgetHUD;

UCLASS()
class DUNGEONRUN_API UDR_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	
	UPROPERTY()
	ADR_GameStateBase* GameStateRef;

	//Pointer to the game hud widget
	//UPROPERTY(VisibleAnywhere, Category = "Widget")
	//UDR_WidgetHUD* GameWidget;
	
	//Exposed class to check the type of widget to display
	//UPROPERTY(EditAnywhere, Category = "Widget")
	//TSubclassOf<UDR_WidgetHUD> GameWidgetClass; 
	
	//UFUNCTION()
	//void CreateWidget();
	
	//UFUNCTION(BlueprintCallable)
	//void UpdateCountDown(float CountDownDuration);
};
