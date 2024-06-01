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
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> JumpPointReadyFinder(TEXT("/Game/Player/Guard/Animation/Jump/JumpPoints/JumpReady.JumpReady"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> JumpPointJumpFinder(TEXT("/Game/Player/Guard/Animation/Jump/JumpPoints/Mutant_Jumping.Mutant_Jumping"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> JumpPointLandFinder(TEXT("/Game/Player/Guard/Animation/Jump/JumpPoints/Hard_Landing.Hard_Landing"));
	
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> DieAnimFinder(TEXT("/Game/Player/Guard/Animation/Sword_And_Shield_Death.Sword_And_Shield_Death"));

	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> HitReactFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Standing_React_Large_Gut.Standing_React_Large_Gut"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> PickUpFinder(TEXT("/Game/Player/Guard/Animation/Picking_Up.Picking_Up"));
	

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

	if (JumpPointReadyFinder.Succeeded()) AnimSequenceJumpPointReady = JumpPointReadyFinder.Object;
	if (JumpPointJumpFinder.Succeeded()) AnimSequenceJumpPointJump = JumpPointJumpFinder.Object;
	if (JumpPointLandFinder.Succeeded()) AnimSequenceJumpPointLand = JumpPointLandFinder.Object;

	if (DieAnimFinder.Succeeded()) AnimSequenceDie = DieAnimFinder.Object;
	if (HitReactFinder.Succeeded()) AnimSequenceHitReact = HitReactFinder.Object;
	if (PickUpFinder.Succeeded()) AnimSequencePickUp = PickUpFinder.Object;
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
	float BonusSpeed = 0.f;
	if (Pawn)
	{
		IIPlayerUIController* UIController = Cast<IIPlayerUIController>(Pawn->GetController());
		ItemStat tempStat;
		UIController->EquippedItemStat(tempStat);
		BonusSpeed += tempStat._AttackSpeed;
	}
	PlaySlotAnimationAsDynamicMontage(AnimSequenceMeleeCombo, "DefaultSlot", 0.25f, 0.25f, 1.f + BonusSpeed);
}

void UCPlayerAnimInstance::MeleeAttackCombo1()
{
	float BonusSpeed = 0.f;
	if (Pawn)
	{
		IIPlayerUIController* UIController = Cast<IIPlayerUIController>(Pawn->GetController());
		ItemStat tempStat;
		UIController->EquippedItemStat(tempStat);
		BonusSpeed += tempStat._AttackSpeed;
	}
	PlaySlotAnimationAsDynamicMontage(AnimSequenceMeleeCombo1, "DefaultSlot", 0.25f, 0.25f, 1.f + BonusSpeed);
}

void UCPlayerAnimInstance::MeleeAttackCombo2()
{
	float BonusSpeed = 0.f;
	if (Pawn)
	{
		IIPlayerUIController* UIController = Cast<IIPlayerUIController>(Pawn->GetController());
		ItemStat tempStat;
		UIController->EquippedItemStat(tempStat);
		BonusSpeed += tempStat._AttackSpeed;
	}
	PlaySlotAnimationAsDynamicMontage(AnimSequenceMeleeCombo2, "DefaultSlot", 0.25f, 0.25f, 1.f + BonusSpeed);
}

void UCPlayerAnimInstance::MeleeAttackCombo3()
{
	float BonusSpeed = 0.f;
	if (Pawn)
	{
		IIPlayerUIController* UIController = Cast<IIPlayerUIController>(Pawn->GetController());
		ItemStat tempStat;
		UIController->EquippedItemStat(tempStat);
		BonusSpeed += tempStat._AttackSpeed;
	}
	PlaySlotAnimationAsDynamicMontage(AnimSequenceMeleeCombo3, "DefaultSlot", 0.25f, 0.25f, 1.f + BonusSpeed);
}

void UCPlayerAnimInstance::FinishAttack()
{
	float BonusSpeed = 0.f;
	if (Pawn)
	{
		IIPlayerUIController* UIController = Cast<IIPlayerUIController>(Pawn->GetController());
		ItemStat tempStat;
		UIController->EquippedItemStat(tempStat);
		BonusSpeed += tempStat._AttackSpeed;
	}
	PlaySlotAnimationAsDynamicMontage(AnimSequenceMeleeFinishAttack, "DefaultSlot", 0.25f, 0.25f, 1.f + BonusSpeed);
}

void UCPlayerAnimInstance::Combo1Attack()
{
	float BonusSpeed = 0.f;
	if (Pawn)
	{
		IIPlayerUIController* UIController = Cast<IIPlayerUIController>(Pawn->GetController());
		ItemStat tempStat;
		UIController->EquippedItemStat(tempStat);
		BonusSpeed += tempStat._AttackSpeed;
	}
	PlaySlotAnimationAsDynamicMontage(AnimSequenceMelee1ComboAttack, "DefaultSlot", 0.25f, 0.25f, 1.f + BonusSpeed);
}

void UCPlayerAnimInstance::Combo2Attack()
{
	float BonusSpeed = 0.f;
	if (Pawn)
	{
		IIPlayerUIController* UIController = Cast<IIPlayerUIController>(Pawn->GetController());
		ItemStat tempStat;
		UIController->EquippedItemStat(tempStat);
		BonusSpeed += tempStat._AttackSpeed;
	}
	PlaySlotAnimationAsDynamicMontage(AnimSequenceMelee2ComboAttack, "DefaultSlot", 0.25f, 0.25f, 1.f + BonusSpeed);
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

void UCPlayerAnimInstance::JumpPoint_Ready()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceJumpPointReady, "DefaultSlot", 0.25f, 0.25f, 1.f);
	//e = AnimSequenceJumpPointReady->GetPlayLength();
}

void UCPlayerAnimInstance::JumpPoint_Jump(float e)
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceJumpPointJump, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::JumpPoint_Land()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceJumpPointLand, "UpperBody", 0.25f, 0.25f, 1.f);
	float e = AnimSequenceJumpPointLand->GetPlayLength();
}

void UCPlayerAnimInstance::Die()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceDie, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::HitReact()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceHitReact, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::PickUp()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequencePickUp, "UpperBody", 0.25f, 0.25f, 1.f);
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
		PC->ClimbingRope.BindLambda([&](bool b) {
			RopeClimbing = b;
			UE_LOG(LogTemp, Log, TEXT("Player AnimInstane : RopeClimbing Set True"));
		});
		PC->JumpPointReady.BindUFunction(this, FName("JumpPoint_Ready"));
		PC->JumpPointJump.BindUFunction(this, FName("JumpPoint_Jump"));
		PC->JumpPointLand.BindUFunction(this, FName("JumpPoint_Land"));
		PC->Die.BindUFunction(this, FName("Die"));
		PC->HitReact.BindUFunction(this, FName("HitReact"));
		PC->PickUp.BindUFunction(this, FName("PickUp"));
		PlayerCharacterStateInterface = Cast<IIPlayerState>(PC);
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

		if (PlayerCharacterStateInterface == nullptr) return;
		Died = PlayerCharacterStateInterface->GetState(PLAYER_DIED);
		bHitDown = PlayerCharacterStateInterface->GetState(PLAYER_RAGDOLL) ||
			PlayerCharacterStateInterface->GetState(PLAYER_CANGETUP);
	}
}
