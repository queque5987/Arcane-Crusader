// Fill out your copyright notice in the Description page of Project Settings.


#include "CRifleStaff.h"
#include "PCH.h"
#include "Sound/SoundCue.h"
#include "CPlayerCharacter.h"
#include "IPlayerUIController.h"
#include "IPlayerState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/AudioComponent.h"
#include "CWeaponSilhouette_Rifle.h"
#include "CRifleStaffBeacon.h"

ACRifleStaff::ACRifleStaff()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RifleOraEffect = CreateDefaultSubobject<UCWeaponSilhouette_Rifle>(TEXT("WeaponSilhouette_Rifle"));
	RootComponent = StaticMeshComponent;

	Collider = CreateDefaultSubobject<USphereComponent>(FName("Collider"));
	Collider->SetupAttachment(StaticMeshComponent);
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	RifleOraEffect->SetupAttachment(StaticMeshComponent);

	DefaultRotator = FRotator(0.f, 0.f, -75.f);
	SetActorRelativeRotation(DefaultRotator);
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
	ConstructorHelpers::FObjectFinder<UParticleSystem>	Rifle_TYPE_ULT_Explode(TEXT("/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Explosion/P_Explosion_Big_C"));

	if (Rifle_Type_A_Projectilie.Succeeded())	WeaponEffect[E_RIFLE_TYPE_A_PROJECTILE]		= Rifle_Type_A_Projectilie.Object;
	if (Rifle_TYPE_A_Spawn.Succeeded())			WeaponEffect[E_RIFLE_SPAWN_EFFECT]			= Rifle_TYPE_A_Spawn.Object;
	if (Rifle_TYPE_A_Explode.Succeeded())		WeaponEffect[E_RIFLE_EXPLODE_EFFECT]		= Rifle_TYPE_A_Explode.Object;
	if (Rifle_TYPE_A_LAUNCH.Succeeded())		WeaponEffect[E_RIFLE_LAUNCH_EFFECT]			= Rifle_TYPE_A_LAUNCH.Object;
	if (Rifle_TYPE_ULT_Explode.Succeeded())		WeaponEffect[E_RIFLE_ULT_EXPLODE_EFFECT]	= Rifle_TYPE_ULT_Explode.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem>	WeaponAttackTrail(TEXT("/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Sparks/P_Sparks_A"));

	if (BattleStaffMeshFinder.Succeeded()) StaticMeshComponent->SetStaticMesh(BattleStaffMeshFinder.Object);
	if (WeaponAttackTrail.Succeeded()) WeaponEffect[E_MELLEWEAPON_ATTACK_TRAIL] = WeaponAttackTrail.Object;

	ConstructorHelpers::FObjectFinder<USoundBase>	Type_A_Charge(TEXT("/Game/Resources/Sound/Rifle/power-charge-6798"));
	ConstructorHelpers::FObjectFinder<USoundBase>	Type_A_Shot(TEXT("/Game/Resources/Sound/Rifle/gun-shots-from-a-distance-6-39721"));
	ConstructorHelpers::FObjectFinder<USoundBase>	Type_A_Hit(TEXT("/Game/Resources/Sound/Rock/rock-destroy-6409"));
	ConstructorHelpers::FObjectFinder<USoundBase>	Type_B_Shot(TEXT("/Game/Resources/Sound/Rifle/shotgun-firing-4-6746"));
	ConstructorHelpers::FObjectFinder<USoundCue>	BombSoundFinder(TEXT("/Game/Resources/Sound/Bomb/SC_Bomb"));

	if (Type_A_Charge.Succeeded())	WeaponSoundEffect[SE_RIFLE_TYPE_A_CHARGE] = Type_A_Charge.Object;
	if (Type_A_Shot.Succeeded())	WeaponSoundEffect[SE_RIFLE_TYPE_A_SHOT] = Type_A_Shot.Object;
	if (Type_A_Hit.Succeeded())		WeaponSoundEffect[SE_RIFLE_TYPE_A_Hit] = Type_A_Hit.Object;
	if (Type_B_Shot.Succeeded())	WeaponSoundEffect[SE_RIFLE_TYPE_B_SHOT] = Type_B_Shot.Object;
	if (BombSoundFinder.Succeeded())BombSoundCue = BombSoundFinder.Object;
	

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

	MachineGunTimerHandler.SetNum(6);
	for (auto& TimerHandler : MachineGunTimerHandler)
	{
		TimerHandler = FTimerHandle();
	}
	ChargeAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));

	MaxBullet.Add(50);
	MaxBullet.Add(50);
	MaxBullet.Add(50);
	CurrBullet.Add(50);
	CurrBullet.Add(50);
	CurrBullet.Add(50);
}

