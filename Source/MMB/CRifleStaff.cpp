// Fill out your copyright notice in the Description page of Project Settings.


#include "CRifleStaff.h"
#include "PCH.h"
#include "Sound/SoundCue.h"
#include "CPlayerCharacter.h"
#include "IPlayerUIController.h"
#include "IPlayerState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/AudioComponent.h"

ACRifleStaff::ACRifleStaff()
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
	WeaponSoundEffect.SetNum(MAX_SE_WEAPON);

	ConstructorHelpers::FObjectFinder<UStaticMesh>		BattleStaffMeshFinder(TEXT("/Game/BattleWizardPolyart/Meshes/MagicStaffs/Staff02SM"));
// Effect - Adjust Later

	ConstructorHelpers::FObjectFinder<UParticleSystem>	Rifle_Type_A_Projectilie(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/combat/P_ProjectileLob_Bomblet_Untyped"));
	ConstructorHelpers::FObjectFinder<UParticleSystem>	Rifle_TYPE_A_Spawn(TEXT("/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Sparks/P_Sparks_C"));
	ConstructorHelpers::FObjectFinder<UParticleSystem>  Rifle_TYPE_A_Explode(TEXT("/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Destruction/P_Destruction_Building_A"));
	ConstructorHelpers::FObjectFinder<UParticleSystem>	Rifle_TYPE_A_LAUNCH(TEXT("/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Hit/P_Default"));
	
	if (Rifle_Type_A_Projectilie.Succeeded())	WeaponEffect[E_RIFLE_TYPE_A_PROJECTILE]		= Rifle_Type_A_Projectilie.Object;
	if (Rifle_TYPE_A_Spawn.Succeeded())			WeaponEffect[E_RIFLE_SPAWN_EFFECT]			= Rifle_TYPE_A_Spawn.Object;
	if (Rifle_TYPE_A_Explode.Succeeded())		WeaponEffect[E_RIFLE_EXPLODE_EFFECT]		= Rifle_TYPE_A_Explode.Object;
	if (Rifle_TYPE_A_LAUNCH.Succeeded())		WeaponEffect[E_RIFLE_LAUNCH_EFFECT]			= Rifle_TYPE_A_LAUNCH.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem>	WeaponAttackTrail(TEXT("/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Sparks/P_Sparks_A"));

	if (BattleStaffMeshFinder.Succeeded()) StaticMeshComponent->SetStaticMesh(BattleStaffMeshFinder.Object);
	if (WeaponAttackTrail.Succeeded()) WeaponEffect[E_MELLEWEAPON_ATTACK_TRAIL] = WeaponAttackTrail.Object;

	ConstructorHelpers::FObjectFinder<USoundBase> Type_A_Charge(TEXT("/Game/Resources/Sound/Rifle/power-charge-6798"));
	ConstructorHelpers::FObjectFinder<USoundBase> Type_A_Shot(TEXT("/Game/Resources/Sound/Rifle/gun-shots-from-a-distance-6-39721"));
	ConstructorHelpers::FObjectFinder<USoundBase> Type_A_Hit(TEXT("/Game/Resources/Sound/Rock/rock-destroy-6409"));
	ConstructorHelpers::FObjectFinder<USoundBase> Type_B_Shot(TEXT("/Game/Resources/Sound/Rifle/shotgun-firing-4-6746"));

	if (Type_A_Charge.Succeeded())	WeaponSoundEffect[SE_RIFLE_TYPE_A_CHARGE] = Type_A_Charge.Object;
	if (Type_A_Shot.Succeeded())	WeaponSoundEffect[SE_RIFLE_TYPE_A_SHOT] = Type_A_Shot.Object;
	if (Type_A_Hit.Succeeded())		WeaponSoundEffect[SE_RIFLE_TYPE_A_Hit] = Type_A_Hit.Object;
	if (Type_B_Shot.Succeeded())	WeaponSoundEffect[SE_RIFLE_TYPE_B_SHOT] = Type_B_Shot.Object;
	

	FireSocketEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireSocketEffet"));
	FireSocketEffectComponent->SetupAttachment(StaticMeshComponent);
	FireSocketEffectComponent->AttachToComponent(StaticMeshComponent, FAttachmentTransformRules::KeepRelativeTransform, "FireSocket");
	FireSocketEffectComponent->SetTemplate(WeaponAttackTrail.Object);
	FireSocketEffectComponent->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	FireSocketEffectComponent->SetRelativeLocation(FVector(0.f, 100.f, 0.f));
	FireSocketEffectComponent->SetAutoActivate(false);

	tempDamage0 = 2.8f;
	tempDamage1 = 3.2f;
	tempDamage2 = 3.5f;

	//Collider->OnComponentBeginOverlap.AddDynamic(this, &ACRifleStaff::OnPickUp);

	UStaticMesh* SM = StaticMeshComponent->GetStaticMesh();
	if (SM != nullptr) FireSocket = SM->FindSocket("FireSocket");

}

