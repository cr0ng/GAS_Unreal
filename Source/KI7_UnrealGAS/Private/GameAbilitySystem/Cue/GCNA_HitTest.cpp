// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilitySystem/Cue/GCNA_HitTest.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

AGCNA_HitTest::AGCNA_HitTest()
{
	GameplayCueTag = FGameplayTag::RequestGameplayTag(FName("GameplayCue.HitTestActor"));
	bAutoDestroyOnRemove = true;
}

bool AGCNA_HitTest::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
    if (SpawnedVFX.IsValid())   // 안전장치 (혹시 만들어진게 있으면 제거하고 진행하라)
    {
        SpawnedVFX->Deactivate();
        SpawnedVFX = nullptr;
    }

    if (MyTarget)
    {
        const FHitResult* HitResult = Parameters.EffectContext.GetHitResult();
        FRotator HitRotator = HitResult->ImpactNormal.Rotation();   // ImpactNoraml 방향을 forward로 하는 회전

        SpawnedVFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(    // 파티클 만들어서 저장해 놓기
            GetWorld(),
            TestVFX,
            HitResult->ImpactPoint,   // 생성 위치
            HitRotator				  // 생성할 때 회전
        );

        return true;
    }
    return false;
}

bool AGCNA_HitTest::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
    if (SpawnedVFX.IsValid())
    {
        SpawnedVFX->Deactivate();
        SpawnedVFX = nullptr;
    }
    return true;
}