void ACRifleStaff::LMB_Triggered(AttackResult& AttackResult)
{
	IIPlayerState* PS = Cast<IIPlayerState>(GetOwner());
	if (PS == nullptr) return;

	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (!IsValid(PC)) return;

	if (!PS->GetState(PLAYER_AIMING)) return;

	if (AttackCoolDown < ConstAttackCoolDown) return;

	if (CurrBullet[BulletType] <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("No Ammo"));
		//return;
	}

	PS->SetState(PLAYER_ATTACKING, true);

	float Delay = 0.01f;
	switch (BulletType)
	{
	case(RIFLESTAFF_BULLET_RIFLE)://Rifle Bullet
		if (!LMBLock)
		{
			SetLMBLock(true);
		}
		AttackResult.StaminaUsed = 0.08f;
		break;
	case(RIFLESTAFF_BULLET_SHOTGUN)://ShotGun Bullet
		AttackResult.StaminaUsed = 12.f;
		PC->FireRifle.ExecuteIfBound();
		for (int i = 0; i < 10; i++)
		{
			BuckShot(i);
		}
		AttackCoolDown = 0.f;
		break;
	case(RIFLESTAFF_BULLET_MACHINEGUN)://MachineGun Bullet
		AttackResult.StaminaUsed = 5.f;
		PC->FireRifle.ExecuteIfBound();

		for (auto& H : MachineGunTimerHandler)
		{
			GetWorld()->GetTimerManager().SetTimer(H, this, &ACRifleStaff::Fire, Delay);
			Delay += 1.f / 6.f;
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


	switch (BulletType)
	{
		//Rifle Bullet
	case(RIFLESTAFF_BULLET_RIFLE):
		PS->SetState(PLAYER_ATTACKING, true);
		AttackResult.StaminaUsed = 5.f;
		PC->FireRifle.ExecuteIfBound();
		Fire();
		SetLMBLock(false);
		AttackCoolDown = 0.f;
		break;
	default:
		PS->SetState(PLAYER_ATTACKING, false);
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
	CancleFire();
	//PS->SetState(PLAYER_ATTACKING, false);
	//if (LMBLock) SetLMBLock(false);
	//if (BulletType == 2)
	//{
	//	for (auto& H : MachineGunTimerHandler)
	//	{
	//		GetWorld()->GetTimerManager().ClearTimer(H);
	//	}
	//}
}

void ACRifleStaff::Tab_Triggered(AttackResult& AttackResult)
{
	SetBulletType((BulletType + 1) % 3);
	//fSpinAct += 360.f;

	GetWorld()->GetTimerManager().SetTimer(
		BulletChangeTimerHandler, FTimerDelegate::CreateLambda([&] {
			fSpinAct += 360.f;
			}
		), 0.2f, false
	);
	CancleFire();

	UE_LOG(LogTemp, Log, TEXT("To BulletType : %d"), BulletType);

}

void ACRifleStaff::Ult_Triggered(AttackResult& AttackResult)
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (!IsValid(PC)) return;

	PC->SetState(PLAYER_ATTACKING, true);

	PC->RifleStaffUlt.Execute();
}

void ACRifleStaff::UltFunc0()
{
	IIPlayerState* PlayerState = Cast<IIPlayerState>(GetOwner());
	ACharacter* Player = Cast<ACharacter>(GetOwner());
	if (PlayerState == nullptr || Player == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ACRifleStaff Is not Attached To Player"));
		return;
	}
	FTransform SocketTransform = PlayerState->GetSocketTransform("RifleSocket");
	UltBeacon = GetWorld()->SpawnActor<ACRifleStaffBeacon>(ACRifleStaffBeacon::StaticClass(), SocketTransform);
	UltBeacon->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "RifleSocket");
	UltBeacon->SetSummonedRifle(this);

	if (UltBeacon != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Beacon Successfully Spawned"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Beacon Ia Not Successfully Spawned"));
	}
}

