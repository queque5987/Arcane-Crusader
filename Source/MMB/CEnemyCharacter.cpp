// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyCharacter.h"
#include "IEnemyBBState.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACEnemyCharacter::ACEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//ConstructorHelpers::FObjectFinder<USkeletalMesh> SMFinder(TEXT("/Game/FourEvilDragonsHP/Meshes/DragonTheNightmare/DragonTheNightmareSK.DragonTheNightmareSK"));
	//ConstructorHelpers::FObjectFinder<UAnimBlueprint>AnimBPFinder(TEXT("/Game/Enemy/Animation/BP_EnemyAnimIntance.BP_EnemyAnimIntance"));
	//if (SMFinder.Succeeded())
	//{
	//	GetMesh()->SetSkeletalMesh(SMFinder.Object);
	//	GetMesh()->SetWorldRotation(FRotator(0.f, -90.f, 0.f));
	//	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	//}
	//GetMesh()->SetAnimClass(AnimBPFinder.Object->GeneratedClass);
	//AIControllerClass = ACEnemyAIController::StaticClass();

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(PlayerAttackChannel, ECollisionResponse::ECR_Ignore);
	//GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	RotationSpeed = 0.8f;
	GetCharacterMovement()->MaxWalkSpeed = 350.f;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetMesh()->SetCollisionObjectType(PlayerAttackChannel);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetCollisionResponseToChannel(PlayerAttackChannel, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void ACEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 1000.f, FColor::Blue);

	if (HP <= 0.f)
	{
		Die();
		return;
	}

	if (bHostile && !bAttacking)
	{
		if (ACEnemyAIController* ECC = Cast<ACEnemyAIController>(GetController()))
		{
			ECC->GetChasingPlayerPos();
			FVector Direction = ECC->GetChasingPlayerPos() - GetActorLocation();
			Direction.Normalize();
			FRotator PlayerHeadingRotation = FRotationMatrix::MakeFromX(Direction).Rotator();

			FRotator TargetRotation = FMath::RInterpTo(GetActorRotation(), PlayerHeadingRotation, DeltaTime, RotationSpeed);

			if (FMath::Abs(GetActorRotation().Yaw - PlayerHeadingRotation.Yaw) > 1.f)
			{
				SetActorRotation(FRotator(GetActorRotation().Pitch, TargetRotation.Yaw, GetActorRotation().Roll));
			}
			
			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Rotate Pawn To Rotation : %s"), *TargetRotation.ToString()));
		}
	}
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
	e ? GetCharacterMovement()->MaxWalkSpeed = 850.f : GetCharacterMovement()->MaxWalkSpeed = 350.f;
}

