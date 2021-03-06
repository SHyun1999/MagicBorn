// Fill out your copyright notice in the Description page of Project Settings.


#include "CharBase.h"
#include "AttributeSetBase.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "BrainComponent.h"

// Sets default values
ACharBase::ACharBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");

	AttributeSetBaseComp = CreateDefaultSubobject<UAttributeSetBase>("AttributeSetBaseComp");

	AttributeSetBaseComp->OnHealthChange.AddDynamic(this, &ACharBase::OnHealthChanged);
	AttributeSetBaseComp->OnManaChange.AddDynamic(this, &ACharBase::OnManaChanged);
	AttributeSetBaseComp->OnStrengthChange.AddDynamic(this, &ACharBase::OnStrengthChanged);

	bIsDead = false;
	TeamID = 255;

	AddGameplayTag(FullHealthTag);
}

// Called when the game starts or when spawned
void ACharBase::BeginPlay()
{
	Super::BeginPlay();
	AutoDetermineTeamByController();
	
}

// Called every frame
void ACharBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ACharBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void ACharBase::AcquireAbility(TSubclassOf<UGameplayAbility> AbilityToAcquire)
{

	if (AbilitySystemComp)
	{
		if (HasAuthority() && AbilityToAcquire)
		{
			FGameplayAbilitySpecDef SpecDef = FGameplayAbilitySpecDef();
			SpecDef.Ability = AbilityToAcquire;
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(SpecDef, 1);
			AbilitySystemComp->GiveAbility(AbilitySpec);
		}

		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}
}

void ACharBase::OnHealthChanged(float Health, float MaxHealth)
{

	if (Health <= 0.f && !bIsDead)
	{
		bIsDead = true;

		APlayerController* PC = Cast<APlayerController>(GetController());
		if (PC)
		{
			PC->DisableInput(PC);
		}

		AAIController* AIC = Cast<AAIController>(GetController());

		if (AIC)
		{
			AIC->GetBrainComponent()->StopLogic("Ded");
		}
		BP_Die();
	}
	BP_OnHealthChanged(Health, MaxHealth);
}

void ACharBase::OnManaChanged(float Mana, float MaxMana)
{
	BP_OnManaChanged(Mana, MaxMana);
}

void ACharBase::OnStrengthChanged(float Strength, float MaxStrength)
{
	BP_OnStrengthChanged(Strength, MaxStrength);
}

bool ACharBase::IsOtherHostile(ACharBase* Other)
{
	return TeamID != Other->GetTeamID();
}

void ACharBase::AddGameplayTag(FGameplayTag& Tag)
{
	GetAbilitySystemComponent()->AddLooseGameplayTag(Tag);
	GetAbilitySystemComponent()->SetTagMapCount(Tag, 1);
}

void ACharBase::RemoveGameplayTag(FGameplayTag& Tag)
{
	GetAbilitySystemComponent()->RemoveLooseGameplayTag(Tag);
}

uint8 ACharBase::GetTeamID() const
{
	return TeamID;
}

void ACharBase::AutoDetermineTeamByController()
{
	if (GetController() && GetController()->IsPlayerController())
	{
		TeamID = 0;
	}
}

