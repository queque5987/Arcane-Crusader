// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerAnimInstance.h"

UCPlayerAnimInstance::UCPlayerAnimInstance()
{
	Pawn = nullptr;
	IsAir = false;
	MovementSpeed = 0.f;
	ZSpeed = 0.f;
	PawnAnimRadian = 0.f;


	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> LMBAttackFinder(TEXT("/Game/BattleWizardPolyart/Animations/Attack01Anim.Attack01Anim"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> RMBCastStartFinder(TEXT("/Game/BattleWizardPolyart/Animations/Attack03StartAnim.Attack03StartAnim"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> RMBCastOngoingFinder(TEXT("/Game/BattleWizardPolyart/Animations/Attack03MaintainAnim.Attack03MaintainAnim"));

	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> MeleeComboFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Standing_Melee_Combo_Attack_Ver__2.Standing_Melee_Combo_Attack_Ver__2"));

	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> MeleeCombo1Finder(TEXT("/Game/Player/Animation/BS_Combo/Mage_Standing_Melee_Combo_Attack_1.Mage_Standing_Melee_Combo_Attack_1"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> MeleeCombo2Finder(TEXT("/Game/Player/Animation/BS_Combo/Mage_Standing_Melee_Combo_Attack_2.Mage_Standing_Melee_Combo_Attack_2"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> MeleeCombo3Finder(TEXT("/Game/Player/Animation/BS_Combo/Mage_Standing_Melee_Combo_Attack_3.Mage_Standing_Melee_Combo_Attack_3"));

	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> FinishAttackFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Sword_And_Shield_Slash.Sword_And_Shield_Slash"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> Combo1AttackFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Standing_1H_Magic_Attack_01.Standing_1H_Magic_Attack_01"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> Combo2AttackFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Standing_1H_Magic_Attack_03.Standing_1H_Magic_Attack_03"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> StandToRollFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Sprinting_Forward_Roll.Sprinting_Forward_Roll"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> HitDownFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Falling_Back_Death.Falling_Back_Death"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> HitDownRecover(TEXT("/Game/Player/Guard/Animation/Hostile/Stand_Up.Stand_Up"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> DizzyFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Injured_Idle.Injured_Idle"));

	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> RopeClimbFinder(TEXT("/Game/Player/Guard/Animation/Climbing_A_Rope.Climbing_A_Rope"));

	

	//Knithe Version
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> LMBAttackFinder(TEXT("/Game/BattleWizardPolyart/Animations/Attack01Anim.Attack01Anim"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> RMBCastStartFinder(TEXT("/Game/BattleWizardPolyart/Animations/Attack03StartAnim.Attack03StartAnim"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> RMBCastOngoingFinder(TEXT("/Game/BattleWizardPolyart/Animations/Attack03MaintainAnim.Attack03MaintainAnim"));

	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> MeleeComboFinder(TEXT("/Game/Player/Mage/Animation/Attack/Standing_Melee_Combo_Attack_Ver__2.Standing_Melee_Combo_Attack_Ver__2"));

	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> MeleeCombo1Finder(TEXT("/Game/Player/Animation/BS_Combo/Mage_Standing_Melee_Combo_Attack_1.Mage_Standing_Melee_Combo_Attack_1"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> MeleeCombo2Finder(TEXT("/Game/Player/Animation/BS_Combo/Mage_Standing_Melee_Combo_Attack_2.Mage_Standing_Melee_Combo_Attack_2"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> MeleeCombo3Finder(TEXT("/Game/Player/Animation/BS_Combo/Mage_Standing_Melee_Combo_Attack_3.Mage_Standing_Melee_Combo_Attack_3"));

	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> FinishAttackFinder(TEXT("/Game/Player/Mage/Animation/Attack/Sword_And_Shield_Slash.Sword_And_Shield_Slash"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> Combo1AttackFinder(TEXT("/Game/Player/Mage/Animation/Attack/Standing_1H_Magic_Attack_01.Standing_1H_Magic_Attack_01"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> Combo2AttackFinder(TEXT("/Game/Player/Mage/Animation/Attack/Standing_1H_Magic_Attack_03.Standing_1H_Magic_Attack_03"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> StandToRollFinder(TEXT("/Game/Player/Mage/Animation/Attack/Stand_To_Roll.Stand_To_Roll"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> HitDownFinder(TEXT("/Game/Player/Mage/Animation/Attack/Falling_Back_Death.Falling_Back_Death"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> HitDownRecover(TEXT("/Game/Player/Mage/Animation/Attack/Stand_Up.Stand_Up"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> DizzyFinder(TEXT("/Game/Player/Mage/Animation/Attack/exhausted_recover.exhausted_recover"));


	//Portrait Version
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> LMBAttackFinder(TEXT("/Game/BattleWizardPolyart/Animations/Attack01Anim.Attack01Anim"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> RMBCastStartFinder(TEXT("/Game/BattleWizardPolyart/Animations/Attack03StartAnim.Attack03StartAnim"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> RMBCastOngoingFinder(TEXT("/Game/BattleWizardPolyart/Animations/Attack03MaintainAnim.Attack03MaintainAnim"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> MeleeComboFinder(TEXT("/Game/Player/Animation/Mage_Standing_Melee_Combo_Attack_Ver__2.Mage_Standing_Melee_Combo_Attack_Ver__2"));

	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> MeleeCombo1Finder(TEXT("/Game/Player/Animation/BS_Combo/Mage_Standing_Melee_Combo_Attack_1.Mage_Standing_Melee_Combo_Attack_1"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> MeleeCombo2Finder(TEXT("/Game/Player/Animation/BS_Combo/Mage_Standing_Melee_Combo_Attack_2.Mage_Standing_Melee_Combo_Attack_2"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> MeleeCombo3Finder(TEXT("/Game/Player/Animation/BS_Combo/Mage_Standing_Melee_Combo_Attack_3.Mage_Standing_Melee_Combo_Attack_3"));

	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> FinishAttackFinder(TEXT("/Game/Player/Animation/Mage_sword_and_shield_slash__4_.Mage_sword_and_shield_slash__4_"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> Combo1AttackFinder(TEXT("/Game/Player/Animation/Mage_Mirror_Standing_1H_Magic_Attack_01.Mage_Mirror_Standing_1H_Magic_Attack_01"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> Combo2AttackFinder(TEXT("/Game/Player/Animation/Mage_Mirror_Standing_1H_Magic_Attack_03.Mage_Mirror_Standing_1H_Magic_Attack_03"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> StandToRollFinder(TEXT("/Game/Player/Animation/Mage_Stand_To_Roll.Mage_Stand_To_Roll"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> HitDownFinder(TEXT("/Game/Player/Animation/Mage_Falling_Back_Death.Mage_Falling_Back_Death"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> HitDownRecover(TEXT("/Game/BattleWizardPolyart/Animations/DieRecoverAnim.DieRecoverAnim"));
	//ConstructorHelpers::FObjectFinder<UAnimSequenceBase> DizzyFinder(TEXT("/Game/BattleWizardPolyart/Animations/DizzyAnim.DizzyAnim"));

	if(LMBAttackFinder.Succeeded())			AnimSequenceLMBAttack = LMBAttackFinder.Object;
	if(RMBCastStartFinder.Succeeded())		AnimSequenceRMBCastStart = RMBCastStartFinder.Object;
	if(RMBCastOngoingFinder.Succeeded())	AnimSequenceRMBCastOngoing = RMBCastOngoingFinder.Object;
	if(MeleeComboFinder.Succeeded())		AnimSequenceMeleeCombo = MeleeComboFinder.Object;
	
	if(MeleeCombo1Finder.Succeeded())		AnimSequenceMeleeCombo1 = MeleeCombo1Finder.Object;
	if(MeleeCombo2Finder.Succeeded())		AnimSequenceMeleeCombo2 = MeleeCombo2Finder.Object;
	if(MeleeCombo3Finder.Succeeded())		AnimSequenceMeleeCombo3 = MeleeCombo3Finder.Object;
	
	if(FinishAttackFinder.Succeeded())		AnimSequenceMeleeFinishAttack = FinishAttackFinder.Object;
	if(Combo1AttackFinder.Succeeded())		AnimSequenceMelee1ComboAttack = Combo1AttackFinder.Object;
	if(Combo2AttackFinder.Succeeded())		AnimSequenceMelee2ComboAttack = Combo2AttackFinder.Object;
	if(StandToRollFinder.Succeeded())		AnimSequenceStandToRoll = StandToRollFinder.Object;
	if(HitDownFinder.Succeeded())			AnimSequenceHitDown = HitDownFinder.Object;
	if(HitDownRecover.Succeeded())			AnimSequenceHitDownRecover = HitDownRecover.Object;
	if(DizzyFinder.Succeeded())				AnimSequenceDizzy = DizzyFinder.Object;

	if (RopeClimbFinder.Succeeded())			AnimSequenceRopeClimb = RopeClimbFinder.Object;
}

void UCPlayerAnimInstance::LMBAttack()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceLMBAttack, "DefaultSlot", 0.25f, 0.25f, 1.3f);
}

void UCPlayerAnimInstance::RMBAttack()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceRMBCastStart, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::RMBCastOngoing()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceRMBCastOngoing, "DefaultSlot", 0.25f, 0.25f, 0.5f);
}

void UCPlayerAnimInstance::MeleeAttackCombo()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceMeleeCombo, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::MeleeAttackCombo1()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceMeleeCombo1, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::MeleeAttackCombo2()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceMeleeCombo2, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::MeleeAttackCombo3()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceMeleeCombo3, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::FinishAttack()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceMeleeFinishAttack, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::Combo1Attack()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceMelee1ComboAttack, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::Combo2Attack()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceMelee2ComboAttack, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::StandToRoll()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceStandToRoll, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::HitDown()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceHitDown, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::HitDownRecover()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceHitDownRecover, "DefaultSlot", 0.25f, 1.25f, 1.f);
}

void UCPlayerAnimInstance::Dizzy()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceDizzy, "DefaultSlot", -1.f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::RopeClimb()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceRopeClimb, "DefaultSlot", 1.f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::NativeInitializeAnimation()
{
	//Super::NativeInitializeAnimation();
	Pawn = TryGetPawnOwner();
	if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(Pawn))
	{
		PC->LMBAttack.BindUFunction(this, FName("LMBAttack"));
		PC->RMBCastStart.BindUFunction(this, FName("RMBAttack"));
		PC->RMBCastOnGoing.BindUFunction(this, FName("RMBCastOngoing"));
		PC->MeleeAttackCombo.BindUFunction(this, FName("MeleeAttackCombo"));
		PC->MeleeAttackCombo1.BindUFunction(this, FName("MeleeAttackCombo1"));
		PC->MeleeAttackCombo2.BindUFunction(this, FName("MeleeAttackCombo2"));
		PC->MeleeAttackCombo3.BindUFunction(this, FName("MeleeAttackCombo3"));
		PC->FinishAttack.BindUFunction(this, FName("FinishAttack"));
		PC->Combo1Attack.BindUFunction(this, FName("Combo1Attack"));
		PC->Combo2Attack.BindUFunction(this, FName("Combo2Attack"));
		PC->StandToRoll.BindUFunction(this, FName("StandToRoll"));
		PC->HitDown.BindUFunction(this, FName("HitDown"));
		PC->HitDownRecover.BindUFunction(this, FName("HitDownRecover"));
		PC->Dizzy.BindUFunction(this, FName("Dizzy"));
		PC->ClimbingRope.BindLambda([&]() {
			RopeClimbing = true;
			UE_LOG(LogTemp, Log, TEXT("Player AnimInstane : RopeClimbing Set True"));
		});
	}
}

void UCPlayerAnimInstance::UpdateProperties(float Delta)
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
