// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_BS_Combo1Projectile.h"
#include "PCH.h"

void UCAnimNotify_BS_Combo1Projectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (GetPlayerCharacter(MeshComp))
	{
		IIWeapon* Weapon = Cast<IIWeapon>(WP);
		if (Weapon == nullptr) return;
		FVector LIndexSocketLocation = PC->GetMesh()->GetBoneLocation("RightHandIndex3");
		FVector SpawnLocation = LIndexSocketLocation + PC->GetActorRotation().RotateVector(FVector::BackwardVector * 50.f + FVector::LeftVector * 50.f);
		float AttackRange = 500.f;
		FHitResult HitResult;
		FVector TargetLocation = PC->CameraComponent->GetComponentLocation() + PC->GetBaseAimRotation().RotateVector(FVector::ForwardVector * (AttackRange + 550.f));

		DrawDebugLine(GetWorld(), SpawnLocation, TargetLocation, FColor::Cyan, false, 1.2f, 0U, 3.f);

		PC->GetLineTraceResult(HitResult, AttackRange);
		if (HitResult.bBlockingHit)
		{
			TargetLocation = HitResult.Location;
		}

		FRotator ProjRotator = (TargetLocation - LIndexSocketLocation).Rotation();

		
		ACProjectile* Proj = GetWorld()->SpawnActor<ACProjectile>(ACProjectile::StaticClass(), LIndexSocketLocation + FVector::UpVector * 30.f, ProjRotator);
		struct DELAY_START_PROJECTILE_CONFIGURE DelayConfig = DELAY_START_PROJECTILE_CONFIGURE();
		DelayConfig.AccCoefficient = 4.5f;
		DelayConfig.LaunchClock = 0.4f;
		DelayConfig.MaxSpeedCoefficient = 2.f;

		Proj->SetLaunch(
			PC,
			Weapon->GetWeaponEffect(E_MELEEATTACKCOMBO_1_PROJECTILE),
			Weapon->GetWeaponEffect(E_MELLEATTACKCOMBO_2_PROJECTILE_HIT),
			Weapon->GetWeaponEffect(E_MELLEATTACKCOMBO_1_PROJECTILE_SPAWN),
			Weapon->GetWeaponEffect(E_MELLEATTACKCOMBO_1_PROJECTILE_LAUNCH),
			Weapon->GettempDamage0(),
			800.f,
			20.f,
			-1.f,
			&DelayConfig
		);
		Proj->SetExplodeSE(Weapon->GetWeaponSoundEffect(SE_MELEEATTACKCOMBO_2_EXPLODE));
		Proj->SetLaunchSE(Weapon->GetWeaponSoundEffect(SE_MELEEATTACKCOMBO_1_LAUNCH));
		//DrawDebugSphere(GetWorld(), LIndexSocketLocation + PC->GetActorRotation().RotateVector(FVector::BackwardVector * 150.f + FVector::LeftVector * 150.f), 30.f, 26, FColor::Red, true, 2.f);
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WP->WeaponEffect[E_MELEEATTACKCOMBO_1_PROJECTILE], LIndexSocketLocation - PC->GetBaseAimRotation().RotateVector(FVector::BackwardVector * 100.f));
	}
}
