// Fill out your copyright notice in the Description page of Project Settings.


#include "CProjectile.h"

ACProjectile::ACProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(FName("Collider"));
	Collider->SetSphereRadius(46.f);
	Collider->SetCollisionObjectType(PlayerAttackChannel);

	SetActorEnableCollision(true);
	SetRootComponent(Collider);

	ParticleSystemFireBall = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireBall"));
	ParticleSystemFireBall->SetupAttachment(Collider);

	ParticleSystemExplode = CreateDefaultSubobject<UCParticleSystemExplode>(TEXT("Explode"));
	ParticleSystemExplode->SetAutoActivate(false);
	ParticleSystemExplode->SetupAttachment(Collider);

	ParticleSystemSpawnEffect = CreateDefaultSubobject<UCParticleSystemExplode>(TEXT("Spawn"));
	ParticleSystemSpawnEffect->SetAutoActivate(false);
	ParticleSystemSpawnEffect->SetupAttachment(Collider);

	ParticleSystemLaunchEffect = CreateDefaultSubobject<UCParticleSystemExplode>(TEXT("Launch"));
	ParticleSystemLaunchEffect->SetAutoActivate(false);
	ParticleSystemLaunchEffect->SetupAttachment(Collider);

	ElipsedTime = 0.f;
	Launch = false;
}

void ACProjectile::OnExplodeFinished(UParticleSystemComponent* ParticleSystem)
{
	Destroy();
}

void ACProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ACProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PC == nullptr) return;
	if (bPenetrate)
	{
		SweepActor = Cast<ACharacter>(SweepResult.GetActor());
		HitLocation = SweepResult.Location;
	}
	if(Cast<ACPlayerCharacter>(PC))
	{
		ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(SweepResult.GetActor());
		if (!IsValid(EC)) return;
		UE_LOG(LogTemp, Log, TEXT("Projectile Overlaped Actor : %s"), *SweepResult.GetActor()->GetName());
		UE_LOG(LogTemp, Log, TEXT("Projectile Overlaped Component : %s"), *SweepResult.GetComponent()->GetName());

		//EC->HitDamage(TotalDamage, *PC, SweepResult.Location);
		EC->HitDamage(TotalDamage, *PC, GetActorLocation());
		Explode(true);
	}
	else if(ACEnemyCharacter* Attacker = Cast<ACEnemyCharacter>(PC))
	{
		ACPlayerCharacter* EC = Cast<ACPlayerCharacter>(SweepResult.GetActor());
		if (!IsValid(EC)) return;
		//DrawDebugSphere(GetWorld(), GetActorLocation(), Collider->GetScaledSphereRadius(), 26, FColor::Red);
		UE_LOG(LogTemp, Log, TEXT("E_Projectile Overlaped Actor : %s"), *SweepResult.GetActor()->GetName());
		UE_LOG(LogTemp, Log, TEXT("E_Projectile Overlaped Component : %s"), *SweepResult.GetComponent()->GetName());

		//EC->HitDamage(TotalDamage, Attacker, SweepResult.Location, PlayerReactPower);
		EC->HitDamage(TotalDamage, Attacker, GetActorLocation(), PlayerReactPower);
		Explode(true);
	}
}

void ACProjectile::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SweepActor = nullptr;
}

void ACProjectile::Explode(bool Hit)
{

	if (!bPenetrate)
	{
		ParticleSystemFireBall->Deactivate();
		ParticleSystemFireBall->SetVisibility(false);
		Acceleration = 0.f;
		ParticleSystemExplode->bAutoDestroy = true;
	}
	if (ParticleSystemExplode != nullptr && ParticleSystemExplode->Template != nullptr) ParticleSystemExplode->Template->bAutoDeactivate = true;

	if (Hit)
	{
		if (ExplodeSE != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(),
				ExplodeSE,
				GetActorLocation(), 1.f, 0.65f
			);
		}
		ParticleSystemExplode->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));
		ParticleSystemExplode->ActivateSystem();
		if (bPenetrate) return;
		ParticleSystemExplode->OnSystemFinished.AddDynamic(this, &ACProjectile::OnExplodeFinished);
	}
	else Destroy();
}

void ACProjectile::SweepOnLaunch()
{
	FHitResult HitResult;
	FCollisionObjectQueryParams OQP(Collider->GetCollisionObjectType());

	bool bResult = GetWorld()->SweepSingleByObjectType(
		HitResult,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		OQP,
		Collider->GetCollisionShape()
	);
	if (bResult)
	{
		if (bPenetrate)
		{
			SweepActor = Cast<ACharacter>(HitResult.GetActor());
			HitLocation = GetActorLocation();
		}

		if (Cast<ACPlayerCharacter>(PC))
		{
			ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(HitResult.GetActor());
			if (!IsValid(EC)) return;
			//EC->HitDamage(TotalDamage, *PC, HitResult.Location);
			EC->HitDamage(TotalDamage, *PC, GetActorLocation());
			Explode(true);
		}
		else if (ACEnemyCharacter* Attacker = Cast<ACEnemyCharacter>(PC))
		{
			ACPlayerCharacter* EC = Cast<ACPlayerCharacter>(HitResult.GetActor());
			if (!IsValid(EC)) return;
			//EC->HitDamage(TotalDamage, Attacker, HitResult.Location, PlayerReactPower);
			EC->HitDamage(TotalDamage, Attacker, GetActorLocation(), PlayerReactPower);
			Explode(true);
		}
		//UE_LOG(LogTemp, Log, TEXT("Hit Actor : %s"), *HitResult.GetActor()->GetName());
	}
	//UE_LOG(LogTemp, Log, TEXT("Did Not Hit"));
}

void ACProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), Collider->GetScaledSphereRadius(), 32, FColor::Blue);

	if (bSnowball)
	{
		Collider->SetSphereRadius(Collider->GetScaledSphereRadius() * (1 + fSnowball));
	}

	ElipsedTime += DeltaTime;

	//Projectile Before Move
	if (!Launch)
	{
		float PreAcc = tanh(ElipsedTime * AccCoefficient) * MaxSpeedCoefficient;
		if (FMath::IsNearlyZero(PreAcc)) return;
		FVector CurrentLocation = GetActorLocation();
		FVector DirectionVector = GetActorForwardVector();
		SetActorLocation(CurrentLocation + DirectionVector * PreAcc);
		return;
	}
	//Projectile Move
	FVector CurrentLocation = GetActorLocation();
	FVector DirectionVector = GetActorForwardVector();

	SetActorLocation(CurrentLocation + DirectionVector*Acceleration);
	Trail -= (DirectionVector * Acceleration).Size();

	//Time Expired
	if (bOnlyDestructOnClock && Trail <= 0.f && LimitTime > ElipsedTime)
	{
		Acceleration = 0.f;
		return;
	}
	//Trail Exceeded
	if (Trail <= 0.f || (LimitTime > 0.f && LimitTime <= ElipsedTime))
	{
		Explode(false);
		Trail = 0.f;
		Launch = false;
		return;
	}
	if (bPenetrate && ElipsedTime >= PenetrationTick * (PenetrationTickCounter + 1))
	{
		PenetrationTickCounter++;
		//if (!bPenetrate || SweepActor == nullptr) return;

		SweepOnLaunch();

		//if (Cast<ACPlayerCharacter>(PC))
		//{
		//	ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(SweepActor);
		//	if (!IsValid(EC)) return;
		//	EC->HitDamage(TotalDamage, *PC, HitLocation);
		//	Explode(true);
		//}
		//else if (ACEnemyCharacter* Attacker = Cast<ACEnemyCharacter>(PC))
		//{
		//	ACPlayerCharacter* EC = Cast<ACPlayerCharacter>(SweepActor);
		//	if (!IsValid(EC)) return;
		//	EC->HitDamage(TotalDamage, Attacker, HitLocation, PlayerReactPower);
		//	Explode(true);
		//}
	}
}

void ACProjectile::SetLaunch(UParticleSystem* ProjectileEffect, UParticleSystem* ExplodeEffect, float RangeLimit, float Acc, float LaunchClock, float ClockLimit, bool Snowball, float SnowballAcc)
{
	Trail = RangeLimit;
	Acceleration = Acc;
	LimitTime = ClockLimit;

	bSnowball = Snowball;
	fSnowball = SnowballAcc;

	ParticleSystemFireBall->SetTemplate(ProjectileEffect);
	ParticleSystemExplode->SetTemplate(ExplodeEffect);

	if (LaunchClock > 0) GetWorld()->GetTimerManager().SetTimer(LaunchTimerHandle, this, &ACProjectile::SetLaunchQuick, LaunchClock);
	else SetLaunchQuick();
}

void ACProjectile::SetLaunch(ACharacter* SpawnCharacter, UParticleSystem* ProjectileEffect, UParticleSystem* ExplodeEffect, UParticleSystem* SpawnEffect, UParticleSystem* LaunchEffect, float Damage, float RangeLimit, float Acc, float ClockLimit, DELAY_START_PROJECTILE_CONFIGURE* config, bool DoPenetrate, bool OnlyDestructOnClock, bool Snowball, float SnowballAcc, USoundBase* pExplodeSE, USoundBase* pLaunchSE)
{
	Trail = RangeLimit;
	Acceleration = Acc;
	LimitTime = ClockLimit;
	TotalDamage = Damage;
	PC = SpawnCharacter;

	Collider->SetCollisionObjectType((SpawnCharacter != nullptr) ? PlayerAttackChannel : EnemyAttackChannel);

	bPenetrate = DoPenetrate;
	bOnlyDestructOnClock = OnlyDestructOnClock;
	bSnowball = Snowball;
	fSnowball = SnowballAcc;

	ParticleSystemFireBall->SetTemplate(ProjectileEffect);
	ParticleSystemExplode->SetTemplate(ExplodeEffect);
	ParticleSystemSpawnEffect->SetTemplate(SpawnEffect);
	ParticleSystemLaunchEffect->SetTemplate(LaunchEffect);
	if (config != nullptr)
	{
		AccCoefficient = config->AccCoefficient;
		MaxSpeedCoefficient = config->MaxSpeedCoefficient;
	}

	SetExplodeSE(pExplodeSE);
	SetLaunchSE(pLaunchSE);

	ParticleSystemSpawnEffect->ActivateSystem();

	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACProjectile::OnOverlapBegin);
	Collider->OnComponentEndOverlap.AddDynamic(this, &ACProjectile::OnEndOverlap);
	if (config != nullptr) GetWorld()->GetTimerManager().SetTimer(LaunchTimerHandle, this, &ACProjectile::SetLaunchQuick, config->LaunchClock);
	else SetLaunchQuick();
}

void ACProjectile::SetLaunchQuick()
{
	Launch = true;
	ParticleSystemLaunchEffect->ActivateSystem();
	if (LaunchSE != nullptr) UGameplayStatics::PlaySoundAtLocation(PC->GetWorld(), LaunchSE, GetActorLocation(), 1.f, 0.65f);
	SweepOnLaunch();
}

void ACProjectile::SetProjCollisionScale(float e)
{
	Collider->SetSphereRadius(e);
}