void ACRifleStaff::UltFunc1()
{
	if (UltBeacon == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Beacon Ia Not Successfully Spawned"));
		return;
	}
	UE_LOG(LogTemp, Error, TEXT("Beacon Ia Not Successfully Spawned"));
	UltBeacon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	IIPlayerState* PlayerState = Cast<IIPlayerState>(GetOwner());
	if (PlayerState == nullptr) return;

	FHitResult HitResult;
	PlayerState->GetLineTraceResult(HitResult, 50000.f);
	FVector ThrowDestination;
	FVector PlayerLocation = GetOwner()->GetActorLocation();

	if (HitResult.bBlockingHit && FVector::Distance(PlayerLocation, HitResult.Location) <= 2500.f)
	{
		ThrowDestination = HitResult.Location;
	}
	else
	{
		FRotator Direction = GetOwner()->GetActorRotation();
		Direction.Pitch = 0.f;
		FVector DirectionalVector = Direction.Vector();
		ThrowDestination = PlayerLocation + DirectionalVector * 2500.f;
	}
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (NavSystem != nullptr)
	{
		FNavLocation StandableLocation;
		bool Success = NavSystem->ProjectPointToNavigation(ThrowDestination, StandableLocation);
		if (Success)
		{
			//DrawDebugSphere(GetWorld(), ThrowDestination, 200.f, 32.f, FColor::Red, false, 2.f);
			ThrowDestination = StandableLocation.Location;
			//DrawDebugSphere(GetWorld(), ThrowDestination, 200.f, 32.f, FColor::Green, false, 2.f);
		}
	}
	FTransform SocketTransform = PlayerState->GetSocketTransform("RifleSocket");

	//DrawDebugSphere(GetWorld(), ThrowDestination, 200.f, 32.f, FColor::Green, false, 2.f);
	UltBeacon->Throw(SocketTransform.GetLocation(), ThrowDestination);
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
	case(RIFLESTAFF_BULLET_RIFLE):
		AttackRange = 3000.f;
		BulletSpeed = 120.f;
		ConstAttackCoolDown = 0.8f * (1 - ItemStatus->_AttackSpeed);
		break;
	case(RIFLESTAFF_BULLET_SHOTGUN):
		AttackRange = 500.f;
		BulletSpeed = 60.f;
		ConstAttackCoolDown = 1.4f * (1 - ItemStatus->_AttackSpeed);
		break;
	case(RIFLESTAFF_BULLET_MACHINEGUN):
		AttackRange = 2500.f;
		BulletSpeed = 90.f;
		ConstAttackCoolDown = 1.1f * (1 - ItemStatus->_AttackSpeed);
		break;
	default:
		break;
	}

	RifleOraEffect->SetWeaponEffect(BulletType);
}

void ACRifleStaff::SetItemStat(ItemStat* ItemStats)
{
	ItemStatus = ItemStats;
	SetBulletType(BulletType);
	UE_LOG(LogTemp, Log, TEXT("updated item stat : AS : %f"), ItemStats->_AttackSpeed);
	UE_LOG(LogTemp, Log, TEXT("updated item stat : AD : %f"), ItemStats->_AttackDamage);
}

void ACRifleStaff::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(NewOwner);
	if (PC == nullptr) return;
	//PC->AimOff.BindLambda([&]() {
	//	if (LMBLock) SetLMBLock(false);
	//	});
}

float ACRifleStaff::GetMaxBullet(int32 ToGetBulletType)
{
	return MaxBullet.IsValidIndex(ToGetBulletType) ? MaxBullet[ToGetBulletType] : MaxBullet[BulletType];
}

float ACRifleStaff::GetCurrBullet(int32 ToGetBulletType)
{
	return CurrBullet.IsValidIndex(ToGetBulletType) ? CurrBullet[ToGetBulletType] : CurrBullet[BulletType];
}

// Called when the game starts or when spawned
void ACRifleStaff::BeginPlay()
{
	Super::BeginPlay();	
	//ChargeAudio = UGameplayStatics::SpawnSoundAttached(WeaponSoundEffect[SE_RIFLE_TYPE_A_CHARGE], StaticMeshComponent, "FireSocket");
	ChargeAudio = UGameplayStatics::SpawnSound2D(GetWorld(), WeaponSoundEffect[SE_RIFLE_TYPE_A_CHARGE], 1.f, 1.f, 0.f, nullptr, false, false);
	ChargeAudio->Stop();
	
}

