// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_BS_FinishAttackBurst.h"
#include "PCH.h"

UCAnimNotify_BS_FinishAttackBurst::UCAnimNotify_BS_FinishAttackBurst()
{
	ArrExplodeTimerHandler.SetNum(6);
	for (auto& TimerHandler : ArrExplodeTimerHandler)
	{
		TimerHandler = FTimerHandle();
	}
}

void UCAnimNotify_BS_FinishAttackBurst::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (GetPlayerCharacter(MeshComp))
	{
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WP->WeaponEffect[E_MELEEATTACKCOMBO_3_FINALATTACK_EXPLODE], FireSocketTransform);

		FVector ForwardVector = PC->GetActorForwardVector();
		FVector RightVector = PC->GetActorRightVector();

		FVector SpawnLocation = PC->GetActorLocation() + FVector::DownVector * 90.f + ForwardVector * 50.f;
		FVector SpawnLocation1 = SpawnLocation + ForwardVector * 250.f + RightVector * 150.f;
		FVector SpawnLocation2 = SpawnLocation + ForwardVector * 250.f - RightVector * 150.f;

		FVector SpawnLocation3 = SpawnLocation + ForwardVector * 500.f + RightVector * 400.f;
		FVector SpawnLocation4 = SpawnLocation + ForwardVector * 500.f;
		FVector SpawnLocation5 = SpawnLocation + ForwardVector * 500.f - RightVector * 400.f;
		SpawnLocations.Empty();
		SpawnLocations.Enqueue(SpawnLocation);
		SpawnLocations.Enqueue(SpawnLocation1);
		SpawnLocations.Enqueue(SpawnLocation2);
		SpawnLocations.Enqueue(SpawnLocation3);
		SpawnLocations.Enqueue(SpawnLocation4);
		SpawnLocations.Enqueue(SpawnLocation5);

		float Delay = 0.01f;
		int MC = 2;
		int C = 1;
		FVector SL;
		for (auto& H : ArrExplodeTimerHandler)
		{
			GetWorld()->GetTimerManager().SetTimer(H, this, &UCAnimNotify_BS_FinishAttackBurst::test, Delay);
			C -= 1;
			if (C <= 0)
			{
				Delay += 0.3f;
				C = MC;
				MC *= 2;
			}
		}
	}
}

void UCAnimNotify_BS_FinishAttackBurst::SpawnBonusExplosion(FVector SpawnLocation, FRotator ActorRotation,float DelayClock)
{
	IIWeapon* Weapon = Cast<IIWeapon>(WP);
	if (Weapon == nullptr) return;
	ACProjectile* Proj = GetWorld()->SpawnActor<ACProjectile>(ACProjectile::StaticClass(), SpawnLocation, ActorRotation);
	DELAY_START_PROJECTILE_CONFIGURE Config = DELAY_START_PROJECTILE_CONFIGURE();
	Config.LaunchClock = DelayClock;
	Proj->Collider->SetSphereRadius(120.f);

	//UParticleSystem** U1 = WP->GetWeaponEffect(E_MELEEATTACK_HITEFFECT);
	//UParticleSystem** U2 = WP->GetWeaponEffect(E_MELEEATTACKCOMBO_3_FINALATTACK_BONUS_EXPLODE);
	//TArray<UParticleSystem*>* ParticleArr = WP->GetWeaponEffect();
	//TArray<UParticleSystem*> ParticleArr = *(WP->GetWeaponEffect());
	Proj->SetLaunch(
		PC,
		nullptr,
		Weapon->GetWeaponEffect(E_MELEEATTACK_HITEFFECT),
		//ParticleArr[E_MELEEATTACK_HITEFFECT],
		nullptr,
		Weapon->GetWeaponEffect(E_MELEEATTACKCOMBO_3_FINALATTACK_BONUS_EXPLODE),
		//ParticleArr[E_MELEEATTACKCOMBO_3_FINALATTACK_BONUS_EXPLODE],
		Weapon->GettempDamage1(),
		100.f,
		10.f,
		1.3f + DelayClock,
		(DelayClock > 0.f) ? &Config : nullptr,
		true, true
	);
}

bool UCAnimNotify_BS_FinishAttackBurst::Sweep(FHitResult& HitResult, FVector SpawnLocation)
{
	FCollisionQueryParams Params(NAME_None, false, PC);
	FCollisionObjectQueryParams OQP(PlayerAttackChannel);

	bool bResult = PC->GetWorld()->SweepSingleByObjectType(
		HitResult,
		SpawnLocation,
		SpawnLocation + FVector::UpVector * ExplodeRadius*2,
		FQuat::Identity,
		OQP,
		FCollisionShape::MakeSphere(ExplodeRadius),
		Params
	);
	return bResult;
}

void UCAnimNotify_BS_FinishAttackBurst::test()
{
	UE_LOG(LogTemp, Log, TEXT("Test function called"));
	FVector SL;
	if (SpawnLocations.Dequeue(SL))
	{
		IIWeapon* Weapon = Cast<IIWeapon>(WP);
		if (Weapon == nullptr) return;
		FHitResult HitResult;
		bool bResult = Sweep(HitResult, SL);
		//DrawDebugSphere(PC->GetWorld(), SL, 120.f, 20.f, bResult? FColor::Green : FColor::Red, false, 1.5f);

		UGameplayStatics::SpawnEmitterAtLocation(PC->GetWorld(),
			Weapon->GetWeaponEffect(E_MELEEATTACKCOMBO_3_FINALATTACK_EXPLODE),
			SL
		);
		UGameplayStatics::PlaySoundAtLocation(PC->GetWorld(),
			Weapon->GetWeaponSoundEffect(SE_MELEEATTACKCOMBO_3_EXPLODE),
			SL, 0.8f, 0.65f
		);
		if (bResult)
		{
			ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(HitResult.GetActor());
			if (EC == nullptr) return;
			EC->HitDamage(Weapon->GettempDamage2(), *PC, HitResult.Location);
			FTransform SpawnTransform;
			SpawnTransform.SetScale3D(FVector(3.f, 3.f, 3.f));
			SpawnTransform.SetLocation(SL);
			UGameplayStatics::SpawnEmitterAtLocation(PC->GetWorld(),
				Weapon->GetWeaponEffect(E_MELLEATTACKCOMBO_2_PROJECTILE_HIT),
				SpawnTransform
			);
		}
	}
}
