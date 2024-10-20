// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotifyState_PlayerAttack.h"

void UCAnimNotifyState_PlayerAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	StopAttack = false;
	if (GetPlayerCharacter(MeshComp))
	{
		if (IIWeapon* IWeaponEquipped = Cast<IIWeapon>(PC->WeaponEquipped))
		{
			float ST = IWeaponEquipped->GetRequiredStamina();
			IWeaponEquipped->SetRequiredStamina(0.f);
			if (ST > 0.f) PC->StaminaSpend(ST);
		}
	}
}

void UCAnimNotifyState_PlayerAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	//if (StopAttack) return;
	if (PC != nullptr)
	{
		if (IIWeapon* IWeaponEquipped = Cast<IIWeapon>(PC->WeaponEquipped))
		{
			IWeaponEquipped->MeleeAttackHitCheck(Staff_0_LFist_1_RFist_2, DamageScale);
		}
	}
}

void UCAnimNotifyState_PlayerAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (PC != nullptr)
	{
		if (IIWeapon* IWeaponEquipped = Cast<IIWeapon>(PC->WeaponEquipped))
		{
			IWeaponEquipped->OnAttackSwingEnd();
		}
	}
}

bool UCAnimNotifyState_PlayerAttack::GetPlayerCharacter(USkeletalMeshComponent* MeshComp)
{
	PC = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	return (PC != nullptr) ? true : false;
}
