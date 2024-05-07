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

// Called when the game starts or when spawned
void ACProjectile::BeginPlay()
{
	Super::BeginPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Collision Profile Name: %s"), *Collider->GetCollisionProfileName().ToString()));
	//Collider->OnComponentBeginOverlap.AddDynamic(this, &ACProjectile::OnOverlapBegin);
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Actor Rotation: %s"), *GetActorRotation().ToString()));
}

void ACProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PC == nullptr) return;
	if(Cast<ACPlayerCharacter>(PC))
	{
		ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(SweepResult.GetActor());
		if (!IsValid(EC)) return;
		//DrawDebugSphere(GetWorld(), GetActorLocation(), 120.f, 26, FColor::Blue, false, 1.2f);
		UE_LOG(LogTemp, Log, TEXT("Projectile Overlaped Actor : %s"), *SweepResult.GetActor()->GetName());
		UE_LOG(LogTemp, Log, TEXT("Projectile Overlaped Component : %s"), *SweepResult.GetComponent()->GetName());

		EC->HitDamage(TotalDamage, *PC, SweepResult.Location);
		Explode(true);
	}
	else if(ACEnemyCharacter* Attacker = Cast<ACEnemyCharacter>(PC))
	{
		ACPlayerCharacter* EC = Cast<ACPlayerCharacter>(SweepResult.GetActor());
		if (!IsValid(EC)) return;
		DrawDebugSphere(GetWorld(), GetActorLocation(), Collider->GetScaledSphereRadius(), 26, FColor::Red);
		UE_LOG(LogTemp, Log, TEXT("E_Projectile Overlaped Actor : %s"), *SweepResult.GetActor()->GetName());
		UE_LOG(LogTemp, Log, TEXT("E_Projectile Overlaped Component : %s"), *SweepResult.GetComponent()->GetName());

		EC->HitDamage(TotalDamage, Attacker, SweepResult.Location, PlayerReactPower);
		Explode(true);
	}
}

void ACProjectile::Explode(bool Hit)
{
	//ParticleSystemExplode->SetComponentTickEnabled(true);
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
		ParticleSystemExplode->ActivateSystem();
		if (bPenetrate) return;
		ParticleSystemExplode->OnSystemFinished.AddDynamic(this, &ACProjectile::OnExplodeFinished);
		return;
	}
	else Destroy();
}

// Called every frame
void ACProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bSnowball)
	{
		Collider->SetSphereRadius(Collider->GetScaledSphereRadius() * (1 + fSnowball));
	}

	//DrawDebugSphere(GetWorld(), GetActorLocation(), Collider->GetScaledSphereRadius(), 26, FColor::Red);
	/*if (Trail == 0.f)
	{
		UE_LOG(LogTemp, Log, TEXT("***Projecttile Trail 0.f Condition***"));
		return;
	}*/

	ElipsedTime += DeltaTime;
	if (!Launch)
	{
		float PreAcc = tanh(ElipsedTime * AccCoefficient) * MaxSpeedCoefficient;
		//UE_LOG(LogTemp, Log, TEXT("current Acc in tanh : %f"), PreAcc);
		if (FMath::IsNearlyZero(PreAcc)) return;
		FVector CurrentLocation = GetActorLocation();
		FVector DirectionVector = GetActorForwardVector();
		SetActorLocation(CurrentLocation + DirectionVector * PreAcc);
		return;
	}

	FVector CurrentLocation = GetActorLocation();
	FVector DirectionVector = GetActorForwardVector();

	SetActorLocation(CurrentLocation + DirectionVector*Acceleration);
	Trail -= (DirectionVector * Acceleration).Size();
	if (bOnlyDestructOnClock && Trail <= 0.f && LimitTime > ElipsedTime)
	{
		Acceleration = 0.f;
		return;
	}
	if (Trail <= 0.f || (LimitTime > 0.f && LimitTime <= ElipsedTime))
	{
		Explode(false);
		Trail = 0.f;
		Launch = false;
	}
	//UE_LOG(LogTemp, Log, TEXT("%f"), DeltaTime);
	//SetActorRelativeLocation(DirectionVector*Acceleration);
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

void ACProjectile::SetLaunch(ACharacter* SpawnCharacter, UParticleSystem* ProjectileEffect, UParticleSystem* ExplodeEffect, UParticleSystem* SpawnEffect, UParticleSystem* LaunchEffect, float Damage, float RangeLimit, float Acc, float ClockLimit, DELAY_START_PROJECTILE_CONFIGURE* config, bool DoPenetrate, bool OnlyDestructOnClock, bool Snowball, float SnowballAcc)
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

	ParticleSystemSpawnEffect->ActivateSystem();

	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACProjectile::OnOverlapBegin);
	if (config != nullptr) GetWorld()->GetTimerManager().SetTimer(LaunchTimerHandle, this, &ACProjectile::SetLaunchQuick, config->LaunchClock);
	else SetLaunchQuick();
}

void ACProjectile::SetLaunchQuick()
{
	//Collider->SetCollisionResponseToChannel(PlayerAttackChannel, ECollisionResponse::ECR_Overlap);
	Launch = true;
	ParticleSystemLaunchEffect->ActivateSystem();
}

void ACProjectile::SetProjCollisionScale(float e)
{
	Collider->SetSphereRadius(e);
}

