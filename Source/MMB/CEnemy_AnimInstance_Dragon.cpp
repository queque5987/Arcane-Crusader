#include "CEnemy_AnimInstance_Dragon.h"
#include "CEnemy_Dragon.h"

UCEnemy_AnimInstance_Dragon::UCEnemy_AnimInstance_Dragon() : Super()
{
	FallCounter = 0.f;

	ConstructorHelpers::FObjectFinder<UAnimSequence> FallFinder(TEXT("/Game/Enemy/MountainDragon/Animations/ANIM_MOUNTAIN_DRAGON_falling"));
	ConstructorHelpers::FObjectFinder<UAnimSequence> StationryToFallFinder(TEXT("/Game/Enemy/MountainDragon/Animations/ANIM_MOUNTAIN_DRAGON_FlyStationaryToFall"));
	ConstructorHelpers::FObjectFinder<UAnimSequence> StationaryToLandinder(TEXT("/Game/Enemy/MountainDragon/Animations/ANIM_MOUNTAIN_DRAGON_FlyStationaryToLanding"));
	ConstructorHelpers::FObjectFinder<UAnimSequence> ClawComboFinder(TEXT("/Game/Enemy/MountainDragon/Animations/ANIM_MOUNTAIN_DRAGON_ClawsAttack2HitComboForward"));
	ConstructorHelpers::FObjectFinder<UAnimSequence> LeftClawFinder(TEXT("/Game/Enemy/MountainDragon/Animations/ANIM_MOUNTAIN_DRAGON_LeftClawsAttackForward"));
	ConstructorHelpers::FObjectFinder<UAnimSequence> RightClawFinder(TEXT("/Game/Enemy/MountainDragon/Animations/ANIM_MOUNTAIN_DRAGON_rightClawsAttackForward"));
	ConstructorHelpers::FObjectFinder<UAnimSequence> BiteFinder(TEXT("/Game/Enemy/MountainDragon/Animations/ANIM_MOUNTAIN_DRAGON_bite"));
	ConstructorHelpers::FObjectFinder<UAnimSequence> BiteGraspFinder(TEXT("/Game/Enemy/MountainDragon/Animations/ANIM_MOUNTAIN_DRAGON_biteGrabThrow"));
	ConstructorHelpers::FObjectFinder<UAnimSequence> FireBallFinder(TEXT("/Game/Enemy/MountainDragon/Animations/ANIM_MOUNTAIN_DRAGON_spitFireBall"));
	ConstructorHelpers::FObjectFinder<UAnimSequence> FireBreathFinder(TEXT("/Game/Enemy/MountainDragon/Animations/ANIM_MOUNTAIN_DRAGON_spreadFire"));

	ConstructorHelpers::FObjectFinder<UAnimSequence> TurnLFinder(TEXT("/Game/Enemy/MountainDragon/Animations/ANIM_MOUNTAIN_DRAGON_turn90Left"));
	ConstructorHelpers::FObjectFinder<UAnimSequence> TurnRFinder(TEXT("/Game/Enemy/MountainDragon/Animations/ANIM_MOUNTAIN_DRAGON_turn90Right"));

	ConstructorHelpers::FObjectFinder<UAnimSequence> SpitFireBallFinder(TEXT("/Game/Enemy/MountainDragon/Animations/ANIM_MOUNTAIN_DRAGON_spitFireBall"));
	ConstructorHelpers::FObjectFinder<UAnimSequence> BreathFireFinder(TEXT("/Game/Enemy/MountainDragon/Animations/ANIM_MOUNTAIN_DRAGON_spreadFire"));

	if (FallFinder.Succeeded())				AnimSequenceFall = FallFinder.Object;
	if (StationryToFallFinder.Succeeded())	AnimSequenceStationayToFall = StationryToFallFinder.Object;
	if (StationaryToLandinder.Succeeded())	AnimSequenceStationayToLand = StationaryToLandinder.Object;

	if (LeftClawFinder.Succeeded())			AnimSequenceLeftClaw = LeftClawFinder.Object;
	if (ClawComboFinder.Succeeded())		AnimSequenceClawCombo = ClawComboFinder.Object;
	if (RightClawFinder.Succeeded())		AnimSequenceRightClaw = RightClawFinder.Object;
	if (BiteFinder.Succeeded())				AnimSequenceBite = BiteFinder.Object;
	if (BiteGraspFinder.Succeeded())		AnimSequenceBiteGrasp = BiteGraspFinder.Object;
	if (FireBallFinder.Succeeded())			AnimSequenceFireBall = FireBallFinder.Object;
	if (FireBreathFinder.Succeeded())		AnimSequenceFireBreath = FireBreathFinder.Object;

	if (TurnLFinder.Succeeded())			AnimSequenceTurnLeft = TurnLFinder.Object;
	if (TurnRFinder.Succeeded())			AnimSequenceTurnRight = TurnRFinder.Object;

	if (SpitFireBallFinder.Succeeded())		AnimSequenceSpitFireBall = SpitFireBallFinder.Object;
	if (BreathFireFinder.Succeeded())		AnimSequenceBreathFire = BreathFireFinder.Object;

	PlayingSequence = false;
}

