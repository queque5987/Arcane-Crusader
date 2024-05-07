// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_BS_Combo2Projectile.h"

void UCAnimNotify_BS_Combo2Projectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//UE_LOG(LogTemp, Log, TEXT("Combo2 Projectile spawn"));
	if (GetPlayerCharacter(MeshComp))
	{
		IIWeapon* Weapon = Cast<IIWeapon>(WP);
		if (Weapon == nullptr) return;
		FVector SpawnLocation = PC->GetActorLocation() + FVector::DownVector * 10.f;

		ACProjectile* Proj = GetWorld()->SpawnActor<ACProjectile>(ACProjectile::StaticClass(), SpawnLocation, PC->GetActorRotation());

		Proj->Collider->SetSphereRadius(80.f);
		Proj->SetLaunch(
			PC,
			Weapon->GetWeaponEffect(E_MELLEATTACKCOMBO_2_PROJECTILE),
			Weapon->GetWeaponEffect(E_MELEEATTACK_HITEFFECT),
			nullptr,
			nullptr,
			Weapon->GettempDamage1(),
			700.f,
			10.f,
			2.8f,
			nullptr,
			true,
			true);
	}
}
