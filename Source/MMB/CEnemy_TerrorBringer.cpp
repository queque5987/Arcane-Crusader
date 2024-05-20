// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy_TerrorBringer.h"
#include "CEnemyAIController_TB.h"
#include "CEnemy_AnimInstance_TB.h"
#include "IEnemyBBState.h"

ACEnemy_TerrorBringer::ACEnemy_TerrorBringer() : Super()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> SMFinder(TEXT("/Game/FourEvilDragonsHP/Meshes/DragonTheTerrorBringer/DragonTheTerrorBringerSK.DragonTheTerrorBringerSK"));
	ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBPFinder(TEXT("/Game/Enemy/TerrorBringer/Animation/BP_EnemyAnimIntance_TB.BP_EnemyAnimIntance_TB"));

	ConstructorHelpers::FObjectFinder<UParticleSystem> FlameThrower(TEXT("/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Fire/P_flamethrower.P_Flamethrower"));

	EnemyAttackEffect.SetNum(MAX_E_ENEMEYATTACK);
	if (FlameThrower.Succeeded()) EnemyAttackEffect[E_ENEMYATTACK_FLAMETHROWER] = FlameThrower.Object;

	if (SMFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SMFinder.Object);
		GetMesh()->SetWorldRotation(FRotator(0.f, -90.f, 0.f));
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	}
	if (AnimBPFinder.Succeeded()) GetMesh()->SetAnimClass(AnimBPFinder.Object->GeneratedClass);
	AIControllerClass = ACEnemyAIController_TB::StaticClass();

	MaxAltitude = 200.f;
	CurrentAltitude = 0.f;
	VirtialAcc = 120.f;
	FlyAcc = 0.5f;
}

void ACEnemy_TerrorBringer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//return;
	UCEnemy_AnimInstance_TB* EA = Cast<UCEnemy_AnimInstance_TB>(GetMesh()->GetAnimInstance());
	if (EA == nullptr) return;
	IIEnemyBBState* AIController = Cast<IIEnemyBBState>(GetController());
	if (AIController == nullptr) return;
	//FVector CurrLoc = GetActorLocation();
	FVector CurrLoc = GetMesh()->GetRelativeLocation();
	if (IsFlying)
	{
		if (CurrentAltitude < MaxAltitude)
		{
			CurrentAltitude += VirtialAcc * DeltaTime;
			GetMesh()->SetRelativeLocation(
				CurrLoc + (
					CurrentAltitude > MaxAltitude ?
					FVector::UpVector * (CurrentAltitude - MaxAltitude) : 
					FVector::UpVector * VirtialAcc * DeltaTime)
			);
		}
	}
	else
	{
		if (CurrentAltitude > 0.f)
		{
			CurrentAltitude -= VirtialAcc * DeltaTime;
			GetMesh()->SetRelativeLocation(
				CurrLoc + (
					CurrentAltitude < 0.f ?
					FVector::UpVector * CurrentAltitude :
					-FVector::UpVector * VirtialAcc * DeltaTime)
			);
			//SetActorLocation(CurrLoc + (CurrentAltitude < 0.f ? FVector::UpVector * CurrentAltitude : -FVector::UpVector * VirtialAcc * DeltaTime));
			//SetActorRelativeLocation(CurrentAltitude < 0.f ? FVector::UpVector * CurrentAltitude : -FVector::UpVector * VirtialAcc * DeltaTime);
			if (CurrentAltitude <= 30.f)
			{
				GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
				EA->SetIsOnAir(false);
			}
			//UE_LOG(LogTemp, Log, TEXT("Getting Down : %f"), CurrentAltitude);
		}
	}
}

float ACEnemy_TerrorBringer::GetFlyMovementSpeed()
{
	return FlyAcc;
}

void ACEnemy_TerrorBringer::SetIsFlying(bool e)
{
	if (e) GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	IsFlying = e;
}

bool ACEnemy_TerrorBringer::FlyTo(FVector Destination, float DeltaSeconds, float AcceptableRadius, float AccWeight)
{
	FVector Dest = FMath::Lerp(GetActorLocation(), Destination, FlyAcc * DeltaSeconds * AccWeight);

	//FVector Direction = Destination - GetActorLocation();
	//FRotator DestHeadingRotation = FRotationMatrix::MakeFromX(Direction).Rotator();

	//FRotator TurnRotation = FMath::RInterpTo(GetActorRotation(), DestHeadingRotation, DeltaSeconds, RotationSpeed*3.f);
	//
	//SetActorRotation(FRotator(GetActorRotation().Pitch,
	//	(FMath::Abs(GetActorRotation().Yaw - DestHeadingRotation.Yaw) > 1.f) ? TurnRotation.Yaw : DestHeadingRotation.Yaw,
	//	GetActorRotation().Roll)
	//);

	//SetActorRotation(FRotationMatrix::MakeFromX(
	//	(Destination - GetActorLocation()).GetSafeNormal()).Rotator()
	//);

	DrawDebugSphere(GetWorld(), GetActorLocation(), 60.f, 32.f, FColor::Cyan, false, 0.2f);
	DrawDebugSphere(GetWorld(), Destination, 60.f, 32.f, FColor::Black, false, 0.2f);

	SetActorLocation(Dest);
	return FVector::Distance(Dest, Destination) < AcceptableRadius ? true : false;
}

bool ACEnemy_TerrorBringer::FlyTo(FRotator DestinedRotation, float DeltaSeconds, float AccWeight)
{
	FVector Dest = GetActorLocation() + DestinedRotation.RotateVector(FVector::ForwardVector) * FlyAcc * AccWeight * 60.f;

	FRotator TurnRotation = FMath::RInterpTo(GetActorRotation(), DestinedRotation, DeltaSeconds, RotationSpeed);

	SetActorRotation(FRotator(GetActorRotation().Pitch,
		(FMath::Abs(GetActorRotation().Yaw - DestinedRotation.Yaw) > 1.f) ? TurnRotation.Yaw : DestinedRotation.Yaw,
		GetActorRotation().Roll)
	);

	SetActorLocation(Dest);

	return true;
}

bool ACEnemy_TerrorBringer::RotateTo(FVector Destination, float DeltaSeconds, float AccWeight)
{
	FVector Direction = (Destination - GetActorLocation()).GetSafeNormal();
	FRotator DirectRot = FRotationMatrix::MakeFromX(Direction).Rotator();
	FRotator CurrRot = GetActorRotation();
	FRotator ToTurnRotation = FMath::RInterpTo(CurrRot, DirectRot, DeltaSeconds, RotationSpeed * AccWeight);
	
	SetActorRotation(FRotator(
		CurrRot.Pitch,
		(FMath::Abs(CurrRot.Yaw - DirectRot.Yaw) > 1.f) ? ToTurnRotation.Yaw : DirectRot.Yaw,
		CurrRot.Roll
	)
	);
	return true;
}

UParticleSystem* ACEnemy_TerrorBringer::GetParticleSystem(int e)
{
	return EnemyAttackEffect.IsValidIndex(e) ? EnemyAttackEffect[e] : nullptr;
}
