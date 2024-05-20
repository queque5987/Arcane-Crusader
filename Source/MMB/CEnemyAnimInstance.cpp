// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyAnimInstance.h"
#include "PCH.h"

UCEnemyAnimInstance::UCEnemyAnimInstance()
{
	Pawn = nullptr;
	IsAir = false;
	MovementSpeed = 0.f;
	ZSpeed = 0.f;
	PawnAnimRadian = 0.f;
	IsHostile = false;

	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> RoarFinder(TEXT("/Game/FourEvilDragonsHP/Animations/DragonTheNightmare/ScreamAnim.ScreamAnim"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> AttackHandFinder(TEXT("/Game/FourEvilDragonsHP/Animations/DragonTheNightmare/AttackHandAnim.AttackHandAnim"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> AttackHeadFinder(TEXT("/Game/FourEvilDragonsHP/Animations/DragonTheNightmare/AttackHornAnim.AttackHornAnim"));
	//if (RoarFinder.Succeeded())
	//{
	//	AnimSequenceRoar = RoarFinder.Object;
	//}
	//if (AttackHandFinder.Succeeded())
	//{
	//	AnimSequenceAttackHand = AttackHandFinder.Object;
	//}
	//if (AttackHeadFinder.Succeeded())
	//{
	//	AnimSequenceAttackHead = AttackHeadFinder.Object;
	//}
}

void UCEnemyAnimInstance::NativeInitializeAnimation()
{
	EnemyCharacter = Cast<ACEnemyCharacter>(TryGetPawnOwner());
	if (EnemyCharacter != nullptr)
	{
		//EnemyCharacter->DoRoar.BindUFunction(this, TEXT("Roar"));
		//EnemyCharacter->DoAttackHand.BindUFunction(this, TEXT("AttackHand"));
		//EnemyCharacter->DoAttackHead.BindUFunction(this, TEXT("AttackHead"));

		OnMontageEnded.AddDynamic(this, &UCEnemyAnimInstance::SetbAttackingFree);
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
