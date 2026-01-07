// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEEC_IceDamage.generated.h"

/**
 * 
 */
UCLASS()
class KI7_UNREALGAS_API UGEEC_IceDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UGEEC_IceDamage();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CustomData")
	TObjectPtr<UCurveTable> DamageTable = nullptr;
};
