// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyAnimInstance.h"
#include "PCH.h"
#include "CStageGameMode.h"

UCEnemyAnimInstance::UCEnemyAnimInstance()
{
	Pawn = nullptr;
	IsAir = false;
	MovementSpeed = 0.f;
	ZSpeed = 0.f;
	PawnAnimRadian = 0.f;
	IsHostile = false;
	PlayRate = 1.f;
}

void UCEnemyAnimInstance::NativeInitializeAnimation()
{
	EnemyCharacter = Cast<ACEnemyCharacter>(TryGetPawnOwner());
	if (EnemyCharacter != nullptr)
	{
		OnMontageEnded.AddDynamic(this, &UCEnemyAnimInstance::SetbAttackingFree);
	}

	ACStageGameMode* StageGM = Cast<ACStageGameMode>(GetWorld()->GetAuthGameMode());
	if (StageGM != nullptr)
	{
		StageGM->PlayerDodged.BindLambda([&]() {
				PlayRate = 0.2f;
			}
		);
		StageGM->PlayerDodgedEnd.BindLambda([&]() {
			PlayRate = 1.f;
			}
		);
	}
}

void UCEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	UpdateProperties(DeltaSeconds);
}

void UCEnemyAnimInstance::UpdateProperties(float Delta)
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}
	if (Pawn != nullptr)
	{
		IsAir = Pawn->GetMovementComponent()->IsFalling();
		FVector PawnVelocity = Pawn->GetVelocity();
		MovementSpeed = (PawnVelocity * FVector(1.f, 1.f, 0.f)).Size();
		ZSpeed = PawnVelocity.Z;

		FRotator ViewRotatorYaw = FRotator(0.f, Pawn->GetViewRotation().Yaw, 0.f);
		FVector RelativeVelocityNormalizedVector = ViewRotatorYaw.UnrotateVector(Pawn->GetVelocity().GetSafeNormal());
		PawnAnimRadian = FMath::RoundToFloat(FMath::Atan2(RelativeVelocityNormalizedVector.Y, RelativeVelocityNormalizedVector.X) * 100.f) / 100.f;
	}
}

void UCEnemyAnimInstance::Roar()
{
	//PlaySlotAnimationAsDynamicMontage(AnimSequenceRoar, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCEnemyAnimInstance::AttackHand()
{
	//EnemyCharacter->SetDamageScale(0.3f);
	//EnemyCharacter->SetbAttacking(true);
	//PlaySlotAnimationAsDynamicMontage(AnimSequenceAttackHand, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCEnemyAnimInstance::AttackHead()
{
	//EnemyCharacter->SetDamageScale(0.8f);
	//EnemyCharacter->SetbAttacking(true);
	//PlaySlotAnimationAsDynamicMontage(AnimSequenceAttackHead, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCEnemyAnimInstance::AttackMouth()
{
}

void UCEnemyAnimInstance::SetbAttackingFree(UAnimMontage* Montage, bool bInterrupted)
{
	EnemyCharacter->SetbAttacking(false);
}
