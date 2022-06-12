// Fill out your copyright notice in the Description page of Project Settings.


#include "DR_GameInstance.h"
#include "DR_PlayerController.h"
#include "DR_WidgetHUD.h"
#include "Blueprint/UserWidget.h"

class ADR_PlayerController;

/*void UDR_GameInstance::CreateWidget()
{
	if(GetWorld())
	{
		//GameWidget = CreateWidget<UDR_WidgetHUD>(this, GameWidgetClass);
		if(GameWidget)
		{
			GameWidget->AddToPlayerScreen();
		}
	}
}

void UDR_GameInstance::UpdateCountDown(float CountDownDuration)
{
	if(GameWidget)
	{
		if(ADR_PlayerController* PlayerController = Cast<ADR_PlayerController>(GameWidget->GetOwningPlayer()))
		{
			//Somehow get the gamestate, pass in the timer value
			//GameWidget->UpdateCountdown();
		}
	}
}*/
