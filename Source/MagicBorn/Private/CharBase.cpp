// Fill out your copyright notice in the Description page of Project Settings.


#include "CharBase.h"
#include "AttributeSetBase.h"

// Sets default values
ACharBase::ACharBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");

	AttributeSetBaseComp = CreateDefaultSubobject<UAttributeSetBase>("AttributeSetBaseComp");

	AttributeSetBaseComp->OnHealthChange.AddDynamic(this, &ACharBase::OnHealthChanged);

	bIsDead = false;
}

// Called when the game starts or when spawned
void ACharBase::BeginPlay()
{
	Super::BeginPlay();
	
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
		BP_Die();
	}
	BP_OnHealthChanged(Health, MaxHealth);
}

