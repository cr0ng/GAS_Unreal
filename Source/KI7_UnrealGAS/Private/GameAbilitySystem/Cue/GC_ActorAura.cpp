// Fill out your copyright notice in the Description page of Project Settings.

#include "GameAbilitySystem/Cue/GC_ActorAura.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "GameFramework/Character.h"


AGC_ActorAura::AGC_ActorAura()
{
	GameplayCueTag = FGameplayTag::RequestGameplayTag(FName("GameplayCue.TestAura"));
	bAutoDestroyOnRemove = true;
}

bool AGC_ActorAura::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
    if (SpawnedVFX.IsValid())   // 안전장치 (혹시 만들어진게 있으면 제거하고 진행하라)
    {
        SpawnedVFX->Deactivate();
        SpawnedVFX = nullptr;
    }

    if (MyTarget)
    {
        // 캐릭터에 붙이기
        USceneComponent* AttachComponent = nullptr;
        ACharacter* Character = Cast<ACharacter>(MyTarget);
        if (Character)
        {
            AttachComponent = Character->GetMesh();  // Mesh에 붙이면 움직임에 따라감
        }
        else
        {
            AttachComponent = MyTarget->GetRootComponent();  // 그냥 Actor이면 RootComponent에 붙임
        }

        SpawnedVFX = UNiagaraFunctionLibrary::SpawnSystemAttached(    // 파티클 만들어서 저장해 놓기
            TestVFX,
            AttachComponent,        // AttachTo
            NAME_None,              // AttachPointName
            FVector::ZeroVector,    // 위치 오프셋
            FRotator::ZeroRotator,  // 회전 오프셋
            EAttachLocation::SnapToTarget, // 위치 맞춤
            true                    // AutoDestroy
        );
        return true;
    }
    return false;
}

bool AGC_ActorAura::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
    if (SpawnedVFX.IsValid())
    {
        SpawnedVFX->Deactivate();
        SpawnedVFX = nullptr;
    }
    return true;
}