void ACRifleStaff::Fire()
{
	if (BulletType > 0 && !SetSpendBullet(BulletType, (BulletType == 0 ? (5 + LMBCharge * 5) : (1.f)))) return;

	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (FireSocket == nullptr || !IsValid(PC)) return;
	FTransform FireSocketTransform;
	FireSocket->GetSocketTransform(FireSocketTransform, StaticMeshComponent);
	
	FVector SpawnLocation = FireSocketTransform.GetLocation();

	//DrawDebugSphere(GetWorld(), SpawnLocation, 100.f, 26, FColor::Green, true, 2.f);
	FVector TargetLocation = PC->CameraComponent->GetComponentLocation() + PC->GetBaseAimRotation().RotateVector(FVector::ForwardVector * (AttackRange + PC->GetCameraArmLength()));

	//DrawDebugSphere(GetWorld(), TargetLocation, 100.f, 26, FColor::Green, true, 2.f);

	FHitResult HitResult;
	PC->GetLineTraceResult(HitResult, AttackRange);
	if (HitResult.bBlockingHit)
	{
		TargetLocation = HitResult.Location;
		UE_LOG(LogTemp, Log, TEXT("TargetLocation : %s"), *HitResult.GetActor()->GetName());
	}

	FRotator ProjRotator = (TargetLocation - SpawnLocation).Rotation();

	ACProjectile* Proj = GetWorld()->SpawnActor<ACProjectile>(ACProjectile::StaticClass(), SpawnLocation, ProjRotator);
	
	float tempAD = ItemStatus->_AttackDamage;

	Proj->SetLaunch(
		PC,
		WeaponEffect[E_RIFLE_TYPE_A_PROJECTILE],
		WeaponEffect[E_RIFLE_EXPLODE_EFFECT],
		nullptr,
		nullptr,
		(BulletType == 0) ? tempAD + (tempAD * LMBCharge * 15.f) : tempAD,
		(BulletType == 0) ? AttackRange + (AttackRange * LMBCharge / 4.f) : AttackRange,
		BulletSpeed,
		-1.f, nullptr, false, false, false, 0.01f, WeaponSoundEffect[SE_RIFLE_TYPE_A_Hit]
	);
	UE_LOG(LogTemp, Log, TEXT("BulletType  : %d , %f "), BulletType, (BulletType == 0 ? (5 + LMBCharge * 5) : (1.f)));
	
	//CurrBullet[BulletType] -= 1;
	if (BulletType == 0) Proj->SetActorRelativeScale3D(FVector(1.f, 1.f, 1.f) * (1 + LMBCharge / 2));
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), WeaponSoundEffect[SE_RIFLE_TYPE_A_SHOT], SpawnLocation, (BulletType == 0) ? 1+LMBCharge : 1.f);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponEffect[E_RIFLE_LAUNCH_EFFECT], SpawnLocation);
}

void ACRifleStaff::BuckShot(int32 i)
{
	if (!SetSpendBullet(BulletType, 0.7f)) return;

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


	FVector RandomVector = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(
		(TargetLocation - SpawnLocation).GetSafeNormal(), 45.f);
	ACProjectile* Proj = GetWorld()->SpawnActor<ACProjectile>(ACProjectile::StaticClass(),
		SpawnLocation, RandomVector.Rotation());
	//UE_LOG(LogTemp, Log, TEXT("Random vector : %s"), *RandomVector.ToString());
	Proj->SetLaunch(
		PC,
		WeaponEffect[E_RIFLE_TYPE_A_PROJECTILE],
		WeaponEffect[E_RIFLE_EXPLODE_EFFECT],
		nullptr,
		nullptr,
		0.6f * ItemStatus->_AttackDamage,
		AttackRange,
		BulletSpeed,
		-1.f, nullptr, false, false, false, 0.01f, WeaponSoundEffect[SE_RIFLE_TYPE_A_Hit]
	);
	//CurrBullet[BulletType] -= 1;
	if (i == 0)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponEffect[E_RIFLE_LAUNCH_EFFECT], SpawnLocation);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), WeaponSoundEffect[SE_RIFLE_TYPE_B_SHOT], SpawnLocation);
	}
	
	//PC->SetState(PLAYER_ATTACKING, false);
}

