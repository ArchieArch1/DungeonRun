// Fill out your copyright notice in the Description page of Project Settings.

#include "DR_WidgetHUD.h"

UDR_WidgetHUD::UDR_WidgetHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("UDR_WidgetHUD Default constructor"));
}

//Override in blueprint
void UDR_WidgetHUD::UpdateCountdown_Implementation(int Time)
{
	UE_LOG(LogTemp, Warning, TEXT("TESTESTEST"));
}

void UDR_WidgetHUD::TestFunction()
{
	
}


