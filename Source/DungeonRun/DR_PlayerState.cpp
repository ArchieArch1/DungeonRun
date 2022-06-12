// Fill out your copyright notice in the Description page of Project Settings.


#include "DR_PlayerState.h"
#include "Net/UnrealNetwork.h"

ADR_PlayerState::ADR_PlayerState()
{
	
}

void ADR_PlayerState::OnRep_UpdateScore()
{
	PlayerScore++;
}

int ADR_PlayerState::UpdateScore()
{
	return ++PlayerScore;
}


void ADR_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADR_PlayerState, PlayerScore);
}