void UCEnemy_AnimInstance_Dragon::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	ACEnemy_Dragon* D = Cast<ACEnemy_Dragon>(TryGetPawnOwner());
	if (D != nullptr)
	{
		D->Delegate_SetPlayingSequence.BindUFunction(this, TEXT("SetPlayingSequence"));
		D->Delegate_Fall.BindLambda([&] {
			bFalling = true;
			if (TryGetPawnOwner() != nullptr)
			{
				IIEnemyBBState* BBState = Cast<IIEnemyBBState>(TryGetPawnOwner()->GetController());
				BBState->SetbFalling(true);
			}
			PlaySlotAnimationAsDynamicMontage(AnimSequenceFall, TEXT("DefaultSlot"), 0.25f, 0.25f, 1.f, 30);
			});
		D->Delegate_StationaryToFall.BindLambda([&] {
			PlaySlotAnimationAsDynamicMontage(AnimSequenceStationayToFall, TEXT("DefaultSlot"), 0.25f, 0.25f, 5.f);
			});
		D->Delegate_StationaryToLand.BindLambda([&] {
			PlaySlotAnimationAsDynamicMontage(AnimSequenceStationayToLand, TEXT("DefaultSlot"), 0.25f, 0.25f, 1.f, 1, -1.f, 1.45f);
			});
		D->Delegate_ClawComboAttack.BindLambda([&] {
			PlaySlotAnimationAsDynamicMontage(AnimSequenceClawCombo, TEXT("DefaultSlot"), 0.25f, 0.25f); });
		D->Delegate_LClawAttack.BindLambda([&] {
			PlaySlotAnimationAsDynamicMontage(AnimSequenceLeftClaw, TEXT("DefaultSlot"), 0.25f, 0.25f); });
		D->Delegate_RClawAttack.BindLambda([&] {
			PlaySlotAnimationAsDynamicMontage(AnimSequenceRightClaw, TEXT("DefaultSlot"), 0.25f, 0.25f); });
		D->Delegate_BiteAttack.BindLambda([&] {
			PlaySlotAnimationAsDynamicMontage(AnimSequenceBite, TEXT("DefaultSlot"), 0.25f, 0.25f); });
		D->Delegate_BiteGrasp.BindLambda([&] {
			PlaySlotAnimationAsDynamicMontage(AnimSequenceBiteGrasp, TEXT("DefaultSlot"), 0.25f, 0.25f, 1.f, 1, -1.f, 0.36f); });
		D->Delegate_FireBallAttack.BindLambda([&] {
			PlaySlotAnimationAsDynamicMontage(AnimSequenceFireBall, TEXT("DefaultSlot"), 0.25f, 0.25f); });
		D->Delegate_FireBreathAttack.BindLambda([&] {
			PlaySlotAnimationAsDynamicMontage(AnimSequenceFireBreath, TEXT("DefaultSlot"), 0.25f, 0.25f); });
		D->Delegate_TurnLeft.BindLambda([&] {
			PlaySlotAnimationAsDynamicMontage(AnimSequenceTurnLeft, TEXT("DefaultSlot"), 0.25f, 0.25f); });
		D->Delegate_TurnRight.BindLambda([&] {
			PlaySlotAnimationAsDynamicMontage(AnimSequenceTurnRight, TEXT("DefaultSlot"), 0.25f, 0.25f); });
		D->Delegate_FireBallAttack.BindLambda([&] {
			PlaySlotAnimationAsDynamicMontage(AnimSequenceSpitFireBall, TEXT("UpperSlot"), 0.25f, 0.25f); });
		D->Delegate_FireBreathAttack.BindLambda([&] {
			PlaySlotAnimationAsDynamicMontage(AnimSequenceBreathFire, TEXT("UpperSlot"), 0.25f, 0.25f); });

	}
}

void UCEnemy_AnimInstance_Dragon::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UCEnemy_AnimInstance_Dragon::UpdateProperties(float Delta)
{
	Super::UpdateProperties(Delta);

	if (bFalling) FallCounter += Delta;
	if (FallCounter > 1.5f)
	{
		//Land Init
		FHitResult HitResult;
		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.AddIgnoredActor(GetOwningActor());
		GetWorld()->LineTraceSingleByChannel(
			HitResult,
			GetOwningActor()->GetActorLocation(),
			GetOwningActor()->GetActorLocation() - GetOwningActor()->GetActorUpVector() * 500.f,
			ECC_PhysicsBody,
			CollisionQueryParams
			);

		//DrawDebugSphere(GetWorld(), GetOwningActor()->GetActorLocation() - GetOwningActor()->GetActorUpVector() * 1500.f, 300.f, 32, FColor::Red);
		if (HitResult.bBlockingHit)
		{
			FallCounter = 0.f;
			bFalling = false;
			if (TryGetPawnOwner() != nullptr)
			{
				IIEnemyBBState* BBState = Cast<IIEnemyBBState>(TryGetPawnOwner()->GetController());
				//BBState->SetbFalling(true);
				BBState->SetbBusy(false);
			}
			GetWorld()->GetTimerManager().ClearTimer(FallSafeTimer);
			PlaySlotAnimationAsDynamicMontage(AnimSequenceStationayToFall, TEXT("DefaultSlot"), 0.25f, 0.25f, -5.f, 1, -1.f, 5.3f);
		}
	}
}

void UCEnemy_AnimInstance_Dragon::SetPlayingSequence(bool e)
{
	if (e != PlayingSequence)
	{
		if (!e)
		{
			GetWorld()->GetTimerManager().SetTimer(FallSafeTimer, FTimerDelegate::CreateLambda([&] {
				FallCounter = 0.f;
				}), 1.2f, false);
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(FallSafeTimer);
		}
	}

	PlayingSequence = e;
}
