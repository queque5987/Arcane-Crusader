// Fill out your copyright notice in the Description page of Project Settings.


#include "CUserWIdget_BattleGauge.h"
#include "Materials/MaterialInstanceDynamic.h"

UCUserWIdget_BattleGauge::UCUserWIdget_BattleGauge(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UCUserWIdget_BattleGauge::NativeConstruct()
{
	Super::NativeConstruct();

	M_StateOrb = StateOrb->GetDynamicMaterial();
	if (M_StateOrb == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("On UCUserWIdget_BattleGauge M_StateOrb Not Found"));
		return;
	}
	M_ProgressBar = ProgressBar->GetDynamicMaterial();
	if (M_ProgressBar == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("On UCUserWIdget_BattleGauge M_ProgressBar Not Found"));
		return;
	}
	SetBruteMode(false);
	SetProgress(0.f);
	SetCooldown(1.f);
}

void UCUserWIdget_BattleGauge::SetBruteMode(bool e)
{
	if (M_StateOrb == nullptr) UE_LOG(LogTemp, Error, TEXT("Can Not Switch BruteMode M_StateOrb Not Found"));
	if (M_ProgressBar == nullptr) UE_LOG(LogTemp, Error, TEXT("Can Not Switch BruteMode M_ProgressBar Not Found"));

	M_StateOrb->SetScalarParameterValue("BruteMode", e ? 1.f : 0.f);
	M_ProgressBar->SetScalarParameterValue("BruteMode", e ? 1.f : 0.f);
}

void UCUserWIdget_BattleGauge::SetProgress(float Percent)
{
	if (M_ProgressBar == nullptr) UE_LOG(LogTemp, Error, TEXT("Can Not Set Progress M_ProgressBar Not Found"));

	M_ProgressBar->SetScalarParameterValue("Progress", Percent);
}

void UCUserWIdget_BattleGauge::SetCooldown(float Percent)
{
	if (M_ProgressBar == nullptr) UE_LOG(LogTemp, Error, TEXT("Can Not Set Progress M_ProgressBar Not Found"));
	//Clamp 0 ~ 1
	M_StateOrb->SetScalarParameterValue("Cooldown", FMath::Max(
		0.f,
		FMath::Min(
			1.f, Percent
		)
	));
}
