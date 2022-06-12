// Fill out your copyright notice in the Description page of Project Settings.


#include "NS_MeleeAttackNotifyState.h"

#include "DR_Player.h"
#include "Engine.h"

class ADR_Player;

void UNS_MeleeAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                             float TotalDuration)
{
	//Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Orange, __FUNCTION__);

	if(MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		ADR_Player* Player = Cast<ADR_Player>(MeshComp->GetOwner());
		if(Player != NULL && Player->EquippedWeapon != nullptr)
		{
			Player->EquippedWeapon->ActivateMeleeCollision();
		}
	}
	
}

void UNS_MeleeAttackNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	//Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Orange, __FUNCTION__);
}

void UNS_MeleeAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//Super::NotifyEnd(MeshComp, Animation);
	//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Orange, __FUNCTION__);

	if(MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		ADR_Player* Player = Cast<ADR_Player>(MeshComp->GetOwner());
		if(Player != NULL && Player->EquippedWeapon != nullptr)
		{
			Player->EquippedWeapon->DeactivateMeleeCollision();
		}
	}
}
