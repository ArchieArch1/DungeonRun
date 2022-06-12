// Fill out your copyright notice in the Description page of Project Settings.

#include "DR_PlayerController.h"
#include "DR_GameModeBase.h"
#include "DR_GameStateBase.h"
#include "Engine.h"
#include "DR_Player.h"
#include "DR_WidgetHUD.h"

void ADR_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(IsLocalController())
	{
		GameStateRef = Cast<ADR_GameStateBase>(GetWorld()->GetGameState());
	}
	
	SetPlayerRef();
}

//Setup the UE4 player input component and use it to bind input actions/axis to functions 
void ADR_PlayerController::SetupInputComponent()
{
	//Call the setup input component parent function
	Super::SetupInputComponent();
	if(InputComponent)
	{
		InputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ADR_PlayerController::RequestAttack);
		InputComponent->BindAction("PickupWeapon", IE_Pressed, this, &ADR_PlayerController::RequestPickupWeapon);
		InputComponent->BindAxis("MoveForward", this, &ADR_PlayerController::RequestMoveForward);
		InputComponent->BindAxis("MoveRight", this, &ADR_PlayerController::RequestMoveRight);
	}
}

void ADR_PlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();
	GameModeRef = Cast<ADR_GameModeBase>(GetWorld()->GetAuthGameMode());
	if(ensureMsgf(GameModeRef, TEXT("ADR_PlayerController::ReceivedPlayer is missing GameMode reference")))
	{
		GameModeRef->ReceivePlayer(this);
	}

	/*if(HUDClass)
	{
		HUDWidget = CreateWidget(this, HUDClass);

		if(HUDWidget)
		{
			HUDWidget->AddToViewport();	
		}
	}*/
}

void ADR_PlayerController::SpawnNewPlayer()
{
	GetWorld()->SpawnActor<AActor>(PlayerToSpawn);
}

void ADR_PlayerController::RequestMoveForward(float AxisValue)
{
	if(AxisValue != 0)
	{
		//Escape this function if the gamemode is not found, or the current gamestate is not "Playing"
		if(!GameStateRef || GameStateRef->GetCurrentGameState() != EGameState::Playing) { return; }

		//To move the player, we need to get the current player rotation so we can find the direction to move it in.
		//This is done by setting up a new FRotator, and using GetControlRotation
		const FRotator PlayerRotation = GetPawn()->GetControlRotation();
		GetPawn()->AddMovementInput(FRotationMatrix(PlayerRotation).GetScaledAxis(EAxis::X), AxisValue, false);
	}
}

void ADR_PlayerController::RequestMoveRight(float AxisValue)
{
	if(AxisValue != 0)
	{
		//Escape this function if the gamemode is not found, or the current gamestate is not "Playing"
		if(!GameStateRef || GameStateRef->GetCurrentGameState() != EGameState::Playing) { return; }

		//Update the control rotation so the character follows it (rotating the character itself didn't update the forward vector)
		//Get the current rotation, increase/decrease the yaw depending on the axis input
		FRotator CurrentRotation = GetControlRotation();
		SetControlRotation(FRotator(CurrentRotation.Pitch, CurrentRotation.Yaw + BaseRotationSpeed * AxisValue * GetWorld()->GetDeltaSeconds(), CurrentRotation.Roll));
	}
}

void ADR_PlayerController::RequestLookUp()
{
	//Escape this function if the gamemode is not found
	//if(!GameModeRef) {return;}
}

void ADR_PlayerController::RequestLookRight()
{
	//Escape this function if the gamemode is not found
	//if(!GameModeRef) {return;}
}
void ADR_PlayerController::RequestAttack()
{
	//Escape this function if the gamemode is not found, or the current gamestate is not "Playing"
	//if(!GameModeRef || GameModeRef->GetCurrentGameState() != EGameState::Playing) { return; }

	/* Tmp commented out
	//Play first on local machine for responsive feel, then play on server which will call the netmulticast
	  *CharacterRef->PlayMeleeAttackMontage();
	  *CharacterRef->ServerRequestAttack(); */

	//Get weapon the character is holding then call the use function
	//CharacterRef->
	if(CharacterRef)
	{
		if(CharacterRef->EquippedWeapon)
		{
			GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Red, TEXT("Attack!!"));
			CharacterRef->EquippedWeapon->UseWeapon();
		}	
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterRef null ADR_PlayerController::RequestAttack"))
	}
}

void ADR_PlayerController::RequestPickupWeapon()
{
	//Escape this function if the gamemode is not found, or the current gamestate is not "Playing"
	//if(!GameModeRef || GameModeRef->GetCurrentGameState() != EGameState::Playing) { return; }

	if(CharacterRef->bHasWeapon)
	{
		CharacterRef->UnEquipWeapon();	
	}

	else
	{
		CharacterRef->EquipWeapon();	
	}
}

void ADR_PlayerController::SetPlayerRef()
{
	CharacterRef = Cast<ADR_Player>(GetCharacter());
}

void ADR_PlayerController::RequestDefeat(ADR_PlayerController* OtherController)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Orange, __FUNCTION__);

	//Tell the server that the player has been defeated
	//ServerPlayerDefeated(OtherController);
	
	//Destroy character class ready for player respawn
	RequestDestroyCharacter();

	//Respawn
	//ServerRestartPlayer();	
}

void ADR_PlayerController::RequestDestroyCharacter()
{
	CharacterRef->Destroy();
}

void ADR_PlayerController::ServerResetPlayer(ADR_PlayerController* Controller)
{
	if(HasAuthority())
	{
		GameStateRef->AttemptRestartPlayer(Controller);
	}
}

void ADR_PlayerController::MulticastResetPlayer_Implementation(ADR_PlayerController* Controller)
{
	if(HasAuthority())
	{
		GameModeRef->ServerRequestResetPlayer(Controller);
	}
}


void ADR_PlayerController::ServerPlayerDefeated_Implementation(ADR_PlayerController* OtherController)
{
	MulticastPlayerDefeated(OtherController);
}

void ADR_PlayerController::MulticastPlayerDefeated_Implementation(ADR_PlayerController* OtherController)
{
	// Todo Increment score of other player
	//OtherController->IncrementPlayerScore();
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Orange, __FUNCTION__);
}

void ADR_PlayerController::IncrementPlayerScore()
{
	PlayerScore++;
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Orange, __FUNCTION__);
}








