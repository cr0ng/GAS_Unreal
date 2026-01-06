// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilitySystem/StatusAttributeSet.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UStatusAttributeSet::UStatusAttributeSet()
{
	InitMoveSpeed(500.0f);
	InitJumpPower(700.0f);
}

void UStatusAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}


