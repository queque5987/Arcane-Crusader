// Fill out your copyright notice in the Description page of Project Settings.


#include "CStaff.h"

ACStaff::ACStaff()
{

	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	Collider = CreateDefaultSubobject<USphereComponent>(FName("Collider"));
	Collider->SetupAttachment(StaticMeshComponent);
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	SetActorRelativeRotation(FRotator(0.f, 0.f, -75.f));
	SetActorRelativeLocation(FVector(0.f, 0.f, 150.f));

	SetActorEnableCollision(true);

	StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	WeaponEffect.SetNum(MAX_E_WEAPONEFFECT);





	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshFinder(TEXT("/Game/BattleWizardPolyart/Meshes/MagicStaffs/Staff02SM.Staff02SM"));
	StaticMeshComponent->SetStaticMesh(StaticMeshFinder.Object);
}

void ACStaff::LMB_Triggered(struct AttackResult& AttackResult)
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	//if (IsValid(PC) && !PC->GetIsAttacking())
	if (!IsValid(PC)) return;
	if (!PC->GetState(PLAYER_ATTACKING) && !PC->GetMovementComponent()->IsFalling())
	{
		UE_LOG(LogTemp, Log, TEXT("LMB Attck Virtual override Called"));
		//PC->SetIsAttacking(true);
		PC->SetState(PLAYER_ATTACKING, true);
		PC->LMBAttack.Execute();

		float AttackRange = 3000.f;
		FHitResult HitResult;
		FVector TargetLocation = PC->CameraComponent->GetComponentLocation() + PC->GetBaseAimRotation().RotateVector(FVector::ForwardVector * AttackRange);
		PC->GetLineTraceResult(HitResult, AttackRange);
		if (HitResult.bBlockingHit)
		{
			TargetLocation = HitResult.Location;
		}

		UStaticMeshSocket* FireSocket = StaticMeshComponent->GetStaticMesh()->FindSocket("FireSocket");
		FVector StartLocation = GetActorLocation() + GetActorRotation().RotateVector(FireSocket->RelativeLocation);
		FVector Direction = (TargetLocation - StartLocation).GetSafeNormal();
		FRotator TargetRotation = FRotator(FMath::RadiansToDegrees(FMath::Asin(Direction.Z)), FMath::RadiansToDegrees(FMath::Atan2(Direction.Y, Direction.X)), 0.f);

//#if WITH_EDITOR
		DrawDebugSphere(GetWorld(), TargetLocation, 30.f, 26, FColor::Green, true, 2.f);
		DrawDebugLine(GetWorld(), StartLocation, TargetLocation, FColor::Green, true, 2.f);
//#endif
		ACProjectile* P = GetWorld()->SpawnActor<ACProjectile>(ACProjectile::StaticClass(), StartLocation, TargetRotation);
	}

	//return AttackResult();
}

void ACStaff::RMB_Triggered(struct AttackResult& AttackResult)
{
	if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner()))
	{
		UE_LOG(LogTemp, Log, TEXT("RMB Attck Triggered Virtual override Called"));
		FVector DebugAimLocation = PC->GetDebugAimLocation();

		UAnimInstance* PlayerAnimInstance = PC->GetMesh()->GetAnimInstance();
		PlayerAnimInstance->OnMontageEnded.AddDynamic(this, &ACStaff::OnCastEnd);

		bool bSecondDimentionalLocator = PC->GetbSecondDimentionalLocator();
		//if (!bSecondDimentionalLocator && !PC->GetIsAttacking())
		if (!bSecondDimentionalLocator && !PC->GetState(PLAYER_ATTACKING))
		{
			//PC->SetIsAttacking(true);
			PC->SetState(PLAYER_ATTACKING, true);
			PC->SetbSecondDimentionalLocator(true);
			PC->RMBCastStart.Execute();
			CastingClock = 0.f;

			FVector NewAimVector = PC->GetBaseAimRotation().RotateVector(FVector::ForwardVector);
			NewAimVector -= FVector(0.f, 0.f, NewAimVector.Z);
			PC->SetDebugAimLocation(PC->GetActorLocation() + NewAimVector * 1000.f);
		}
		else if (FVector::Dist(DebugAimLocation, GetActorLocation()) > 1000.f)
		{
			FVector DirectionVector = (DebugAimLocation - GetActorLocation()).GetSafeNormal();
			PC->SetDebugAimLocation(GetActorLocation() + DirectionVector * 1000.f);
		}
		DrawDebugCircle(GetWorld(), DebugAimLocation, 150.f, 128, FColor::Red, false, -1.f, (uint8)0U, 20.f, FVector(0.f, 1.f, 0.f), FVector(1.f, 0.f, 0.f));
	}
	


	//if (!bSecondDimentionalLocator && !IsAttacking)
	//{
	//	CastingClock = 0.f;
	//	PlayerAnimInstance->OnMontageEnded.AddDynamic(this, &ACPlayerCharacter::OnMontageEnd);
	//	RMBCastStart.Execute();
	//	bSecondDimentionalLocator = true;
	//	IsAttacking = true;

	//	FVector NewAimVector = GetBaseAimRotation().RotateVector(FVector::ForwardVector);
	//	NewAimVector -= FVector(0.f, 0.f, NewAimVector.Z);
	//	DebugAimLocation = GetActorLocation() + NewAimVector * 1000.f;
	//}
	//else if (FVector::Dist(DebugAimLocation, GetActorLocation()) > 1000.f)
	//{
	//	FVector DirectionVector = (DebugAimLocation - GetActorLocation()).GetSafeNormal();
	//	DebugAimLocation = GetActorLocation() + DirectionVector * 1000.f;
	//}
	///*else if (bSecondDimentionalLocator)
	//{
	//	DrawDebugCircle(GetWorld(), DebugAimLocation, 500.f, 128, FColor::Red, false, -1.f, (uint8)0U, 20.f, FVector(0.f, 1.f, 0.f), FVector(1.f, 0.f, 0.f));
	//}*/
	//DrawDebugCircle(GetWorld(), DebugAimLocation, 150.f, 128, FColor::Red, false, -1.f, (uint8)0U, 20.f, FVector(0.f, 1.f, 0.f), FVector(1.f, 0.f, 0.f));

	//return AttackResult();
}

