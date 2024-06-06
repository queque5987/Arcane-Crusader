// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy_AnimInstance_TB.h"
#include "CEnemy_TerrorBringer.h"

UCEnemy_AnimInstance_TB::UCEnemy_AnimInstance_TB()
{
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> RoarFinder			(TEXT("/Game/FourEvilDragonsHP/Animations/DragonTheTerrorBringer/ScreamAnim"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> AttackHandFinder	(TEXT("/Game/FourEvilDragonsHP/Animations/DragonTheTerrorBringer/AttackWingClawAnim"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> FireFinder (TEXT("/Game/FourEvilDragonsHP/Animations/DragonTheTerrorBringer/AttackFlameAnim"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> FlyFireFinder(TEXT("/Game/FourEvilDragonsHP/Animations/DragonTheTerrorBringer/FlyAttackAnim"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> LandFinder(TEXT("/Game/FourEvilDragonsHP/Animations/DragonTheTerrorBringer/LandingAnim"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> TakeOffFinder(TEXT("/Game/FourEvilDragonsHP/Animations/DragonTheTerrorBringer/TakeOffAnim"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> AttackMouthFinder(TEXT("/Game/FourEvilDragonsHP/Animations/DragonTheTerrorBringer/AttackMouthAnim"));
	
	if (RoarFinder.Succeeded())			AnimSequenceRoar = RoarFinder.Object;
	if (AttackHandFinder.Succeeded())	AnimSequenceAttackHand = AttackHandFinder.Object;
	if (FireFinder.Succeeded())			AnimSequenceFire = FireFinder.Object;
	if (FlyFireFinder.Succeeded())		AnimSequenceFlyFire = FlyFireFinder.Object;
	if (LandFinder.Succeeded())			AnimSequenceLand = LandFinder.Object;
	if (TakeOffFinder.Succeeded())		AnimSequenceTakeOff = TakeOffFinder.Object;
	if (AttackMouthFinder.Succeeded())	AnimSequenceAttackMouth = AttackMouthFinder.Object;
}

void UCEnemy_AnimInstance_TB::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	EnemyCharacter = Cast<ACEnemyCharacter>(TryGetPawnOwner());
	if (EnemyCharacter != nullptr)
	{
		EnemyCharacter->DoRoar.BindUFunction(this, TEXT("Roar"));
		EnemyCharacter->DoAttackHand.BindUFunction(this, TEXT("AttackHand"));
		EnemyCharacter->DoAttackFire.BindUFunction(this, TEXT("AttackFire"));
		if (ACEnemy_TerrorBringer* TB = Cast<ACEnemy_TerrorBringer>(EnemyCharacter))
		{
			TB->DoFlyFireAttack.BindUFunction(this, TEXT("AttackFlyFire"));
		}
		EnemyCharacter->DoAttackMouth.BindUFunction(this, TEXT("AttackMouth"));
	}
}

void UCEnemy_AnimInstance_TB::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UCEnemy_AnimInstance_TB::UpdateProperties(float Delta)
{
	Super::UpdateProperties(Delta);

	if (EnemyCharacter == nullptr) return;
	IIFlyMonster* FM = Cast<IIFlyMonster>(EnemyCharacter);
	if (FM == nullptr) return;

	MaxAltitude = FM->GetMaxAltitude();
	CurrentAltitude = FM->GetCurrentAltitude();

}

void UCEnemy_AnimInstance_TB::Roar()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceRoar, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCEnemy_AnimInstance_TB::AttackHand()
{
	EnemyCharacter->SetDamageScale(0.3f);
	EnemyCharacter->SetAttackPower(PLAYER_HIT_REACT_FLINCH);
	EnemyCharacter->SetbAttacking(true);
	UE_LOG(LogTemp, Log, TEXT("Attack Hand"));
	PlaySlotAnimationAsDynamicMontage(AnimSequenceAttackHand, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCEnemy_AnimInstance_TB::AttackMouth()
{
	EnemyCharacter->SetDamageScale(0.8f);
	EnemyCharacter->SetAttackPower(PLAYER_HIT_REACT_HITDOWN);
	EnemyCharacter->SetbAttacking(true);
	PlaySlotAnimationAsDynamicMontage(AnimSequenceAttackMouth, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCEnemy_AnimInstance_TB::AttackFire()
{
	EnemyCharacter->SetbAttacking(true);
	EnemyCharacter->SetAttackPower(PLAYER_HIT_REACT_STAND);
	PlaySlotAnimationAsDynamicMontage(AnimSequenceFire, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCEnemy_AnimInstance_TB::AttackFlyFire()
{
	EnemyCharacter->SetbAttacking(true);
	EnemyCharacter->SetAttackPower(PLAYER_HIT_REACT_STAND);
	PlaySlotAnimationAsDynamicMontage(AnimSequenceFlyFire, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCEnemy_AnimInstance_TB::Land()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceLand, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCEnemy_AnimInstance_TB::TakeOff()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceTakeOff, "DefaultSlot", 0.25f, 0.25f, 1.f);
}
