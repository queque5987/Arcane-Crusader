// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotifyState_EnemyAtk_FlyF.h"
#include "CEnemyAIController.h"
#include "IFlyMonster.h"

void UCAnimNotifyState_EnemyAtk_FlyF::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	ContinueAttack = true;
	//AttackType = ENEMY_ATTACK_RHAND;
	if (MeshComp == nullptr) return;
	ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(MeshComp->GetOwner());
	if (!IsValid(EC)) return;
	ACEnemyAIController* ECC = Cast<ACEnemyAIController>(EC->GetController());
	if (!IsValid(ECC)) return;
	FVector TargetDirection = ECC->GetChasingPlayerPos() - EC->GetActorLocation();
	TargetDirection = TargetDirection.GetSafeNormal();
	TargetRot = FRotationMatrix::MakeFromX(TargetDirection).Rotator();

	RotationAcc = 0.f;
}

void UCAnimNotifyState_EnemyAtk_FlyF::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	if (!ContinueAttack) return;
	if (MeshComp == nullptr) return;
	ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(MeshComp->GetOwner());
	if (!IsValid(EC)) return;
	ACEnemyAIController* ECC = Cast<ACEnemyAIController>(EC->GetController());
	if (!IsValid(ECC)) return;
	IIFlyMonster* IFly = Cast<IIFlyMonster>(EC);
	if (IFly == nullptr) return;


	if (RotationAcc < MaxRotAcc)
	{
		FVector TargetDirection = ECC->GetChasingPlayerPos() - EC->GetActorLocation();
		TargetDirection = TargetDirection.GetSafeNormal();
		FRotator CurrTargetRot = FRotationMatrix::MakeFromX(TargetDirection).Rotator();
		RotationAcc += IFly->GetRotationSpeed() * FrameDeltaTime;
		TargetRot = FMath::RInterpTo(TargetRot, CurrTargetRot, FrameDeltaTime, IFly->GetRotationSpeed());
	}
	//UE_LOG(LogTemp, Log, TEXT("Rotation Accumulation : %f"), RotationAcc);
	IFly->FlyTo(TargetRot, FrameDeltaTime, (RotationAcc < MaxRotAcc) ? 1.f : 0.2f);
}