void ACRifleStaff::LMB_Triggered(AttackResult& AttackResult)
{
	IIPlayerState* PS = Cast<IIPlayerState>(GetOwner());
	if (PS == nullptr) return;

	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (!IsValid(PC)) return;

	if (!PS->GetState(PLAYER_AIMING)) return;

	if (AttackCoolDown < ConstAttackCoolDown) return;

	PS->SetState(PLAYER_ATTACKING, true);
	switch (BulletType)
	{
	case(0)://Rifle Bullet
		SetLMBLock(true);
		AttackResult.StaminaUsed = 0.08f;
		break;
	case(1)://ShotGun Bullet
		AttackResult.StaminaUsed = 12.f;
		PC->FireRifle.ExecuteIfBound();
		for (int i = 0; i < 20; i++)
		{
			BuckShot(i);
		}
		AttackCoolDown = 0.f;
		break;
	default:
		break;
	}
}

void ACRifleStaff::LMB_Completed(AttackResult& AttackResult)
{
	IIPlayerState* PS = Cast<IIPlayerState>(GetOwner());
	if (PS == nullptr) return;

	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (!IsValid(PC)) return;

	if (!PS->GetState(PLAYER_AIMING)) return;

	if (AttackCoolDown < ConstAttackCoolDown) return;

	PS->SetState(PLAYER_ATTACKING, true);
	switch (BulletType)
	{
		//Rifle Bullet
	case(0):
		AttackResult.StaminaUsed = 5.f;
		PC->FireRifle.ExecuteIfBound();
		Fire();
		SetLMBLock(false);
		AttackCoolDown = 0.f;
		break;
		//ShotGun Bullet
	case(1):
		AttackResult.StaminaUsed = 12.f;
		PC->FireRifle.ExecuteIfBound();
		for (int i = 0; i < 20; i++)
		{
			BuckShot(i);
		}
		AttackCoolDown = 0.f;
		break;
	default:
		break;
	}
}

void ACRifleStaff::RMB_Triggered(AttackResult& AttackResult)
{
	IIPlayerState* PS = Cast<IIPlayerState>(GetOwner());
	if (PS == nullptr || PS->GetState(PLAYER_ROLLING)) return;
	PS->SetState(PLAYER_AIMING, true);
}

void ACRifleStaff::RMB_Completed(AttackResult& AttackResult)
{
	IIPlayerState* PS = Cast<IIPlayerState>(GetOwner());
	if (PS == nullptr) return;

	PS->SetState(PLAYER_AIMING, false);
	PS->SetState(PLAYER_ATTACKING, false);
	SetLMBLock(false);
}

void ACRifleStaff::SetIsEquiped(bool e)
{
	IsEquiped = e;
}

void ACRifleStaff::SetBulletType(int32 e)
{
	BulletType = e;

	switch (BulletType)
	{
	case(0):
		AttackRange = 2500.f;
		BulletSpeed = 100.f;
		ConstAttackCoolDown = 0.8f * (1 - ItemStatus->_AttackSpeed);
		break;
	case(1):
		AttackRange = 500.f;
		BulletSpeed = 60.f;
		ConstAttackCoolDown = 1.4f * (1 - ItemStatus->_AttackSpeed);
		break;
	default:
		break;
	}
}

void ACRifleStaff::SetItemStat(ItemStat* ItemStats)
{
	ItemStatus = ItemStats;
}

void ACRifleStaff::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(NewOwner);
	if (PC == nullptr) return;
	PC->AimOff.BindLambda([&]() {
		SetLMBLock(false);
		});
}

// Called when the game starts or when spawned
void ACRifleStaff::BeginPlay()
{
	Super::BeginPlay();	
	ChargeAudio = UGameplayStatics::SpawnSoundAttached(WeaponSoundEffect[SE_RIFLE_TYPE_A_CHARGE], StaticMeshComponent, "FireSocket");
	ChargeAudio->Stop();
}

void ACRifleStaff::Fire()
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (FireSocket == nullptr || !IsValid(PC)) return;
	FTransform FireSocketTransform;
	FireSocket->GetSocketTransform(FireSocketTransform, StaticMeshComponent);
	
	FVector SpawnLocation = FireSocketTransform.GetLocation();

	//DrawDebugSphere(GetWorld(), SpawnLocation, 100.f, 26, FColor::Green, true, 2.f);

	FVector TargetLocation = PC->CameraComponent->GetComponentLocation() + PC->GetBaseAimRotation().RotateVector(FVector::ForwardVector * AttackRange);
	
	FHitResult HitResult;
	PC->GetLineTraceResult(HitResult, AttackRange);
	if (HitResult.bBlockingHit)
	{
		TargetLocation = HitResult.Location;
		UE_LOG(LogTemp, Log, TEXT("TargetLocation : %s"), *HitResult.GetActor()->GetName());
	}

	FRotator ProjRotator = (TargetLocation - SpawnLocation).Rotation();

	ACProjectile* Proj = GetWorld()->SpawnActor<ACProjectile>(ACProjectile::StaticClass(), SpawnLocation, ProjRotator);

	Proj->SetLaunch(
		PC,
		WeaponEffect[E_RIFLE_TYPE_A_PROJECTILE],
		WeaponEffect[E_RIFLE_EXPLODE_EFFECT],
		WeaponEffect[E_RIFLE_SPAWN_EFFECT],
		nullptr,
		AttackDamage + (AttackDamage * LMBCharge * 2.f),
		AttackRange,
		BulletSpeed,
		-1.f, nullptr, false, false, false, 0.01f, WeaponSoundEffect[SE_RIFLE_TYPE_A_Hit]
	);
	Proj->SetActorRelativeScale3D(FVector(1.f, 1.f, 1.f) * (1 + LMBCharge / 2));
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), WeaponSoundEffect[SE_RIFLE_TYPE_A_SHOT], SpawnLocation, 1+LMBCharge);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponEffect[E_RIFLE_LAUNCH_EFFECT], SpawnLocation);
}

