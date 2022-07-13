// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "CharBase.generated.h"

UCLASS()
class MAGICBORN_API ACharBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharBase")
	UAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharBase")
	class UAttributeSetBase* AttributeSetBaseComp;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	UFUNCTION(BlueprintCallable, Category = "CharBase")
		void AcquireAbility(TSubclassOf<UGameplayAbility> AbilityToAcquire);

	UFUNCTION()
		void OnHealthChanged(float Health, float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName="OnHealthChanged"))
		void BP_OnHealthChanged(float Health, float MaxHealth);


	UFUNCTION()
		void OnManaChanged(float Mana, float MaxMana);

	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "OnManaChanged"))
		void BP_OnManaChanged(float Mana, float MaxMana);

	UFUNCTION()
		void OnStrengthChanged(float Strength, float MaxStrength);

	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "OnStrengthChanged"))
		void BP_OnStrengthChanged(float Strength, float MaxStrength);

	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "Die"))
		void BP_Die();

	UFUNCTION(BlueprintCallable, Category = "CharBase")
		bool IsOtherHostile(ACharBase* Other);

	UFUNCTION(BlueprintCallable, Category = "CharBase")
		void AddGameplayTag(FGameplayTag &Tag);

	UFUNCTION(BlueprintCallable, Category = "CharBase")
		void RemoveGameplayTag(FGameplayTag &Tag);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterBase")
		FGameplayTag FullHealthTag;

	uint8 GetTeamID() const;

private:
	bool bIsDead;
	uint8 TeamID;

	void AutoDetermineTeamByController();
};
