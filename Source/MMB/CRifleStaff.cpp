// Fill out your copyright notice in the Description page of Project Settings.


#include "CRifleStaff.h"
#include "PCH.h"
#include "Sound/SoundCue.h"
#include "CPlayerCharacter.h"
#include "IPlayerUIController.h"
#include "IPlayerState.h"
#include "Kismet/KismetMathLibrary.h"

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

	//ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackCombo_ExplodeEffect(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_RockBurst/P_RBurst_Default_Burst_Area_01"));
	//ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackCombo_FinalAttackExplode(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_RockBurst/P_RBurst_Default_Burst_SinkH_01"));
	//ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackCombo_FinalAttackBonusExplode(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_RockBurst/P_RBurst_Default_Burst_Stalag_01"));
	//ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackCombo_Combo2AttackExplode(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_RockBurst/P_RBurst_Default_Charge_Slam_01"));
	//ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackHitEffect(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_RockBurst/P_RBurst_Base_Charge_01"));
	//ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackCombo_Combo1AttackProjectileEffect(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/combat/P_ProjectileLob_Bomblet_Untyped"));
	//ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackCombo_Combo1AttackProjectileExplode(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/combat/P_ProjectileLob_Explo_Untyped"));
	//ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackCombo_Combo1AttackProjectileLaunchEffect(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/combat/P_Shout_00"));
	//ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackCombo_Combo1AttackProjectileSpawnEffect(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/combat/P_Shout_Charge_00"));
	//ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackCombo_Combo2AttackProjectileEffect(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/combat/P_LineToPoint_Projectile_Untyped"));
	//ConstructorHelpers::FObjectFinder<UParticleSystem>	WeaponAttackingEffect(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/Fire/P_Beam_Laser_Dot"));
	ConstructorHelpers::FObjectFinder<UParticleSystem>	WeaponAttackTrail(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_WeaponThrow/P_Skill_Throw_Fire_Trail_Base"));
	//ConstructorHelpers::FObjectFinder<UParticleSystem>	WeaponAttackHitEffect(TEXT("/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Sparks/P_Sparks_C"));
	//ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackCombo_Combo2AttackProjectileHitEffect(TEXT("/Game/InfinityBladeEffects/Effects/FX_Treasure/Resources/P_Resource_Impact_Rock"));

	if (BattleStaffMeshFinder.Succeeded()) StaticMeshComponent->SetStaticMesh(BattleStaffMeshFinder.Object);

	//if (MeleeAttackCombo_ExplodeEffect.Succeeded()) WeaponEffect[E_MELEEATTACKCOMBO_3_EXPLODE] = MeleeAttackCombo_Combo2AttackExplode.Object;;
	//if (MeleeAttackCombo_FinalAttackExplode.Succeeded()) WeaponEffect[E_MELEEATTACKCOMBO_3_FINALATTACK_EXPLODE] = MeleeAttackCombo_ExplodeEffect.Object;
	//if (MeleeAttackCombo_FinalAttackBonusExplode.Succeeded()) WeaponEffect[E_MELEEATTACKCOMBO_3_FINALATTACK_BONUS_EXPLODE] = MeleeAttackCombo_FinalAttackBonusExplode.Object;
	//if (MeleeAttackCombo_Combo2AttackExplode.Succeeded()) WeaponEffect[E_MELEEATTACKCOMBO_2_EXPLODE] = MeleeAttackCombo_Combo2AttackExplode.Object;
	//if (MeleeAttackHitEffect.Succeeded()) WeaponEffect[E_MELEEATTACK_HITEFFECT] = MeleeAttackHitEffect.Object;
	//if (MeleeAttackCombo_Combo1AttackProjectileEffect.Succeeded()) WeaponEffect[E_MELEEATTACKCOMBO_1_PROJECTILE] = MeleeAttackCombo_Combo1AttackProjectileEffect.Object;
	//if (MeleeAttackCombo_Combo1AttackProjectileExplode.Succeeded()) WeaponEffect[E_MELLEATTACKCOMBO_1_PROJECTILE_EXPLODE] = MeleeAttackCombo_Combo1AttackProjectileExplode.Object;
	//if (MeleeAttackCombo_Combo1AttackProjectileLaunchEffect.Succeeded()) WeaponEffect[E_MELLEATTACKCOMBO_1_PROJECTILE_LAUNCH] = MeleeAttackCombo_Combo1AttackProjectileLaunchEffect.Object;
	//if (MeleeAttackCombo_Combo1AttackProjectileSpawnEffect.Succeeded()) WeaponEffect[E_MELLEATTACKCOMBO_1_PROJECTILE_SPAWN] = MeleeAttackCombo_Combo1AttackProjectileSpawnEffect.Object;
	//if (MeleeAttackCombo_Combo2AttackProjectileEffect.Succeeded()) WeaponEffect[E_MELLEATTACKCOMBO_2_PROJECTILE] = MeleeAttackCombo_Combo2AttackProjectileEffect.Object;
	//if (WeaponAttackingEffect.Succeeded()) WeaponEffect[E_MELLEWEAPON_ATTACKING_EFFECT] = WeaponAttackingEffect.Object;
	if (WeaponAttackTrail.Succeeded()) WeaponEffect[E_MELLEWEAPON_ATTACK_TRAIL] = WeaponAttackTrail.Object;
	//if (WeaponAttackHitEffect.Succeeded()) WeaponEffect[E_MELLEWEAPON_ATTACK_HIT] = WeaponAttackHitEffect.Object;
	//if (MeleeAttackCombo_Combo2AttackProjectileHitEffect.Succeeded()) WeaponEffect[E_MELLEATTACKCOMBO_2_PROJECTILE_HIT] = MeleeAttackCombo_Combo2AttackProjectileHitEffect.Object;

	ConstructorHelpers::FObjectFinder<USoundBase> Type_A_Shot(TEXT("/Game/Resources/Sound/Rifle/gun-shots-from-a-distance-6-39721"));
	ConstructorHelpers::FObjectFinder<USoundBase> Type_A_Hit(TEXT("/Game/Resources/Sound/Rock/rock-destroy-6409"));
	//ConstructorHelpers::FObjectFinder<USoundBase> MeleeAttackCombo_FinalAttack_ExplodeSE(TEXT("/Game/Resources/Sound/Rock/rock-destroy-6409"));
	//ConstructorHelpers::FObjectFinder<USoundBase> MeleeAttackCombo_Combo2AttackProjectile_ExplodeSE(TEXT("/Game/Resources/Sound/Rock/small-rock-break-194553"));
	//ConstructorHelpers::FObjectFinder<USoundBase> MeleeAttackCombo_Combo2AttackProjectile_LauncchSE(TEXT("/Game/Resources/Sound/Rock/stones-falling-6375"));
	//ConstructorHelpers::FObjectFinder<USoundBase> MeleeAttackCombo_Combo1AttackProjectile_LauncchSE(TEXT("/Game/Resources/Sound/Rock/rocks-6129"));

	//if (MeleeAttackCombo_FinalAttack_ExplodeSE.Succeeded()) WeaponSoundEffect[SE_MELEEATTACKCOMBO_3_EXPLODE] = MeleeAttackCombo_FinalAttack_ExplodeSE.Object;
	//if (MeleeAttackCombo_Combo2AttackProjectile_ExplodeSE.Succeeded()) WeaponSoundEffect[SE_MELEEATTACKCOMBO_2_EXPLODE] = MeleeAttackCombo_Combo2AttackProjectile_ExplodeSE.Object;
	//if (MeleeAttackCombo_Combo2AttackProjectile_LauncchSE.Succeeded()) WeaponSoundEffect[SE_MELEEATTACKCOMBO_2_LAUNCH] = MeleeAttackCombo_Combo2AttackProjectile_LauncchSE.Object;
	//if (MeleeAttackCombo_Combo1AttackProjectile_LauncchSE.Succeeded()) WeaponSoundEffect[SE_MELEEATTACKCOMBO_1_LAUNCH] = MeleeAttackCombo_Combo1AttackProjectile_LauncchSE.Object;

	if (Type_A_Shot.Succeeded())	WeaponSoundEffect[SE_RIFLE_TYPE_A_SHOT] = Type_A_Shot.Object;
	if (Type_A_Hit.Succeeded())		WeaponSoundEffect[SE_RIFLE_TYPE_A_Hit] = Type_A_Hit.Object;


	FireSocketEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireSocketEffet"));
	FireSocketEffectComponent->SetupAttachment(StaticMeshComponent);
	FireSocketEffectComponent->AttachToComponent(StaticMeshComponent, FAttachmentTransformRules::KeepRelativeTransform, "FireSocket");
	FireSocketEffectComponent->SetTemplate(WeaponAttackTrail.Object);

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
		//Rifle Bullet
	case(0):
		//PS->StaminaSpend(5.f);
		AttackResult.StaminaUsed = 5.f;
		PC->FireRifle.ExecuteIfBound();
		Fire();
		AttackCoolDown = 0.f;
		break;
		//ShotGun Bullet
	case(1):
		AttackResult.StaminaUsed = 12.f;
		//PS->StaminaSpend(12.f);
		PC->FireRifle.ExecuteIfBound();
		for (int i = 0; i < 20; i++)
		{
			BuckShot();
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

	if (PS->GetState(PLAYER_AIMING))
	{
		//PC->StopAnimMontage();
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
	case(1):
		AttackRange = 500.f;
		BulletSpeed = 60.f;
		ConstAttackCoolDown = 1.4f * (1 - ItemStatus->_AttackSpeed);
	default:
		break;
	}
}

void ACRifleStaff::SetItemStat(ItemStat* ItemStats)
{
	ItemStatus = ItemStats;
}

// Called when the game starts or when spawned
void ACRifleStaff::BeginPlay()
{
	Super::BeginPlay();
	
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
		AttackDamage,
		AttackRange,
		BulletSpeed,
		-1.f, nullptr, false, false, false, 0.01f, WeaponSoundEffect[SE_RIFLE_TYPE_A_Hit], WeaponSoundEffect[SE_RIFLE_TYPE_A_SHOT]
	);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponEffect[E_RIFLE_LAUNCH_EFFECT], SpawnLocation);
}