void ACRifleStaff::CancleFire()
{
	IIPlayerState* PS = Cast<IIPlayerState>(GetOwner());
	if (PS == nullptr) return;

	PS->SetState(PLAYER_ATTACKING, false);
	if (LMBLock) SetLMBLock(false);
	for (auto& H : MachineGunTimerHandler)
	{
		GetWorld()->GetTimerManager().ClearTimer(H);
	}
}

bool ACRifleStaff::SetSpendBullet(int32 Type, float Amount)
{
	if (CurrBullet[Type] < Amount) return false;
	CurrBullet[Type] -= Amount;
	//UE_LOG(LogTemp, Log, TEXT("ACRifleStaff - Execute BulletCountUpdated : Spend Amount : %f"), Amount);
	BulletCountUpdated.Execute(CurrBullet[BulletType] / MaxBullet[BulletType]);
	return true;
}

bool ACRifleStaff::HitCheckAtLocation(FVector SweepLocation, float Radius, float OverrideDamageScale)
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, GetAttachParentActor());
	FCollisionObjectQueryParams OQP(PlayerAttackChannel);

	bool bResult = GetWorld()->SweepSingleByObjectType(
		HitResult,
		SweepLocation,
		SweepLocation,
		FQuat::Identity,
		OQP,
		FCollisionShape::MakeSphere(Radius),
		Params
	);
	//if (bResult) UE_LOG(LogTemp, Log, TEXT("Hit At Actor : %s"), *HitResult.GetActor()->GetName());
	//if (bResult) UE_LOG(LogTemp, Log, TEXT("Hit At Component : %s"), *HitResult.GetComponent()->GetFullName());
	//if (bResult) UE_LOG(LogTemp, Log, TEXT("Hit At Actor : %s"), *HitResult.GetActor()->GetFullName());

	if (bResult)
	{
		//DrawDebugSphere(GetWorld(), SweepLocation, Radius, 32.f, bResult ? FColor::Green : FColor::Red, false, 0.1f);

		ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(HitResult.GetActor());
		if (EC == nullptr) return false;
		ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetAttachParentActor());
		if (PC == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("AttachParentActor is not ACPlayerCharacter"));
			return false;
		}

		UE_LOG(LogTemp, Log, TEXT("Attack Damage : %f, Damage Scale : %f"), AttackDamage, DamageScale);

		PC->DealtDamage(AttackDamage, OverrideDamageScale, EC);
		EC->HitDamage(AttackDamage * OverrideDamageScale, *PC, HitResult.Location);

		//FTransform HitEffectSpawnTransform;
		//HitEffectSpawnTransform.SetLocation(HitResult.Location);
		//FRotator HitEffectTempRot = FRotationMatrix::MakeFromX(SwingingDirection.GetSafeNormal()).Rotator();
		//HitEffectSpawnTransform.SetRotation(FQuat(HitEffectTempRot));
		//HitEffectSpawnTransform.SetScale3D(FVector(0.5f, 0.5f, 0.5f));

		//UParticleSystemComponent* tempParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponEffect[E_MELLEWEAPON_ATTACK_HIT], HitEffectSpawnTransform);
		//if (tempParticle != nullptr)
		//{
		//	HitParticleQueue.Enqueue(tempParticle);
		//	GetWorld()->GetTimerManager().SetTimer(EffectSpawnTimerHandler, this, &ACBattleStaff::DequeueHitParticle, 0.5f);
		//}
	}


	return bResult;
}

//DEPRECATED
void ACRifleStaff::UpdateCharacterStat()
{
	//ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	//if (PC == nullptr) return;
	//IIPlayerUIController* UIController = Cast<IIPlayerUIController>(PC->GetController());
	//if (UIController == nullptr) return;
	//UIController->EquippedItemStat(ItemStatus);
}

