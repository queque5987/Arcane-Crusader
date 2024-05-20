// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy_AnimInstance_Nightmare.h"
#include "CEnemyCharacter.h"

UCEnemy_AnimInstance_Nightmare::UCEnemy_AnimInstance_Nightmare() : Super()
{
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> RoarFinder(TEXT("/Game/FourEvilDragonsHP/Animations/DragonTheNightmare/ScreamAnim.ScreamAnim"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> AttackHandFinder(TEXT("/Game/FourEvilDragonsHP/Animations/DragonTheNightmare/AttackHandAnim.AttackHandAnim"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> AttackHeadFinder(TEXT("/Game/FourEvilDragonsHP/Animations/DragonTheNightmare/AttackHornAnim.AttackHornAnim"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> AttackMouthFinder(TEXT("/Game/FourEvilDragonsHP/Animations/DragonTheNightmare/AttackMouthAnim.AttackMouthAnim"));

	if (RoarFinder.Succeeded())			AnimSequenceRoar = RoarFinder.Object;
	if (AttackHandFinder.Succeeded())	AnimSequenceAttackHand = AttackHandFinder.Object;
	if (AttackHeadFinder.Succeeded())	AnimSequenceAttackHead = AttackHeadFinder.Object;
	if (AttackMouthFinder.Succeeded())	AnimSequenceAttackMouth = AttackMouthFinder.Object;
}

void UCEnemy_AnimInstance_Nightmare::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	//EnemyCharacter = Cast<ACEnemyCharacter>(TryGetPawnOwner());
	if (EnemyCharacter != nullptr)
	{
		EnemyCharacter->DoRoar.BindUFunction(this, TEXT("Roar"));
		EnemyCharacter->DoAttackHand.BindUFunction(this, TEXT("AttackHand"));
		EnemyCharacter->DoAttackHead.BindUFunction(this, TEXT("AttackHead"));
		EnemyCharacter->DoAttackMouth.BindUFunction(this, TEXT("AttackMouth"));
	}
}

void UCEnemy_AnimInstance_Nightmare::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UCEnemy_AnimInstance_Nightmare::Roar()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceRoar, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCEnemy_AnimInstance_Nightmare::AttackHand()
{
	EnemyCharacter->SetDamageScale(0.3f);
	EnemyCharacter->SetAttackPower(PLAYER_HIT_REACT_HITDOWN);
	EnemyCharacter->SetbAttacking(true);
	PlaySlotAnimationAsDynamicMontage(AnimSequenceAttackHand, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCEnemy_AnimInstance_Nightmare::AttackHead()
{
	EnemyCharacter->SetDamageScale(0.8f);
	EnemyCharacter->SetAttackPower(PLAYER_HIT_REACT_FLINCH);
	EnemyCharacter->SetbAttacking(true);
	PlaySlotAnimationAsDynamicMontage(AnimSequenceAttackHead, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCEnemy_AnimInstance_Nightmare::AttackMouth()
{
	EnemyCharacter->SetDamageScale(1.8f);
	EnemyCharacter->SetAttackPower(PLAYER_HIT_REACT_HITDOWN);
	EnemyCharacter->SetbAttacking(true);
	PlaySlotAnimationAsDynamicMontage(AnimSequenceAttackMouth, "DefaultSlot", 0.25f, 0.25f, 1.f);
}