void ACStaff::RMB_Completed(struct AttackResult& AttackResult)
{
	if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner()))
	{
		UAnimInstance* PlayerAnimInstance = PC->GetMesh()->GetAnimInstance();

		if (CastingClock < 1.2f)
		{
			PlayerAnimInstance->StopAllMontages(0.2f);
		}
		PC->SetbSecondDimentionalLocator(false);
		PC->SetState(PLAYER_ATTACKING, false);
		//PC->SetIsAttacking(false);
		CastingClock = -1.f;

		//ParticleSystemAimCircle->SetVisibility(false);

		PlayerAnimInstance->OnMontageEnded.RemoveDynamic(this, &ACStaff::OnCastEnd);
	}
	//return AttackResult();
}

// Called when the game starts or when spawned
void ACStaff::BeginPlay()
{
	Super::BeginPlay();
	/*Collider->OnComponentBeginOverlap.AddDynamic(this, &ACStaff::OnOverlapBegin);*/
}

//void ACStaff::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (ACPlayerCharacter* PlayerCharacter = Cast<ACPlayerCharacter>(OtherActor))
//	{
//		ACPlayerController* PCC = Cast<ACPlayerController>(PlayerCharacter->GetController());
//		PCC->AddInventoryItem(ACStaff::StaticClass());
//		this->Destroy();
//		return;
//		IsEquiped = true;
//		SetActorRelativeRotation(FRotator::ZeroRotator);
//		PlayerCharacter->Equip(*this);
//		Collider->OnComponentBeginOverlap.RemoveDynamic(this, &ACStaff::OnOverlapBegin);
//	}
//}

void ACStaff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CastingClock >= 0.f)
	{
		CastingClock += DeltaTime;
	}
}

void ACStaff::Fire(FVector TargetLocation)
{
	UStaticMeshSocket* FireSocket = StaticMeshComponent->GetStaticMesh()->FindSocket("FireSocket");
	FVector StartLocation = GetActorLocation() + GetActorRotation().RotateVector(FireSocket->RelativeLocation);
	FVector Direction = (TargetLocation - StartLocation).GetSafeNormal();
	FRotator TargetRotation = FRotator(FMath::RadiansToDegrees(FMath::Asin(Direction.Z)), FMath::RadiansToDegrees(FMath::Atan2(Direction.Y, Direction.X)), 0.f);
	//UE_LOG(LogTemp, Log, TEXT("Calculated Rotation: %s"), *TargetRotation.ToString());

	DrawDebugSphere(GetWorld(), TargetLocation, 30.f, 26, FColor::Green, true, 2.f);
	DrawDebugLine(GetWorld(), StartLocation, TargetLocation, FColor::Green, true, 2.f);

	ACProjectile* P = GetWorld()->SpawnActor<ACProjectile>(ACProjectile::StaticClass(), StartLocation, TargetRotation);
}

void ACStaff::OnCastEnd(UAnimMontage* Montage, bool bInterrupted)
{
	if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner()))
	{
		if (CastingClock >= 1.2f)
		{
			PC->RMBCastOnGoing.Execute();
			PC->SetbSecondDimentionalLocator(false);
			CastingClock = -1.f;
			FVector SpawnLocation = PC->GetDebugAimLocation() + FVector(0.f, 0.f, 1000.f);
			//GetWorld()->SpawnActor<ACMeteor>(ACMeteor::StaticClass(), SpawnLocation, FRotator::ZeroRotator);
		}
	}
}

