// Fill out your copyright notice in the Description page of Project Settings.

#include "DR_GameModeBase.h"
#include "DR_Player.h"
#include "DR_PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ADR_GameModeBase::BeginPlay()
{
	//Setup
	Super::BeginPlay();
	GameStateRef = Cast<ADR_GameStateBase>(GetWorld()->GetGameState());
}

void ADR_GameModeBase::ReceivePlayer(APlayerController* PlayerController)
{
	GameStateRef->AttemptStartGame();
}

void ADR_GameModeBase::SetNumExpectedPlayers(int expectedPlayers)
{
	NumExpectedPlayers = expectedPlayers;
}

void ADR_GameModeBase::ServerRequestResetPlayer_Implementation(ADR_PlayerController* Controller)
{
	MulticastResetPlayer(Controller);
}

void ADR_GameModeBase::MulticastResetPlayer_Implementation(ADR_PlayerController* Controller)
{
	if(Controller)
	{
		FActorSpawnParameters SpawnParams;
		Controller->Possess(GetWorld()->SpawnActor<ADR_Player>(SpawnParams));
	}
}