void ACRifleStaff::BuckShot()
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (FireSocket == nullptr || !IsValid(PC)) return;
	FTransform FireSocketTransform;
	FireSocket->GetSocketTransform(FireSocketTransform, StaticMeshComponent);

	FVector SpawnLocation = FireSocketTransform.GetLocation();

	DrawDebugSphere(GetWorld(), SpawnLocation, 100.f, 26, FColor::Green, true, 2.f);

	FVector TargetLocation = PC->CameraComponent->GetComponentLocation() + PC->GetBaseAimRotation().RotateVector(FVector::ForwardVector * AttackRange);

	FHitResult HitResult;
	PC->GetLineTraceResult(HitResult, AttackRange);
	if (HitResult.bBlockingHit)
	{
		TargetLocation = HitResult.Location;
	}

	FRotator ProjRotator = (TargetLocation - SpawnLocation).Rotation();

	FVector RandomVector = UKismetMathLibrary::RandomUnitVectorInConeInDegrees((SpawnLocation - TargetLocation).GetSafeNormal(), 45.f);
	ACProjectile* Proj = GetWorld()->SpawnActor<ACProjectile>(ACProjectile::StaticClass(), SpawnLocation, RandomVector.Rotation());
	UE_LOG(LogTemp, Log, TEXT("Random vector : %s"), *RandomVector.ToString());
	Proj->SetLaunch(
		PC,
		WeaponEffect[E_RIFLE_TYPE_A_PROJECTILE],
		WeaponEffect[E_RIFLE_EXPLODE_EFFECT],
		WeaponEffect[E_RIFLE_SPAWN_EFFECT],
		nullptr,
		AttackDamage,
		AttackRange,
		BulletSpeed,
		-1.f, nullptr, false, false, false, 0.01f, WeaponSoundEffect[SE_RIFLE_TYPE_A_Hit], WeaponSoundEffect[SE_RIFLE_TYPE_A_SHOT]
	);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponEffect[E_RIFLE_LAUNCH_EFFECT], SpawnLocation);
}

void ACRifleStaff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AttackCoolDown += DeltaTime;
	if (AttackCoolDown >= ConstAttackCoolDown)
	{
		AttackCoolDown = ConstAttackCoolDown;

		IIPlayerState* PS = Cast<IIPlayerState>(GetOwner());
		if (PS == nullptr) return;

		PS->SetState(PLAYER_ATTACKING, false);
	}
}

