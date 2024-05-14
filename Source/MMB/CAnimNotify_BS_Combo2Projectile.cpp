// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_BS_Combo2Projectile.h"
#include "PCH.h"
//#include "Kismet/GameplayStatics.h"

void UCAnimNotify_BS_Combo2Projectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//UE_LOG(LogTemp, Log, TEXT("Combo2 Projectile spawn"));
	if (GetPlayerCharacter(MeshComp))
	{
		IIWeapon* Weapon = Cast<IIWeapon>(WP);
		if (Weapon == nullptr) return;
		FVector SpawnLocation = PC->GetActorLocation() + FVector::DownVector * 30.f;

		ACProjectile* Proj = GetWorld()->SpawnActor<ACProjectile>(ACProjectile::StaticClass(), SpawnLocation, PC->GetActorRotation());

		Proj->Collider->SetSphereRadius(180.f);
		Proj->SetLaunch(
			PC,
			Weapon->GetWeaponEffect(E_MELLEATTACKCOMBO_2_PROJECTILE),
			Weapon->GetWeaponEffect(E_MELLEATTACKCOMBO_2_PROJECTILE_HIT),
			nullptr,
			nullptr,
			Weapon->GettempDamage1(),
			700.f,
			10.f,
			2.8f,
			nullptr,
			true,
			true,
			false,
			0.f,
			Weapon->GetWeaponSoundEffect(SE_MELEEATTACKCOMBO_2_EXPLODE)
		);
		/*Proj->SetLaunch(
			PC,
			Weapon->GetWeaponEffect(E_MELLEATTACKCOMBO_2_PROJECTILE),
			Weapon->GetWeaponEffect(E_MELLEATTACKCOMBO_2_PROJECTILE_HIT), nullptr, nullptr,
			Weapon->GettempDamage1(), 700.f, 10.f, 2.8f,
			nullptr,
			true, true, false, float SnowballAcc = 0.01f,
			USoundBase * pExplodeSE = nullptr, USoundBase * pLaunchSE = nullptr
		)*/
		//Proj->SetExplodeSE(Weapon->GetWeaponSoundEffect(SE_MELEEATTACKCOMBO_2_EXPLODE));
		UGameplayStatics::PlaySoundAtLocation(PC->GetWorld(),
			Weapon->GetWeaponSoundEffect(SE_MELEEATTACKCOMBO_2_LAUNCH),
			SpawnLocation, 1.f, 0.65f
		);
	}
}
