// Fill out your copyright notice in the Description page of Project Settings.

#include "DR_GameStateBase.h"
#include "DR_Player.h"
#include "DR_PlayerController.h"
#include "DR_PlayerState.h"
#include "DR_WidgetHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

class ADR_PlayerState;

ADR_GameStateBase::ADR_GameStateBase()
{
	bReplicates = true;
}

void ADR_GameStateBase::BeginPlay()
{
	Super::BeginPlay();

	GameModeRef = Cast<ADR_GameModeBase>(GetWorld()->GetAuthGameMode());
	
	//Find each player controller in the game and add to the PlayerControllers array.

	/*for(FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		//Get the next found iterator
		APlayerController* PlayerController = Iterator->Get();

		//If valid
		if(PlayerController)
		{
			//Create a new HUD widget for the found player controller
			if(UDR_WidgetHUD* HUDWidget = CreateWidget<UDR_WidgetHUD>(PlayerController, HUDWidgetClass))
			{
				//Add the found player controller and its HUD widget to the TMap.
				HUDWidget->AddToViewport();
				PlayerControllers.Add(PlayerController, HUDWidget);	
			}
		}
	}*/

	for(FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		//Get the next found iterator
		APlayerController* PlayerController = Iterator->Get();

		//If valid
		if(PlayerController)
		{
			PlayerControllers.Add(PlayerController);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(StartCountdownTimerHandle, this, &ADR_GameStateBase::ServerRequestStartCountdownTick, 1, true);
	
	UE_LOG(LogTemp, Warning, TEXT("ADR_GameStateBase::BeginPlay"));
}

void ADR_GameStateBase::AttemptStartGame()
{

	//if(GameModeRef->NumExpectedPlayers == GameModeRef->GetNumPlayers())
	//{
		//Begin countdown
	    //GetWorld()->GetTimerManager().SetTimer(StartCountdownTimerHandle, this, &ADR_GameStateBase::ServerRequestStartCountdownTick, 1, true);	
	//}
	
}

void ADR_GameStateBase::IncrementPlayerScore_Implementation(ADR_PlayerController* Controller)
{
	ADR_PlayerState* PlayerState = Controller->GetPlayerState<ADR_PlayerState>();
	PlayerState->PlayerScore++;
	
	//UI stuff
}

void ADR_GameStateBase::AttemptRestartPlayer(ADR_PlayerController* Controller)
{
	//Find the controller
	/*for(int32 i = 0; i <= PlayerControllers.Num() - 1; i++)
	{
		APlayerController* Controller = PlayerControllers[i];

		//If the controller has been found, pass it into ResetPlayer
		if(ControllerID == UGameplayStatics::GetPlayerControllerID(Controller))
		{
			Cast<ADR_PlayerController>(PlayerControllers[i]);
			ServerResetPlayer_Implementation(Cast<ADR_PlayerController>(PlayerControllers[i]));
		}
	}*/

	ServerResetPlayer(Controller);
}

void ADR_GameStateBase::ServerResetPlayer_Implementation(ADR_PlayerController* Controller)
{
	//MulticastResetPlayer(Controller);
	FVector SpawnLocation = FVector(0.f, 0.f, 10.f);
	FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);
	GetWorld()->SpawnActor<ADR_Player>(PlayerToSpawn, SpawnLocation, SpawnRotation);
}

void ADR_GameStateBase::MulticastResetPlayer_Implementation(ADR_PlayerController* Controller)
{
	//Spawn a new player and make the player controller possess it
}

EGameState ADR_GameStateBase::GetCurrentGameState()
{
	return CurrentGameState;
}

void ADR_GameStateBase::ServerRequestStartCountdownTick_Implementation()
{
	MulticastStartCountdownTick();
}

void ADR_GameStateBase::MulticastStartCountdownTick_Implementation()
{
	//Each second, reduce StartCountdownDuration
	StartCountdownDuration--;
	FOnUpdateStartTimerWidget.Broadcast();

	//Call update start timer on each player controller HUD
	//for(int32 i = 0; i <= PlayerControllers.Num(); ++i)
	//{
	//	Cast<ADR_PlayerController>(PlayerControllers[i]);
	//}

	if(StartCountdownDuration <= 0)
	{
		ServerRequestStartGame();
		GetWorldTimerManager().ClearTimer(StartCountdownTimerHandle);
	}
}

void ADR_GameStateBase::ServerRequestStartGame_Implementation()
{
	MulticastStartGame();
}

void ADR_GameStateBase::MulticastStartGame_Implementation()
{
	CurrentGameState = EGameState::Playing;
	GetWorld()->GetTimerManager().SetTimer(RoundCountdownTimerHandle, this, &ADR_GameStateBase::ServerRequestRoundCountdown, 1, true);
}

void ADR_GameStateBase::ServerRequestRoundCountdown_Implementation()
{
	MulticastRoundCountdown();
}

void ADR_GameStateBase::MulticastRoundCountdown_Implementation()
{
	RemainingRoundTime--;
	FOnUpdateRoundTimerWidget.Broadcast();

	if(RemainingRoundTime <= 0)
	{
		GetWorldTimerManager().ClearTimer(RoundCountdownTimerHandle);
		ServerRequestGameover();
	}
}

void ADR_GameStateBase::ServerRequestGameover_Implementation()
{
	MulticastGameOver();
}

void ADR_GameStateBase::MulticastGameOver_Implementation()
{
	//Todo - Gameover & widget anims!
	CurrentGameState = EGameState::GameOver;
}

void ADR_GameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADR_GameStateBase, CurrentGameState);
	DOREPLIFETIME(ADR_GameStateBase, StartCountdownDuration);
	DOREPLIFETIME(ADR_GameStateBase, RemainingRoundTime);
}
