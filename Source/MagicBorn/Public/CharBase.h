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


	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;


	UFUNCTION(BlueprintCallable, Category = "CharBase")
		void AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAcquire);

};
