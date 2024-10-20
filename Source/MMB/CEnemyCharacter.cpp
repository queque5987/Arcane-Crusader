// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyCharacter.h"
#include "IEnemyBBState.h"
#include "DrawDebugHelpers.h"
#include "IPlayerState.h"
#include "CStageGameMode.h"

ACEnemyCharacter::ACEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(PlayerAttackChannel, ECollisionResponse::ECR_Ignore);

	RotationSpeed = 0.8f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	//GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetMesh()->SetCollisionObjectType(PlayerAttackChannel);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetCollisionResponseToChannel(PlayerAttackChannel, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	BoneNameArr.SetNum(ENEMY_ATTACK_BONE_NUM);
}

void ACEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	ACStageGameMode* StageGM = Cast<ACStageGameMode>(GetWorld()->GetAuthGameMode());
	if (StageGM != nullptr)
	{
		StageGM->PlayerDodged.BindUFunction(this, "OnPlayerDodged");
		StageGM->PlayerDodgedEnd.BindUFunction(this, "OnPlayerDodgedEnd");
	}

	GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &ACEnemyCharacter::OnOverlapPlayer);
	GetMesh()->OnComponentEndOverlap.AddDynamic(this, &ACEnemyCharacter::OnOverlapEndPlayer);
}

void ACEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HP <= 0.f)
	{
		Die();
		return;
	}

	//if (bHostile && !bAttacking)
	//{
	//	if (ACEnemyAIController* ECC = Cast<ACEnemyAIController>(GetController()))
	//	{
	//		ECC->GetChasingPlayerPos();
	//		FVector Direction = ECC->GetChasingPlayerPos() - GetActorLocation();
	//		Direction.Normalize();
	//		FRotator PlayerHeadingRotation = FRotationMatrix::MakeFromX(Direction).Rotator();

	//		FRotator TargetRotation = FMath::RInterpTo(GetActorRotation(), PlayerHeadingRotation, DeltaTime, RotationSpeed);

	//		if (FMath::Abs(GetActorRotation().Yaw - PlayerHeadingRotation.Yaw) > 1.f)
	//		{
	//			//SetActorRotation(FRotator(GetActorRotation().Pitch, TargetRotation.Yaw, GetActorRotation().Roll));
	//			//UE_LOG(LogTemp, Log, TEXT("Curr Yaw : %f, Target Yaw : %f"), GetActorRotation().Yaw, TargetRotation.Yaw);
	//			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Rotate Character To Rotation : %s"), *TargetRotation.ToString()));
	//		}
	//	}
	//}

	//Bone Correction
	//GetMesh();
}

// Called to bind functionality to input
void ACEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACEnemyCharacter::SetbHostile(bool e)
{
	bHostile = e;
	if (UCEnemyAnimInstance* EA = Cast<UCEnemyAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		//UE_LOG(LogTemp, Log, TEXT("Set IsHostile to %s"), e ? TEXT("true") : TEXT("false"));
		EA->SetIsHostile(e);
	}
	//e ? GetCharacterMovement()->MaxWalkSpeed = 850.f : GetCharacterMovement()->MaxWalkSpeed = 350.f;
}

bool ACEnemyCharacter::AttackHitCheck(int AttackType, float DamageScale)
{
	bool bResult = false;
	TArray<bool> AdditionalResults;
	FVector StartLocation;
	FVector EndLocation;
	float Radius = 0.f;
	FVector Scale = GetActorScale();
	float FScale = (Scale.X + Scale.Y + Scale.Z) / 3;
	switch (AttackType)
	{
	case(ENEMY_ATTACK_RHAND):
		StartLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_RHAND]);//"R_RowerArm");
		EndLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_RHAND_E]);//"R_Hand");
		Radius = ArmRadius * FScale;
		break;
	case(ENEMY_ATTACK_HEAD):
		StartLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_HEAD]);// "Head");
		EndLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_HEAD_E]);//"Jaw03");
		Radius = HeadRadius * FScale;
		AdditionalResults.Add(AttackHitCheck(ENEMY_ATTACK_LHAND));
		AdditionalResults.Add(AttackHitCheck(ENEMY_ATTACK_RHAND));
		break;
	case(ENEMY_ATTACK_MOUTH):
		StartLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_MOUTH]);//"Head");
		EndLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_MOUTH_E]);//"Jaw03");
		Radius = HeadRadius * FScale;
		break;
	case(ENEMY_ATTACK_LHAND):
		StartLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_LHAND]);//"L_LowerArm");
		EndLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_LHAND_E]);//"L_Hand");
		Radius = ArmRadius * FScale;
		break;
	case(ENEMY_ATTACK_WINGS):
		StartLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_WINGS]);//"WingClaw1_L");
		EndLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_WINGS_E]);//"WingClaw2_L");
		Radius = ArmRadius * FScale;
		AdditionalResults.Add(AttackHitCheck(ENEMY_ATTACK_WINGS_R));
		break;
	case(ENEMY_ATTACK_WINGS_R):
		StartLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_WINGS_R]);//"WingClaw1_R");
		EndLocation = GetMesh()->GetBoneLocation(BoneNameArr[ENEMY_ATTACK_WINGS_R_E]);//"WingClaw2_R");
		Radius = ArmRadius * FScale;
		break;
	}

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	FCollisionObjectQueryParams OQP(ECollisionChannel::ECC_Pawn);

	bResult = GetWorld()->SweepSingleByObjectType(
		HitResult,
		StartLocation,
		EndLocation,
		FQuat::Identity,
		OQP,
		FCollisionShape::MakeSphere(Radius),
		Params
	);

	if (AdditionalResults.Num() > 0)
	{
		for (bool d : AdditionalResults)
		{
			bResult |= d;
		}
	}

	if (bResult)
	{
		if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(HitResult.GetActor()))
		{
			UE_LOG(LogTemp, Log, TEXT("Hit At Actor : %s"), *HitResult.GetActor()->GetName());
			bResult = PC->HitDamage(AttackDamage * DamageScale, this, HitResult.Location, AttackPower);
		}
	}

	//DrawDebugSphere(GetWorld(), StartLocation, Radius, 32, bResult ? FColor::Green : FColor::Red);
	//DrawDebugSphere(GetWorld(), EndLocation, Radius, 32, bResult ? FColor::Green : FColor::Red);

	return bResult;
}