void ACRifleStaff::UltBombArea(FVector BombLocation, float Radius)
{
	UE_LOG(LogTemp, Log, TEXT("Got BombLocation : %s"), *BombLocation.ToString());
	BombCounter = 24;

	GetWorld()->GetTimerManager().SetTimer(UltBombTimerHandler, FTimerDelegate::CreateLambda([&, BombLocation, Radius] {
		if (BombCounter < 0)
		{
			GetWorld()->GetTimerManager().ClearTimer(UltBombTimerHandler);
		}

		float Theta = FMath::FRandRange(0.f, 2 * PI);
		float r = Radius * FMath::Sqrt(FMath::FRand());

		float X = r * FMath::Cos(Theta);
		float Y = r * FMath::Sin(Theta);

		FVector RandomLocation = BombLocation + FVector(X, Y, 0.f);
		//DrawDebugSphere(GetWorld(), RandomLocation, 50.f, 32.f, FColor::Red, false, 2.f);

		HitCheckAtLocation(RandomLocation, 200.f, 10.f);

		float Scale = 1.f + FMath::FRand() * 0.4f;

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), BombSoundCue, RandomLocation, Scale - 0.4f);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponEffect[E_RIFLE_ULT_EXPLODE_EFFECT], RandomLocation, FRotator(0.f, 0.f, r / Radius * 360.f), FVector(Scale, Scale, Scale));

		BombCounter -= 1;
		}
	), 0.28f, true);
}

void ACRifleStaff::SetLMBLock(bool e)
{
	if (e)
	{
		FireSocketEffectComponent->Activate();
		if (ChargeAudio == nullptr)
		ChargeAudio->Play();
		LMBLock = e;
	}
	else
	{
		FireSocketEffectComponent->Deactivate();
		LMBCharge = 0.f;
		if (ChargeAudio == nullptr) return;
		if (ChargeAudio->IsPlaying()) ChargeAudio->Stop();
		LMBLock = e;
	}
}

void ACRifleStaff::GetLeftBullet(FVector& LeftBulletPercent)
{
	LeftBulletPercent.X = CurrBullet[BulletType] / MaxBullet[BulletType];
	LeftBulletPercent.Y = CurrBullet[(BulletType + 2) % 3] / MaxBullet[(BulletType + 2) % 3];
	LeftBulletPercent.Z = CurrBullet[(BulletType + 1) % 3] / MaxBullet[(BulletType + 1) % 3];
}

void ACRifleStaff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

// Rifle Mode Charging
	if (LMBLock)
	{
		LMBCharge += DeltaTime * (1 + ItemStatus->_AttackSpeed);

		if (ChargeAudio != nullptr)
		{
			ChargeAudio->VolumeMultiplier = 1.f + LMBCharge;
		}

		//CurrBullet[RIFLESTAFF_BULLET_RIFLE] -= DeltaTime * (1 + ItemStatus->_AttackSpeed);
		if (!SetSpendBullet(RIFLESTAFF_BULLET_RIFLE, DeltaTime * (7 + ItemStatus->_AttackSpeed)) || LMBCharge > 2.f)
		{
			// Force Fire When Not Enough Bullet Or Exceed Charge Time
			ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
			if (PC == nullptr) return;
			PC->StaminaSpend(12.f);
			PC->FireRifle.ExecuteIfBound();
			LMBCharge /= 2.f;
			Fire();
			AttackCoolDown = 0.f;
			if (LMBLock) SetLMBLock(false);
		}
	}

	AttackCoolDown += DeltaTime;
	if (AttackCoolDown >= ConstAttackCoolDown)
	{
		//IIPlayerState* PS = Cast<IIPlayerState>(GetOwner());
		//if (PS == nullptr) return;
		AttackCoolDown = ConstAttackCoolDown;
		//PS->SetState(PLAYER_ATTACKING, false);
	}

	IIPlayerState* PS = Cast<IIPlayerState>(GetOwner());
	if (PS == nullptr) return;
	if (PS->GetState(PLAYER_STAMINA_RUNOUT) && BulletType == 2)
	{
		for (auto& H : MachineGunTimerHandler)
		{
			GetWorld()->GetTimerManager().ClearTimer(H);
		}
	}

	//Bullet Regen
	for (int i = 0; i < 3; i++)
	{
		if (i == BulletType) continue;
		float TheLessTheFaster = (((MaxBullet[i] - CurrBullet[i]) / MaxBullet[i]) / 2.f + 1.f);
		CurrBullet[i] += MaxBullet[i] / 60.f * DeltaTime * TheLessTheFaster;
		if (CurrBullet[i] > MaxBullet[i]) CurrBullet[i] = MaxBullet[i];
	}

	//Bullet Chanage Spin Act
	if (fSpinAct > 0.f)
	{
		float DoSpin = DeltaTime * 360.f * 3.f;
		if (fSpinAct < DoSpin) DoSpin = fSpinAct;
		fSpinAct -= DoSpin;
		SetActorRelativeRotation(FRotator(0.f, 0.f, fSpinAct - 360.f));
	}
}

