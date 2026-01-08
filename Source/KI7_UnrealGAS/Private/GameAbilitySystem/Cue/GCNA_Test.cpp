// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilitySystem/Cue/GCNA_Test.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

AGCNA_Test::AGCNA_Test()
{
	GameplayCueTag = FGameplayTag::RequestGameplayTag(FName("GameplayCue.TestActor"));
    bAutoDestroyOnRemove = true;
}

bool AGCNA_Test::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
    if (SpawnedVFX.IsValid())   // 안전장치 (혹시 만들어진게 있으면 제거하고 진행하라)
    {
        SpawnedVFX->Deactivate();
        SpawnedVFX = nullptr;
    }

    if (MyTarget)
    {
        SpawnedVFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(    // 파티클 만들어서 저장해 놓기
            GetWorld(),
            TestVFX,
            MyTarget->GetActorLocation(),   // 생성 위치
            MyTarget->GetActorRotation()    // 생성할 때 회전
        );
        return true;
    }
    return false;
}

bool AGCNA_Test::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
    if (SpawnedVFX.IsValid())
    {
        SpawnedVFX->Deactivate();
        SpawnedVFX = nullptr;
    }
	return true;
}
