// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_BS_Combo3Burst.h"

void UCAnimNotify_BS_Combo3Burst::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (GetPlayerCharacter(MeshComp))
	{
		IIWeapon* Weapon = Cast<IIWeapon>(WP);
		if (Weapon == nullptr) return;
		FireSocketTransform.SetRotation(FQuat::MakeFromRotator(PC->GetActorRotation()));
		FireSocketTransform.SetLocation(FireSocketTransform.GetLocation() + FVector::DownVector * 55.f);


		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			Weapon->GetWeaponEffect(E_MELEEATTACKCOMBO_3_EXPLODE),
			FireSocketTransform);
	}
}
