// Fill out your copyright notice in the Description page of Project Settings.

#include "DR_WeaponBase.h"
#include "DR_Player.h"
#include "Engine.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ADR_WeaponBase::ADR_WeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;
	InteractBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Box"));
	RootComponent = InteractBox;

	bReplicates = true;
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void ADR_WeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
	InteractBox->OnComponentBeginOverlap.AddDynamic(this, &ADR_WeaponBase::OnOverlapBegin);
	InteractBox->OnComponentEndOverlap.AddDynamic(this, &ADR_WeaponBase::OnOverlapEnd);
}

// Called every frame
void ADR_WeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADR_WeaponBase::SetEquipped(ADR_Player* Player)
{
	PlayerRef = Player;
	bIsEquipped = true;
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Orange, __FUNCTION__);
	UE_LOG(LogTemp, Warning, TEXT("ADR_WeaponBase::SetEquipped"));
}

void ADR_WeaponBase::SetUnEquipped()
{
	bIsEquipped = false;
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Orange, __FUNCTION__);
}


void ADR_WeaponBase::UseWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("ADR_WeaponBase::UseWeapon"));
}

void ADR_WeaponBase::ActivateMeleeCollision()
{
}

void ADR_WeaponBase::DeactivateMeleeCollision()
{
}

//Overlap for pickup box
void ADR_WeaponBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!bIsEquipped && !bCanBeEquipped)
	{
		PlayerRef = Cast<ADR_Player>(OtherActor);
		if(PlayerRef)
		{
			bCanBeEquipped = true;
			PlayerRef->SetAvailableWeapon(this);
		}
	}
}

//Overlap for pickup box
void ADR_WeaponBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(!bIsEquipped && bCanBeEquipped)
	{
		if(PlayerRef)
		{
			bCanBeEquipped = false;
			PlayerRef->ClearAvailableWeapon();
			PlayerRef = nullptr;
		}
	}
}


