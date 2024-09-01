// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerAnimInstance.h"

UCPlayerAnimInstance::UCPlayerAnimInstance()
{
	Pawn = nullptr;
	IsAir = false;
	MovementSpeed = 0.f;
	ZSpeed = 0.f;
	PawnAnimRadian = 0.f;


	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> LMBAttackFinder(TEXT("/Game/BattleWizardPolyart/Animations/Attack01Anim"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> RMBCastStartFinder(TEXT("/Game/BattleWizardPolyart/Animations/Attack03StartAnim"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> RMBCastOngoingFinder(TEXT("/Game/BattleWizardPolyart/Animations/Attack03MaintainAnim"));

	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> MeleeComboFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Standing_Melee_Combo_Attack_Ver__2"));

	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> MeleeCombo1Finder(TEXT("/Game/Player/Animation/BS_Combo/Mage_Standing_Melee_Combo_Attack_1"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> MeleeCombo2Finder(TEXT("/Game/Player/Animation/BS_Combo/Mage_Standing_Melee_Combo_Attack_2"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> MeleeCombo3Finder(TEXT("/Game/Player/Animation/BS_Combo/Mage_Standing_Melee_Combo_Attack_3"));

	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> FinishAttackFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Sword_And_Shield_Slash"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> Combo1AttackFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Standing_1H_Magic_Attack_01"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> Combo2AttackFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Standing_1H_Magic_Attack_03"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> SheathFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Brute/Sheath_A_Sword"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> DrawFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Brute/Draw_A_Sword"));

	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> StandToRollFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Sprinting_Forward_Roll"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> HitDownFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Falling_Back_Death"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> HitDownRecover(TEXT("/Game/Player/Guard/Animation/Hostile/Stand_Up"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> DizzyFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Injured_Idle"));
	
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> RopeClimbFinder(TEXT("/Game/Player/Guard/Animation/Climbing_A_Rope"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> JumpPointReadyFinder(TEXT("/Game/Player/Guard/Animation/Jump/JumpPoints/JumpReady"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> JumpPointJumpFinder(TEXT("/Game/Player/Guard/Animation/Jump/JumpPoints/Mutant_Jumping"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> JumpPointLandFinder(TEXT("/Game/Player/Guard/Animation/Jump/JumpPoints/Hard_Landing"));
	
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> DieAnimFinder(TEXT("/Game/Player/Guard/Animation/Sword_And_Shield_Death"));

	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> HitReactFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Standing_React_Large_Gut"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> PickUpFinder(TEXT("/Game/Player/Guard/Animation/Picking_Up"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> DrinkFinder(TEXT("/Game/Player/Guard/Animation/Drinking"));

	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> FireFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Rifle/Firing_Rifle__2_"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> BulletChangeFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Rifle/Block_With_Rifle"));
	
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> RifleStaffUltFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Rifle/Toss_Grenade"));

	ConstructorHelpers::FObjectFinder<UAnimSequenceBase>  InitiatePunchComboFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Brute/OraOra/InitiatePunchCombo"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase>  Rush0Finder(TEXT("/Game/Player/Guard/Animation/Hostile/Brute/OraOra/BruteRush_Punch_Combo"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase>  FinishPunchFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Brute/OraOra/FinishPunch"));
	
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase>  Brute_LMB_Combo1Finder(TEXT("/Game/Player/Guard/Animation/Hostile/Brute/LMBCombo/Brute_LMB_Combo1"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase>  Brute_LMB_Combo2Finder(TEXT("/Game/Player/Guard/Animation/Hostile/Brute/LMBCombo/Brute_LMB_Combo2"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase>  Brute_LMB_Combo3Finder(TEXT("/Game/Player/Guard/Animation/Hostile/Brute/LMBCombo/Brute_LMB_Combo3"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase>  Brute_LMB_Combo4Finder(TEXT("/Game/Player/Guard/Animation/Hostile/Brute/LMBCombo/Brute_LMB_Combo4"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase>  Brute_LMB_Combo5Finder(TEXT("/Game/Player/Guard/Animation/Hostile/Brute/LMBCombo/Brute_LMB_Combo5"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase>  Brute_LMB_Combo6Finder(TEXT("/Game/Player/Guard/Animation/Hostile/Brute/LMBCombo/Brute_LMB_Combo6"));

	ConstructorHelpers::FObjectFinder<UAnimSequenceBase>  BattleStaffUltFinder(TEXT("/Game/Player/Guard/Animation/Hostile/Standing_Melee_Combo_Attack_Ver__1"));

	if (LMBAttackFinder.Succeeded())		AnimSequenceLMBAttack = LMBAttackFinder.Object;
	if (RMBCastStartFinder.Succeeded())		AnimSequenceRMBCastStart = RMBCastStartFinder.Object;
	if (RMBCastOngoingFinder.Succeeded())	AnimSequenceRMBCastOngoing = RMBCastOngoingFinder.Object;
	if (MeleeComboFinder.Succeeded())		AnimSequenceMeleeCombo = MeleeComboFinder.Object;
	
	if	(MeleeCombo1Finder.Succeeded())		AnimSequenceMeleeCombo1 = MeleeCombo1Finder.Object;
	if	(MeleeCombo2Finder.Succeeded())		AnimSequenceMeleeCombo2 = MeleeCombo2Finder.Object;
	if	(MeleeCombo3Finder.Succeeded())		AnimSequenceMeleeCombo3 = MeleeCombo3Finder.Object;
	
	if (FinishAttackFinder.Succeeded())		AnimSequenceMeleeFinishAttack = FinishAttackFinder.Object;
	if (Combo1AttackFinder.Succeeded())		AnimSequenceMelee1ComboAttack = Combo1AttackFinder.Object;
	if (Combo2AttackFinder.Succeeded())		AnimSequenceMelee2ComboAttack = Combo2AttackFinder.Object;
	if (SheathFinder.Succeeded())			AnimSequenceSheath = SheathFinder.Object;
	if (DrawFinder.Succeeded())				AnimSequenceDraw = DrawFinder.Object;

	if (StandToRollFinder.Succeeded())		AnimSequenceStandToRoll = StandToRollFinder.Object;
	if (HitDownFinder.Succeeded())			AnimSequenceHitDown = HitDownFinder.Object;
	if (HitDownRecover.Succeeded())			AnimSequenceHitDownRecover = HitDownRecover.Object;
	if (DizzyFinder.Succeeded())			AnimSequenceDizzy = DizzyFinder.Object;

	if (RopeClimbFinder.Succeeded())		AnimSequenceRopeClimb = RopeClimbFinder.Object;

	if (JumpPointReadyFinder.Succeeded())	AnimSequenceJumpPointReady = JumpPointReadyFinder.Object;
	if (JumpPointJumpFinder.Succeeded())	AnimSequenceJumpPointJump = JumpPointJumpFinder.Object;
	if (JumpPointLandFinder.Succeeded())	AnimSequenceJumpPointLand = JumpPointLandFinder.Object;

	if (DieAnimFinder.Succeeded())			AnimSequenceDie = DieAnimFinder.Object;
	if (HitReactFinder.Succeeded())			AnimSequenceHitReact = HitReactFinder.Object;
	if (PickUpFinder.Succeeded())			AnimSequencePickUp = PickUpFinder.Object;
	if (DrinkFinder.Succeeded())			AnimSequenceDrink = DrinkFinder.Object;

	if (FireFinder.Succeeded())				AnimSequenceFire = FireFinder.Object;
	if (BulletChangeFinder.Succeeded())		AnimSequenceBulletChange = BulletChangeFinder.Object;
	if (RifleStaffUltFinder.Succeeded())	AnimSequenceRifleStaffUlt = RifleStaffUltFinder.Object;

	if (InitiatePunchComboFinder.Succeeded())	AnimSequenceInitiatePunchCombo = InitiatePunchComboFinder.Object;
	if (Rush0Finder.Succeeded())	AnimSequenceRush0 = Rush0Finder.Object;
	if (FinishPunchFinder.Succeeded())	AnimSequenceFinishPunch = FinishPunchFinder.Object;

	if (Brute_LMB_Combo1Finder.Succeeded())	AnimSequenceBrute_LMB_Combo1 = Brute_LMB_Combo1Finder.Object;
	if (Brute_LMB_Combo2Finder.Succeeded())	AnimSequenceBrute_LMB_Combo2 = Brute_LMB_Combo2Finder.Object;
	if (Brute_LMB_Combo3Finder.Succeeded())	AnimSequenceBrute_LMB_Combo3 = Brute_LMB_Combo3Finder.Object;
	if (Brute_LMB_Combo4Finder.Succeeded())	AnimSequenceBrute_LMB_Combo4 = Brute_LMB_Combo4Finder.Object;
	if (Brute_LMB_Combo5Finder.Succeeded())	AnimSequenceBrute_LMB_Combo5 = Brute_LMB_Combo5Finder.Object;
	if (Brute_LMB_Combo6Finder.Succeeded())	AnimSequenceBrute_LMB_Combo6 = Brute_LMB_Combo6Finder.Object;

	if (BattleStaffUltFinder.Succeeded())	AnimSequenceBattleStaffUlt = BattleStaffUltFinder.Object;
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

void UCPlayerAnimInstance::Sheath()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceSheath, "UpperBody", 0.25f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::Draw()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceDraw, "UpperBody", 0.25f, 0.25f, 1.f);
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
	float DizzyLength = AnimSequenceDizzy->GetPlayLength();
	GetWorld()->GetTimerManager().SetTimer(DizzyTimerHandle, FTimerDelegate::CreateLambda([&] {
		if (PlayerCharacterStateInterface != nullptr)
		{
			PlayerCharacterStateInterface->SetState(PLAYER_DIZZY, false);
		}
		}), DizzyLength, false);
}

void UCPlayerAnimInstance::RopeClimb()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceRopeClimb, "DefaultSlot", 1.f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::JumpPoint_Ready()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceJumpPointReady, "DefaultSlot", 0.25f, 0.25f, 1.f);
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

void UCPlayerAnimInstance::Drink()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceDrink, "UpperBody", 0.25f, 0.25f, 1.5f);
}

void UCPlayerAnimInstance::Fire()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceFire, "UpperBody", 0.25f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::BulletChange()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceBulletChange, "UpperBody", 0.25f, 0.25f, 2.f);
}

void UCPlayerAnimInstance::InitiatePunchCombo()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceInitiatePunchCombo, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::BruteRush0(bool Initiating)
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceRush0, "UpperBody", Initiating ? 0.25f : 0.05f, Initiating ? 0.25f : 0.05f, 1.f, 1, -1.f, Initiating ? 0.f : 0.23f);
}

void UCPlayerAnimInstance::FinishPunch()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceFinishPunch, "UpperBody", 0.25f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::Brute_LMB_Combo(int32 ComboStack)
{
	float BonusSpeed = 0.f;
	if (Pawn)
	{
		IIPlayerUIController* UIController = Cast<IIPlayerUIController>(Pawn->GetController());
		ItemStat tempStat;
		UIController->EquippedItemStat(tempStat);
		BonusSpeed += tempStat._AttackSpeed;
	}

	switch (ComboStack)
	{
	case(0):
		PlaySlotAnimationAsDynamicMontage(AnimSequenceBrute_LMB_Combo1, "UpperBody", 0.25f, 0.25f, 1.f + BonusSpeed);
		break;
	case(1):
		PlaySlotAnimationAsDynamicMontage(AnimSequenceBrute_LMB_Combo2, "UpperBody", 0.25f, 0.25f, 1.f + BonusSpeed);
		break;
	case(2):
		PlaySlotAnimationAsDynamicMontage(AnimSequenceBrute_LMB_Combo3, "UpperBody", 0.25f, 0.25f, 1.f + BonusSpeed);
		break;
	case(3):
		PlaySlotAnimationAsDynamicMontage(AnimSequenceBrute_LMB_Combo4, "UpperBody", 0.25f, 0.25f, 1.f + BonusSpeed);
		break;
	case(4):
		PlaySlotAnimationAsDynamicMontage(AnimSequenceBrute_LMB_Combo5, "UpperBody", 0.25f, 0.25f, 1.f + BonusSpeed);
		break;
	default:
		PlaySlotAnimationAsDynamicMontage(AnimSequenceBrute_LMB_Combo1, "UpperBody", 0.25f, 0.25f, 1.f + BonusSpeed);
		break;
	}
}

void UCPlayerAnimInstance::BattleStaffUlt()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceBattleStaffUlt, "DefaultSlot", 0.25f, 0.25f, 1.f);
}

void UCPlayerAnimInstance::RifleStaffUlt()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceRifleStaffUlt, "DefaultSlot", 0.25f, 0.25f, 1.f);
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
		PC->Sheath.BindUFunction(this, FName("Sheath"));
		PC->Draw.BindUFunction(this, FName("Draw"));
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
		PC->Drink.BindUFunction(this, FName("Drink"));
		PC->FireRifle.BindUFunction(this, FName("Fire"));
		PC->BulletChange.BindUFunction(this, FName("BulletChange"));

		PC->InitiatePunchCombo.BindUFunction(this, FName("InitiatePunchCombo"));
		PC->BruteRush0.BindUFunction(this, FName("BruteRush0"));
		PC->FinishPunch.BindUFunction(this, FName("FinishPunch"));

		PC->Brute_LMB_Combo.BindUFunction(this, FName("Brute_LMB_Combo"));
		PC->BattleStaffUlt.BindUFunction(this, FName("BattleStaffUlt"));
		PC->RifleStaffUlt.BindUFunction(this, FName("RifleStaffUlt"));
		
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
		Aiming = PlayerCharacterStateInterface->GetState(PLAYER_AIMING);

		BruteMode = PlayerCharacterStateInterface->IsBruteMode();
		AimingYaw = Pawn->GetViewRotation().Pitch;
		if (AimingYaw >= 270.f)
		{
			AimingYaw -= 360.f;
		}
	}
}