bool ACEnemyCharacter::AttackHitCheck(int AttackType)
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
		StartLocation = GetMesh()->GetBoneLocation("R_RowerArm");
		EndLocation = GetMesh()->GetBoneLocation("R_Hand");
		Radius = ArmRadius * FScale;
		break;
	case(ENEMY_ATTACK_HEAD):
		StartLocation = GetMesh()->GetBoneLocation("Head");
		EndLocation = GetMesh()->GetBoneLocation("Jaw03");
		Radius = HeadRadius * FScale;
		AdditionalResults.Add(AttackHitCheck(ENEMY_ATTACK_LHAND));
		AdditionalResults.Add(AttackHitCheck(ENEMY_ATTACK_RHAND));
		break;
	case(ENEMY_ATTACK_MOUTH):
		StartLocation = GetMesh()->GetBoneLocation("Head");
		EndLocation = GetMesh()->GetBoneLocation("Jaw03");
		Radius = HeadRadius * FScale;
		break;
	case(ENEMY_ATTACK_LHAND):
		StartLocation = GetMesh()->GetBoneLocation("L_LowerArm");
		EndLocation = GetMesh()->GetBoneLocation("L_Hand");
		Radius = ArmRadius * FScale;
		break;
	case(ENEMY_ATTACK_WINGS):
		StartLocation = GetMesh()->GetBoneLocation("WingClaw1_L");
		EndLocation = GetMesh()->GetBoneLocation("WingClaw2_L");
		Radius = WingClawRadius * FScale;
		AdditionalResults.Add(AttackHitCheck(ENEMY_ATTACK_WINGS_R));
		break;
	case(ENEMY_ATTACK_WINGS_R):
		StartLocation = GetMesh()->GetBoneLocation("WingClaw1_R");
		EndLocation = GetMesh()->GetBoneLocation("WingClaw2_R");
		Radius = WingClawRadius * FScale;
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

	DrawDebugSphere(
		GetWorld(),
		EndLocation,
		Radius,
		16,
		bResult? FColor::Red : FColor::Green,
		false,
		0.8f
	);

	if (bResult)
	{
		if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(HitResult.GetActor()))
		{
			UE_LOG(LogTemp, Log, TEXT("Hit At Actor : %s"), *HitResult.GetActor()->GetName());
			PC->HitDamage(AttackDamage * DamageScale, this, HitResult.Location, AttackPower);
		}
		//return true;
	}
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

			SetLifeSpan(10.0f);
			bIsRagdoll = true;

			//Drop Item
			UCInventoryItemData* D;
			FDropTableRow* R;
			ACDroppedItem* DI;
			AMMBGameModeBase* GM = Cast<AMMBGameModeBase>(GetWorld()->GetAuthGameMode());

			//float RNG;

			if (DropTable == nullptr) return;
			for (FName RowName : DropTable->GetRowNames())
			{
				UE_LOG(LogTemp, Log, TEXT("Row Name : %s"), *RowName.ToString());
				R = DropTable->FindRow<FDropTableRow>(RowName, FString(""));
				if (R == nullptr || FMath::RandRange(0.f, 1.f) < R->ItemDropRate) continue;

				D = NewObject<UCInventoryItemData>(GetWorld(), UCInventoryItemData::StaticClass(), *(R->ItemName.ToString()));
				D->SetIconTexture(R->ItemTexture);
				D->SetItemClass(StaticLoadClass(UObject::StaticClass(), nullptr, *R->ItemClass));
				//D->SetItemClass(GM->GetItemClass(R->ItemClass));
				D->SetItemCount(1);
				D->SetstrName(R->ItemName.ToString());
				D->SetAttackDamage(R->ItemAttackDamage);
				D->SetPrice(R->ItemPrice);
				D->SetRarity(R->Rarity);

				DI = GetWorld()->SpawnActor<ACDroppedItem>(ACDroppedItem::StaticClass(), GetActorLocation(), FRotator::ZeroRotator);
				DI->SetPossessingItem(D);
			}

			//for (int i = 0; i < DropRates.Num(); i++)
			//{
			//	RNG = FMath::RandRange(0.f, 1.f);
			//	if (RNG < DropRates[i])
			//	{
			//		UE_LOG(LogTemp, Log, TEXT("Loss : %f < %f"), RNG, DropRates[i]);
			//	}
			//	if (RNG >= DropRates[i])
			//	{
			//		UE_LOG(LogTemp, Log, TEXT("Win : %f > %f"), RNG, DropRates[i]);
			//		R = DropTable->FindRow<FDropTableRow>(DropItemNames[i], FString(""));
			//		if (R == nullptr) continue;
			//		D = NewObject<UCInventoryItemData>(GetWorld(), UCInventoryItemData::StaticClass(), *(R->ItemName.ToString() + FString::FromInt(i)));
			//		D->SetIconTexture(R->ItemTexture);
			//		D->SetItemClass(GM->GetItemClass(R->ItemClass));
			//		D->SetItemCount(1);
			//		D->SetstrName(R->ItemName.ToString());
			//		D->SetAttackDamage(R->ItemAttackDamage);
			//		D->SetPrice(R->ItemPrice);
			//		D->SetRarity(R->Rarity);

			//		DI = GetWorld()->SpawnActor<ACDroppedItem>(ACDroppedItem::StaticClass(), GetActorLocation(), FRotator::ZeroRotator);
			//		DI->SetPossessingItem(D);
			//	}
			//}
		}
	}

	

	/*if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		FPointDamageEvent PointDmg = *((FPointDamageEvent*)(&DamageEvent));
		{
			GetMesh()->AddImpulseAtLocation(PointDmg.ShotDirection * 5000, PointDmg.HitInfo.ImpactPoint, PointDmg.HitInfo.BoneName);
		}
	}
	if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
	{
		FRadialDamageEvent RadialDmg = *((FRadialDamageEvent const*)(&DamageEvent));
		{
			GetMesh()->AddRadialImpulse(RadialDmg.Origin, RadialDmg.Params.GetMaxRadius(), 100000, ERadialImpulseFalloff::RIF_Linear);
		}
	}*/

	//return true;
}

void ACEnemyCharacter::SetbAttacking(bool e)
{
	SetBBAttacking.ExecuteIfBound(e);
	//UE_LOG(LogTemp, Log, TEXT("Set bAttacking to %d"), e);
	bAttacking = e;
}
