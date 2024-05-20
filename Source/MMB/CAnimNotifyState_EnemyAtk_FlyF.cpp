// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotifyState_EnemyAtk_FlyF.h"
#include "CEnemyAIController.h"
#include "IFlyMonster.h"
#include "PCH.h"

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

	FVector tempVector = EC->GetActorLocation();
	FVector DesiredFireDirection = tempVector + (EC->GetActorForwardVector() * IFly->GetCurrentAltitude()*3);
	FVector DesiredFireLocation = ECC->GetChasingPlayerPos() - (EC->GetActorForwardVector() * IFly->GetCurrentAltitude() * 3);
	//DrawDebugLine(MeshComp->GetWorld(), tempVector, tempDrawVector, FColor::Cyan, false, 0.1f, 0U, 50.f);

	//DrawDebugSphere(MeshComp->GetWorld(), tempDrawVector, 120.f, 32.f, FColor::Cyan, false, 0.4f);


	FHitResult HitResult;
	FCollisionObjectQueryParams OQP(EC->GetMesh()->GetCollisionObjectType());
	FCollisionShape CS = FCollisionShape();
	CS.SetSphere(120.f);
	bool bResult = MeshComp->GetWorld()->SweepSingleByChannel(
		HitResult, tempVector, DesiredFireDirection, FQuat::Identity, EC->GetMesh()->GetCollisionObjectType(), CS
	);

	if (bResult && Cast<ACPlayerCharacter>(HitResult.GetActor()))
	{
		UE_LOG(LogTemp, Log, TEXT("Hit Actor : %s"), *HitResult.GetActor()->GetName());
		IFly->FlyTo(DesiredFireLocation, FrameDeltaTime, 50.f, 1.f);
	}
	else
	{
		IFly->FlyTo(DesiredFireLocation, FrameDeltaTime, 50.f, 5.f);
		IFly->RotateTo(ECC->GetChasingPlayerPos(), FrameDeltaTime, 1.f);
		return;
		if (RotationAcc < MaxRotAcc)
		{
			FVector TargetDirection = DesiredFireLocation - EC->GetActorLocation();
			TargetDirection = TargetDirection.GetSafeNormal();
			FRotator CurrTargetRot = FRotationMatrix::MakeFromX(TargetDirection).Rotator();
			RotationAcc += IFly->GetRotationSpeed() * FrameDeltaTime;
			TargetRot = FMath::RInterpTo(TargetRot, CurrTargetRot, FrameDeltaTime, IFly->GetRotationSpeed());
		}
		//UE_LOG(LogTemp, Log, TEXT("Rotation Accumulation : %f"), RotationAcc);
		IFly->FlyTo(TargetRot, FrameDeltaTime, (RotationAcc < MaxRotAcc) ? 1.f : 0.2f);
	}
}
