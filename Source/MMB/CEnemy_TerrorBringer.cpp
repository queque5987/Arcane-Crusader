// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy_TerrorBringer.h"
#include "CEnemyAIController_TB.h"
#include "CEnemy_AnimInstance_TB.h"
#include "IEnemyBBState.h"

ACEnemy_TerrorBringer::ACEnemy_TerrorBringer() : Super()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> SMFinder(TEXT("/Game/FourEvilDragonsHP/Meshes/DragonTheTerrorBringer/DragonTheTerrorBringerSK"));
	//ConstructorHelpers::FClassFinder<UAnimBlueprint> AnimBPFinder(TEXT("/Game/Enemy/TerrorBringer/Animation/BP_EnemyAnimIntance_TB"));
	//ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBPFinder(TEXT("AnimBlueprint'/Game/Enemy/TerrorBringer/Animation/BP_EnemyAnimIntance_TB.BP_EnemyAnimIntance_TB_C'"));

	ConstructorHelpers::FObjectFinder<UParticleSystem> FlameThrower(TEXT("/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Fire/P_flamethrower"));

	EnemyAttackEffect.SetNum(MAX_E_ENEMEYATTACK);
	if (FlameThrower.Succeeded()) EnemyAttackEffect[E_ENEMYATTACK_FLAMETHROWER] = FlameThrower.Object;

	if (SMFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SMFinder.Object);
		GetMesh()->SetWorldRotation(FRotator(0.f, -90.f, 0.f));
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
		FString MatAddres = TEXT("/Game/FourEvilDragonsPBR/Materials/DragonTheTerrorBringer/AlbedoMat_Inst");
		switch (FMath::RandRange(0, 3))
		{
		case(0):
			break;
		case(1):
			MatAddres = TEXT("/Game/FourEvilDragonsPBR/Materials/DragonTheTerrorBringer/BlueMat_Inst");
			break;
		case(2):
			MatAddres = TEXT("/Game/FourEvilDragonsPBR/Materials/DragonTheTerrorBringer/GreenMat_Inst");
			break;
		case(3):
			MatAddres = TEXT("/Game/FourEvilDragonsPBR/Materials/DragonTheTerrorBringer/RedMat_Inst");
			break;
		default:
			break;
		}
		ConstructorHelpers::FObjectFinder<UMaterialInstance> Mat0Finder(*MatAddres);
		if (Mat0Finder.Succeeded())
		{
			GetMesh()->SetMaterial(0, Mat0Finder.Object);
		}
	}
	//if (AnimBPFinder.Succeeded()) GetMesh()->SetAnimClass(AnimBPFinder.Class);// .Object->GeneratedClass);
	AIControllerClass = ACEnemyAIController_TB::StaticClass();

	MaxAltitude = 200.f;
	CurrentAltitude = 0.f;
	VirtialAcc = 120.f;
	FlyAcc = 0.5f;
}

void ACEnemy_TerrorBringer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FString AnimBPAdderss = "Class'/Game/Enemy/TerrorBringer/Animation/BP_EnemyAnimIntance_TB.BP_EnemyAnimIntance_TB_C'";
	UClass* tempAnimBP = LoadObject<UClass>(nullptr, *AnimBPAdderss);
	if (!tempAnimBP) return;
	GetMesh()->SetAnimInstanceClass(tempAnimBP);
}

void ACEnemy_TerrorBringer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UCEnemy_AnimInstance_TB* EA = Cast<UCEnemy_AnimInstance_TB>(GetMesh()->GetAnimInstance());
	if (EA == nullptr) return;
	IIEnemyBBState* AIController = Cast<IIEnemyBBState>(GetController());
	if (AIController == nullptr) return;
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
			if (CurrentAltitude <= 30.f)
			{
				GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
				EA->SetIsOnAir(false);
			}
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

void ACEnemy_TerrorBringer::SetMonsterConfig(MonsterConfigure& Config)
{
	Super::SetMonsterConfig(Config);
	FlyAcc = Config._FlyAcc;
	VirtialAcc = Config._VirticalAcc;
}