void ACRifleStaff::BuckShot(int32 i)
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (FireSocket == nullptr || !IsValid(PC)) return;
	FTransform FireSocketTransform;
	FireSocket->GetSocketTransform(FireSocketTransform, StaticMeshComponent);

	FVector SpawnLocation = FireSocketTransform.GetLocation();
	FVector CameraLocation = PC->CameraComponent->GetComponentLocation();
	//DrawDebugSphere(GetWorld(), SpawnLocation, 100.f, 26, FColor::Green, true, 2.f);

	float CameraSocketDist = FVector::Distance(CameraLocation, SpawnLocation);
	FVector TargetLocation = CameraLocation + PC->GetBaseAimRotation().RotateVector(FVector::ForwardVector * (AttackRange + CameraSocketDist));

	FHitResult HitResult;
	PC->GetLineTraceResult(HitResult, AttackRange);
	if (HitResult.bBlockingHit)
	{
		TargetLocation = HitResult.Location;
		UE_LOG(LogTemp, Log, TEXT("Hit Actor : %s"), *HitResult.GetActor()->GetName());
	}

	FRotator ProjRotator = (SpawnLocation - TargetLocation).Rotation();
	DrawDebugSphere(GetWorld(), SpawnLocation, 100.f, 26, FColor::Green, false, 2.f);
	DrawDebugSphere(GetWorld(), TargetLocation, 100.f, 26, FColor::Red, false, 2.f);


	FVector RandomVector = UKismetMathLibrary::RandomUnitVectorInConeInDegrees((TargetLocation - SpawnLocation).GetSafeNormal(), 45.f);
	ACProjectile* Proj = GetWorld()->SpawnActor<ACProjectile>(ACProjectile::StaticClass(), SpawnLocation, RandomVector.Rotation());
	//UE_LOG(LogTemp, Log, TEXT("Random vector : %s"), *RandomVector.ToString());
	Proj->SetLaunch(
		PC,
		WeaponEffect[E_RIFLE_TYPE_A_PROJECTILE],
		WeaponEffect[E_RIFLE_EXPLODE_EFFECT],
		WeaponEffect[E_RIFLE_SPAWN_EFFECT],
		nullptr,
		AttackDamage,
		AttackRange,
		BulletSpeed,
		-1.f, nullptr, false, false, false, 0.01f, WeaponSoundEffect[SE_RIFLE_TYPE_A_Hit]
	);
	if (i == 0)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponEffect[E_RIFLE_LAUNCH_EFFECT], SpawnLocation);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), WeaponSoundEffect[SE_RIFLE_TYPE_B_SHOT], SpawnLocation);
	}
}

void ACRifleStaff::SetLMBLock(bool e)
{
	//UE_LOG(LogTemp, Log, TEXT("Set LMB Lock %s"), e ? TEXT("True") : TEXT("False"));

	if (e == LMBLock) return;

	if (e)
	{
		FireSocketEffectComponent->Activate();
		if (ChargeAudio != nullptr)
		{
			ChargeAudio->Play();
		}
	}
	else
	{
		FireSocketEffectComponent->Deactivate();
		LMBCharge = 0.f;
		if (ChargeAudio != nullptr)
		{
			ChargeAudio->Stop();
		}
	}
	LMBLock = e;
}

void ACRifleStaff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (LMBLock)
	{
		LMBCharge += DeltaTime * (1 + ItemStatus->_AttackSpeed);
		UE_LOG(LogTemp, Log, TEXT("LMBCharge : %f"), LMBCharge);

		if (ChargeAudio != nullptr)
		{
			ChargeAudio->VolumeMultiplier = 1.f + LMBCharge;
		}
	}
	if (LMBCharge > 2.f)
	{// Force Fire When Exceed Charge Time
		ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
		if (PC == nullptr) return;
		PC->StaminaSpend(12.f);
		PC->FireRifle.ExecuteIfBound();
		LMBCharge /= 2.f;
		Fire();
		AttackCoolDown = 0.f;
		SetLMBLock(false);
	}

	AttackCoolDown += DeltaTime;
	if (AttackCoolDown >= ConstAttackCoolDown)
	{
		//IIPlayerState* PS = Cast<IIPlayerState>(GetOwner());
		//if (PS == nullptr) return;
		AttackCoolDown = ConstAttackCoolDown;
		//PS->SetState(PLAYER_ATTACKING, false);
	}
}