void ACEnemyCharacter::HitDamage(float e, ACharacter& Attacker, FVector HitLocation)
{
	//UE_LOG(LogTemp, Log, TEXT("Took Damage %f"), e);
	if (HitLocation == FVector::ZeroVector) HitLocation == GetActorLocation();
	HP -= e;

	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(&Attacker);
	PC->SetLastDealingEnemy(this);
	PC->ShowDamageUI(e, HitLocation);

	if (!bIsDying && HP < 0.f)
	{
		//PC->MonsterKilledCount(this->StaticClass());
		PC->MonsterKilledCount(this);
		Die();
		PC->SetLastDealingEnemy(nullptr);
	}

	IIEnemyBBState* AIController = Cast<IIEnemyBBState>(GetController());
	if (AIController == nullptr) return;
	AIController->SetTargetDetected(&Attacker);
}

void ACEnemyCharacter::Die()
{
	if (!bIsDying)
	{
		DetachFromControllerPendingDestroy();

		UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
		CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
		SetActorEnableCollision(true);

		if (!bIsRagdoll)
		{
			// Ragdoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetSimulatePhysics(true);
			GetMesh()->WakeAllRigidBodies();
			GetMesh()->bBlendPhysics = true;

			UCharacterMovementComponent* CharacterComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
			if (CharacterComp)
			{
				CharacterComp->StopMovementImmediately();
				CharacterComp->DisableMovement();
				CharacterComp->SetComponentTickEnabled(false);
			}

			SetLifeSpan(18.0f);
			bIsRagdoll = true;

			//Drop Item
			FDropTableRow* R;
			ACDroppedItem* DI;
			AMMBGameModeBase* GM = Cast<AMMBGameModeBase>(GetWorld()->GetAuthGameMode());

			if (DropTable == nullptr) return;
			for (FName RowName : DropTable->GetRowNames())
			{
				UE_LOG(LogTemp, Log, TEXT("Row Name : %s"), *RowName.ToString());
				R = DropTable->FindRow<FDropTableRow>(RowName, FString(""));
				if (R == nullptr || FMath::RandRange(0.f, 1.f) > R->ItemDropRate) continue;

				DI = GetWorld()->SpawnActor<ACDroppedItem>(ACDroppedItem::StaticClass(), GetActorLocation(), FRotator::ZeroRotator);
				UCInventoryItemData* ID = GM->GetItem(FName(R->ItemCode));
				if (ID == nullptr) continue;
				DI->SetPossessingItem(*ID);
			}
		}
	}

}

void ACEnemyCharacter::SetbAttacking(bool e)
{
	if (bAttacking_Comboing && !e)
	{
		bAttacking_Comboing = false;
		return;
	}
	SetBBAttacking.ExecuteIfBound(e);
	bAttacking = e;
}

void ACEnemyCharacter::SetMonsterConfig(MonsterConfigure& Config)
{
	DropTable = Config._DropTable;
	AttackDamage =  Config._AttackDamage;
	WalkSpeed = Config._MaxWalkSpeed;
	HP = Config._HP;
	MaxHP = Config._MaxHP;

}

void ACEnemyCharacter::OnPlayerDodged()
{
	UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
	if (AnimInst == nullptr) return;
	AnimInst->Montage_SetPlayRate(GetCurrentMontage(), 0.2f);
}

void ACEnemyCharacter::OnPlayerDodgedEnd()
{
	UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
	if (AnimInst == nullptr) return;
	AnimInst->Montage_SetPlayRate(GetCurrentMontage(), 1.f);
}

void ACEnemyCharacter::OnOverlapPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IIPlayerState* PC = Cast<IIPlayerState>(OtherActor);
	if (PC != nullptr)
	{
		//UE_LOG(LogTemp, Log, TEXT("PC Name : %s"), *PC->GetName());
		PC->OnOverlapEnemy(this);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Overlapping Actor Is Not Player"));
	}
}

void ACEnemyCharacter::OnOverlapEndPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IIPlayerState* PC = Cast<IIPlayerState>(OtherActor);
	if (PC != nullptr)
	{
		//UE_LOG(LogTemp, Log, TEXT("PC Name : %s"), *PC->GetName());
		PC->OnOverlapEndEnemy(this);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Overlapping End Actor Is Not Player"));
	}
}

void ACEnemyCharacter::SetWalkSpeed(float e)
{
	GetCharacterMovement()->MaxWalkSpeed = e;
}

float ACEnemyCharacter::GetWalkSpeed()
{
	return GetCharacterMovement()->MaxWalkSpeed;
}

ACharacter* ACEnemyCharacter::GetDealingPlayer()
{
	IIEnemyAITactics* AITactics = Cast<IIEnemyAITactics>(GetController());
	if (AITactics == nullptr) return nullptr;
	return AITactics->GetPlayer();
}

bool ACEnemyCharacter::IsBusy()
{
	return bAttacking;
}
