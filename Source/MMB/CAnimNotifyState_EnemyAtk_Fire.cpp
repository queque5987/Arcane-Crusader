// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotifyState_EnemyAtk_Fire.h"
#include "CEnemyCharacter.h"
#include "CEnemy_TerrorBringer.h"
#include "CProjectile.h"
#include "IFlyMonster.h"

void UCAnimNotifyState_EnemyAtk_Fire::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	//Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	ContinueAttack = true;
	AttackType = ENEMY_ATTACK_RHAND;
	SpitFire = 0;

	if (MeshComp == nullptr) return;
	EnemyChar = Cast<ACEnemyCharacter>(MeshComp->GetOwner());
	EC = Cast<IIEnemyStateManager>(EnemyChar);
	if (EC == nullptr || EnemyChar == nullptr) return;
	IIFlyMonster* IEC = Cast<IIFlyMonster>(EnemyChar);
	if (IEC == nullptr) return;
	FireEffect = IEC->GetParticleSystem(E_ENEMYATTACK_FLAMETHROWER);
	FString SoundAddress = "/Game/Resources/Sound/Dragon/fire-sound-efftect-21991_5.fire-sound-efftect-21991_5";
	USoundBase* SoundWave = LoadObject<USoundBase>(nullptr, *SoundAddress);
	if (SoundWave != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Fire Sound Effect"));
		UGameplayStatics::PlaySoundAtLocation(MeshComp->GetOwner(), SoundWave, MeshComp->GetOwner()->GetActorLocation());
	}
}

void UCAnimNotifyState_EnemyAtk_Fire::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (!ContinueAttack) return;
	if (EC == nullptr) return;
	IIFlyMonster* IEC = Cast<IIFlyMonster>(MeshComp->GetOwner());
	if (IEC == nullptr) return;
	bool IsFlying = IEC->GetIsFlying();
	float projscale = IsFlying ? 30.f : 30.f;
	float projspeed = IsFlying ? 35.f : 25.f;
	float projclock = IsFlying ? 1.4f : 0.65f;
	float projscaleA = IsFlying ? 0.09f : 0.11f;

	FVector JawLocation = MeshComp->GetBoneLocation(JawBoneNameOverride);
	FVector HeadLocation = MeshComp->GetBoneLocation(HeadBoneNameOverride);

	FVector JawToHead = (JawLocation - HeadLocation).GetSafeNormal();
	FRotator HeadRotation = FRotationMatrix::MakeFromX(JawToHead).Rotator();
	//HeadRotation.Pitch += 30.f;
	//HeadRotation += FlameAxisAdjust;
	ACProjectile* Proj = MeshComp->GetWorld()->SpawnActor<ACProjectile>(
		ACProjectile::StaticClass(), JawLocation, HeadRotation);

	Proj->SetLaunch(
		EnemyChar,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		2.5f,
		2500.f,
		projspeed,
		1.6f,
		nullptr,
		false,
		false,
		true,
		projscaleA
	);
	Proj->SetProjCollisionScale(projscale);

	if (SpitFire % 3 == 0)
	{
		UParticleSystemComponent* FEC = UGameplayStatics::SpawnEmitterAttached(
			FireEffect,
			MeshComp,
			JawBoneNameOverride,
			IsFlying ? FVector(80.f, -120.f, 0.f) : FVector(40.f, -60.f, 0.f),
			//IsFlying ? FRotator(-90.f, 0.f, -50.f) : FRotator(-90.f, 0.f, -20.f),
			FlameAxisAdjust,
			IsFlying ? FVector(3.f, 3.f, 4.f) : FVector(2.5f, 2.f, 2.f),
			EAttachLocation::KeepRelativeOffset,
			true
		);
		if (FEC == nullptr) return;
		FEQueue.Enqueue(FEC);

		FTimerManager& TM = MeshComp->GetWorld()->GetTimerManager();
		TM.SetTimer(AttackTimerHandle, this, &UCAnimNotifyState_EnemyAtk_Fire::FEOff, 0.8f);
	}

	SpitFire++;
}

void UCAnimNotifyState_EnemyAtk_Fire::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UParticleSystemComponent* D;
	while (!FEQueue.IsEmpty())
	{
		if (FEQueue.Dequeue(D))
		{
			if (D == nullptr) break;
			D->SetActive(false);
		}
	}
}

void UCAnimNotifyState_EnemyAtk_Fire::FEOff()
{
	UParticleSystemComponent* D;
	if (FEQueue.Dequeue(D))
	{
		D->SetActive(false);
	}
}
