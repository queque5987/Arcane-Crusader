// Fill out your copyright notice in the Description page of Project Settings.


#include "CBattleStaff.h"
#include "Sound/SoundCue.h"
#include "IPlayerUIController.h"

ACBattleStaff::ACBattleStaff() : Super()
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


	ConstructorHelpers::FObjectFinder <USoundCue> MeleeHitSoundCueFinder(TEXT("/Game/Resources/Sound/Hit/Staff_Melee_Hit.Staff_Melee_Hit"));
	if (MeleeHitSoundCueFinder.Succeeded()) StaffMeleeHitSoundCue = MeleeHitSoundCueFinder.Object;

	ConstructorHelpers::FObjectFinder<UStaticMesh>		BattleStaffMeshFinder								(TEXT("/Game/BattleWizardPolyart/Meshes/MagicStaffs/Staff01SM.Staff01SM"));
	ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackCombo_ExplodeEffect						(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_RockBurst/P_RBurst_Default_Burst_Area_01.P_RBurst_Default_Burst_Area_01"));
	ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackCombo_FinalAttackExplode					(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_RockBurst/P_RBurst_Default_Burst_SinkH_01.P_RBurst_Default_Burst_SinkH_01"));
	ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackCombo_FinalAttackBonusExplode			(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_RockBurst/P_RBurst_Default_Burst_Stalag_01.P_RBurst_Default_Burst_Stalag_01"));
	ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackCombo_Combo2AttackExplode				(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_RockBurst/P_RBurst_Default_Charge_Slam_01.P_RBurst_Default_Charge_Slam_01"));
	ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackHitEffect								(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_RockBurst/P_RBurst_Base_Charge_01.P_RBurst_Base_Charge_01"));
	ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackCombo_Combo1AttackProjectileEffect		(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/combat/P_ProjectileLob_Bomblet_Untyped.P_ProjectileLob_Bomblet_Untyped"));
	ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackCombo_Combo1AttackProjectileExplode		(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/combat/P_ProjectileLob_Explo_Untyped.P_ProjectileLob_Explo_Untyped"));
	ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackCombo_Combo1AttackProjectileLaunchEffect	(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/combat/P_Shout_00.P_Shout_00"));
	ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackCombo_Combo1AttackProjectileSpawnEffect	(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/combat/P_Shout_Charge_00.P_Shout_Charge_00"));
	ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackCombo_Combo2AttackProjectileEffect		(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/combat/P_LineToPoint_Projectile_Untyped.P_LineToPoint_Projectile_Untyped"));
	ConstructorHelpers::FObjectFinder<UParticleSystem>	WeaponAttackingEffect								(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/Fire/P_Beam_Laser_Dot.P_Beam_Laser_Dot"));
	ConstructorHelpers::FObjectFinder<UParticleSystem>	WeaponAttackTrail									(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_WeaponThrow/P_Skill_Throw_Fire_Trail_Base.P_Skill_Throw_Fire_Trail_Base"));
	ConstructorHelpers::FObjectFinder<UParticleSystem>	WeaponAttackHitEffect								(TEXT("/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Sparks/P_Sparks_C.P_Sparks_C"));
	ConstructorHelpers::FObjectFinder<UParticleSystem>	MeleeAttackCombo_Combo2AttackProjectileHitEffect	(TEXT("/Game/InfinityBladeEffects/Effects/FX_Treasure/Resources/P_Resource_Impact_Rock.P_Resource_Impact_Rock"));

	if (BattleStaffMeshFinder.Succeeded()) StaticMeshComponent->SetStaticMesh(BattleStaffMeshFinder.Object);

	if (MeleeAttackCombo_ExplodeEffect.Succeeded()) WeaponEffect[E_MELEEATTACKCOMBO_3_EXPLODE] = MeleeAttackCombo_Combo2AttackExplode.Object;;
	if (MeleeAttackCombo_FinalAttackExplode.Succeeded()) WeaponEffect[E_MELEEATTACKCOMBO_3_FINALATTACK_EXPLODE] = MeleeAttackCombo_ExplodeEffect.Object;
	if (MeleeAttackCombo_FinalAttackBonusExplode.Succeeded()) WeaponEffect[E_MELEEATTACKCOMBO_3_FINALATTACK_BONUS_EXPLODE] = MeleeAttackCombo_FinalAttackBonusExplode.Object;
	if (MeleeAttackCombo_Combo2AttackExplode.Succeeded()) WeaponEffect[E_MELEEATTACKCOMBO_2_EXPLODE] = MeleeAttackCombo_Combo2AttackExplode.Object;
	if (MeleeAttackHitEffect.Succeeded()) WeaponEffect[E_MELEEATTACK_HITEFFECT] = MeleeAttackHitEffect.Object;
	if (MeleeAttackCombo_Combo1AttackProjectileEffect.Succeeded()) WeaponEffect[E_MELEEATTACKCOMBO_1_PROJECTILE] = MeleeAttackCombo_Combo1AttackProjectileEffect.Object;
	if (MeleeAttackCombo_Combo1AttackProjectileExplode.Succeeded()) WeaponEffect[E_MELLEATTACKCOMBO_1_PROJECTILE_EXPLODE] = MeleeAttackCombo_Combo1AttackProjectileExplode.Object;
	if (MeleeAttackCombo_Combo1AttackProjectileLaunchEffect.Succeeded()) WeaponEffect[E_MELLEATTACKCOMBO_1_PROJECTILE_LAUNCH] = MeleeAttackCombo_Combo1AttackProjectileLaunchEffect.Object;
	if (MeleeAttackCombo_Combo1AttackProjectileSpawnEffect.Succeeded()) WeaponEffect[E_MELLEATTACKCOMBO_1_PROJECTILE_SPAWN] = MeleeAttackCombo_Combo1AttackProjectileSpawnEffect.Object;
	if (MeleeAttackCombo_Combo2AttackProjectileEffect.Succeeded()) WeaponEffect[E_MELLEATTACKCOMBO_2_PROJECTILE] = MeleeAttackCombo_Combo2AttackProjectileEffect.Object;
	if (WeaponAttackingEffect.Succeeded()) WeaponEffect[E_MELLEWEAPON_ATTACKING_EFFECT] = WeaponAttackingEffect.Object;
	if (WeaponAttackTrail.Succeeded()) WeaponEffect[E_MELLEWEAPON_ATTACK_TRAIL] = WeaponAttackTrail.Object;
	if (WeaponAttackHitEffect.Succeeded()) WeaponEffect[E_MELLEWEAPON_ATTACK_HIT] = WeaponAttackHitEffect.Object;
	if (MeleeAttackCombo_Combo2AttackProjectileHitEffect.Succeeded()) WeaponEffect[E_MELLEATTACKCOMBO_2_PROJECTILE_HIT] = MeleeAttackCombo_Combo2AttackProjectileHitEffect.Object;

	WeaponSoundEffect.SetNum(MAX_SE_WEAPON);

	ConstructorHelpers::FObjectFinder<USoundBase> MeleeAttackCombo_FinalAttack_ExplodeSE(TEXT("/Game/Resources/Sound/Rock/rock-destroy-6409.rock-destroy-6409"));
	ConstructorHelpers::FObjectFinder<USoundBase> MeleeAttackCombo_Combo2AttackProjectile_ExplodeSE(TEXT("/Game/Resources/Sound/Rock/small-rock-break-194553.small-rock-break-194553"));
	ConstructorHelpers::FObjectFinder<USoundBase> MeleeAttackCombo_Combo2AttackProjectile_LauncchSE(TEXT("/Game/Resources/Sound/Rock/stones-falling-6375.stones-falling-6375"));
	ConstructorHelpers::FObjectFinder<USoundBase> MeleeAttackCombo_Combo1AttackProjectile_LauncchSE(TEXT("/Game/Resources/Sound/Rock/rocks-6129.rocks-6129"));

	if (MeleeAttackCombo_FinalAttack_ExplodeSE.Succeeded()) WeaponSoundEffect[SE_MELEEATTACKCOMBO_3_EXPLODE] = MeleeAttackCombo_FinalAttack_ExplodeSE.Object;
	if (MeleeAttackCombo_Combo2AttackProjectile_ExplodeSE.Succeeded()) WeaponSoundEffect[SE_MELEEATTACKCOMBO_2_EXPLODE] = MeleeAttackCombo_Combo2AttackProjectile_ExplodeSE.Object;
	if (MeleeAttackCombo_Combo2AttackProjectile_LauncchSE.Succeeded()) WeaponSoundEffect[SE_MELEEATTACKCOMBO_2_LAUNCH] = MeleeAttackCombo_Combo2AttackProjectile_LauncchSE.Object;
	if (MeleeAttackCombo_Combo1AttackProjectile_LauncchSE.Succeeded()) WeaponSoundEffect[SE_MELEEATTACKCOMBO_1_LAUNCH] = MeleeAttackCombo_Combo1AttackProjectile_LauncchSE.Object;


	


	FireSocketEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireSocketEffet"));
	FireSocketEffectComponent->SetupAttachment(StaticMeshComponent);
	FireSocketEffectComponent->AttachToComponent(StaticMeshComponent, FAttachmentTransformRules::KeepRelativeTransform, "FireSocket");
	FireSocketEffectComponent->SetTemplate(WeaponAttackTrail.Object);

	FireSocketEffectComponent->SetAutoActivate(false);

	tempDamage0 = 2.8f;
	tempDamage1 = 3.2f;
	tempDamage2 = 3.5f;

	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACBattleStaff::OnPickUp);

	UStaticMesh* SM = StaticMeshComponent->GetStaticMesh();
	if (SM != nullptr) FireSocket = SM->FindSocket("FireSocket");


}

void ACBattleStaff::LMB_Triggered(struct AttackResult& AttackResult)
{
	float Stamina = 0.f;
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (!IsValid(PC)) return;
	if (!PC->GetState(PLAYER_ATTACKING) && !PC->GetState(PLAYER_ROLLING) && !PC->GetMovementComponent()->IsFalling())
	{
		PC->SetState(PLAYER_ATTACKING, true);
		PC->MeleeAttackCombo.ExecuteIfBound();
		RequiredStamina = 6.f;
	}
	if (!PC->GetContinueCombo())
	{
		PC->SetContinueCombo(true);
	}
	if (PC->GetState(PLAYER_COMBO_STACK_2) || PC->GetState(PLAYER_COMBO_STACK_3))
	{
		RequiredStamina = 4.f;
		DamageScale = 0.7f;
	}
	else DamageScale = 0.3f;
}

void ACBattleStaff::LMB_Completed(struct AttackResult& AttackResult)
{
}

void ACBattleStaff::RMB_Triggered(struct AttackResult& AttackResult)
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (!IsValid(PC)) return;

	float Stamina = 0.f;
	
	if (PC->GetState(PLAYER_COMBO_STACK_3))
	{
		UE_LOG(LogTemp, Log, TEXT("Combo 3 Stack"));
		PC->StopAnimMontage();
		if (PC->FinishAttack.ExecuteIfBound())
		{
			Stamina = 8.f;
			PC->SetState(PLAYER_ATTACKING, true);
			DamageScale = 1.2f;
			//CreateParticleSystem();
		}
	}
	else if (PC->GetState(PLAYER_COMBO_STACK_2))
	{
		UE_LOG(LogTemp, Log, TEXT("Combo 2 Stack"));
		PC->StopAnimMontage();
		if (PC->Combo2Attack.ExecuteIfBound())
		{
			Stamina = 6.f;
			PC->SetContinueCombo(true);
			PC->SetState(PLAYER_ATTACKING, true);
			DamageScale = 0.5f;
		}
	}
	else if (PC->GetState(PLAYER_COMBO_STACK_1))
	{
		Stamina = 2.f;
		UE_LOG(LogTemp, Log, TEXT("Combo 1 Stack"));
		PC->StopAnimMontage();
		if (PC->Combo1Attack.ExecuteIfBound())
		{
			PC->SetContinueCombo(true);
			PC->SetState(PLAYER_ATTACKING, true);
			DamageScale = 0.2f;
		}
	}
	AttackResult.StaminaUsed = Stamina;
}

float ACBattleStaff::GettempDamage0()
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(PC->GetController());
	if (UIController == nullptr) return AttackDamage * tempDamage0;
	ItemStat temp;
	UIController->EquippedItemStat(temp);
	return temp._AttackDamage * tempDamage0;
}

float ACBattleStaff::GettempDamage1()
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(PC->GetController());
	if (UIController == nullptr) return AttackDamage * tempDamage1;
	ItemStat temp;
	UIController->EquippedItemStat(temp);
	return temp._AttackDamage * tempDamage1;

}

float ACBattleStaff::GettempDamage2()
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(PC->GetController());
	if (UIController == nullptr) return AttackDamage * tempDamage2;
	ItemStat temp;
	UIController->EquippedItemStat(temp);
	return temp._AttackDamage * tempDamage2;
}

void ACBattleStaff::SetIsEquiped(bool e)
{
	IsEquiped = e;
	if (e)
	{
		Collider->OnComponentBeginOverlap.RemoveDynamic(this, &ACBattleStaff::OnPickUp);
	}
	else
	{
		Collider->OnComponentBeginOverlap.AddDynamic(this, &ACBattleStaff::OnPickUp);
	}
}

void ACBattleStaff::OnPickUp(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACPlayerCharacter* PlayerCharacter = Cast<ACPlayerCharacter>(OtherActor))
	{
		ACPlayerController* PCC = Cast<ACPlayerController>(PlayerCharacter->GetController());
		UCInventoryItemData* ID = GetItemData(PlayerCharacter);
		PCC->AddInventoryItem(ID);
		//UE_LOG(LogTemp, Log, TEXT("Equipping Item : %s"), *ID->GetstrName());
		this->Destroy();
	}
}

void ACBattleStaff::SpawnEmitterAttachedToSocket()
{
	//UStaticMeshSocket* FireSocket = StaticMeshComponent->GetStaticMesh()->FindSocket("FireSocket");
	if (FireSocket == nullptr) return;
	FVector FireSocketLocation = GetActorLocation() + GetActorRotation().RotateVector(FireSocket->RelativeLocation);

	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponEffect[E_MELLEWEAPON_ATTACKING_EFFECT], FireSocketLocation);
	UGameplayStatics::SpawnEmitterAttached(
		WeaponEffect[E_MELLEWEAPON_ATTACKING_EFFECT],
		StaticMeshComponent,
		"FireSocket",
		FVector::ZeroVector,
		FRotator(90.f, 90.f, 0.f)
	);
}

void ACBattleStaff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsEquiped)
	{
		SetActorRotation(GetActorRotation() + FRotator(0.f, 3.f, 0.f));
	}

	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (!IsValid(PC)) return;
	if (PC->GetState(PLAYER_ATTACKING))
	{
		FireSocketEffectComponent->SetActive(true);
	}
	else {
		FireSocketEffectComponent->SetActive(false);
	}

	if (FireSocket == nullptr) return;
	FTransform FireSocketTransform;
	FireSocket->GetSocketTransform(FireSocketTransform, StaticMeshComponent);
	SwingingDirection = (FireSocketTransform.GetLocation() - PrevFireSocketPos);
	//DrawDebugLine(GetWorld(), PrevFireSocketPos, PrevFireSocketPos + Direction * 300.f, FColor::Cyan, false, 0.1f, 0U, 3.f);
	PrevFireSocketPos = FireSocketTransform.GetLocation();
}

bool ACBattleStaff::MeleeAttackHitCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, GetAttachParentActor());
	//FCollisionObjectQueryParams OQP(ECollisionChannel::ECC_Pawn);
	FCollisionObjectQueryParams OQP(PlayerAttackChannel);
	//FVector FireSocketLocation = 
	FTransform FireSocketTransform;
	//UStaticMesh* SM = StaticMeshComponent->GetStaticMesh();
	//UStaticMeshSocket* FireSocket = SM->FindSocket("FireSocket");
	if (FireSocket != nullptr) FireSocket->GetSocketTransform(FireSocketTransform, StaticMeshComponent);

	bool bResult = GetWorld()->SweepSingleByObjectType(
		HitResult,
		FireSocketTransform.GetLocation(),
		FireSocketTransform.GetLocation(),
		FQuat::Identity,
		OQP,
		FCollisionShape::MakeSphere(30.f),
		Params
	);
	//if (bResult) UE_LOG(LogTemp, Log, TEXT("Hit At Actor : %s"), *HitResult.GetActor()->GetName());
	//if (bResult) UE_LOG(LogTemp, Log, TEXT("Hit At Component : %s"), *HitResult.GetComponent()->GetFullName());
	//if (bResult) UE_LOG(LogTemp, Log, TEXT("Hit At Actor : %s"), *HitResult.GetActor()->GetFullName());

	if (bResult)
	{
		ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(HitResult.GetActor());
		if (EC == nullptr) return false;
		ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetAttachParentActor());
		if (PC == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("AttachParentActor is not ACPlayerCharacter"));
			return false;
		}

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), StaffMeleeHitSoundCue, GetActorLocation());

		UE_LOG(LogTemp, Log, TEXT("Attack Damage : %f, Damage Scale : %f"), AttackDamage, DamageScale);

		EC->HitDamage(AttackDamage * DamageScale, *PC, HitResult.Location);

		FTransform HitEffectSpawnTransform;
		HitEffectSpawnTransform.SetLocation(HitResult.Location);
		FRotator HitEffectTempRot = FRotationMatrix::MakeFromX(SwingingDirection.GetSafeNormal()).Rotator();
		HitEffectSpawnTransform.SetRotation(FQuat(HitEffectTempRot));
		HitEffectSpawnTransform.SetScale3D(FVector(0.5f, 0.5f, 0.5f));

		UParticleSystemComponent* tempParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponEffect[E_MELLEWEAPON_ATTACK_HIT], HitEffectSpawnTransform);
		if (tempParticle != nullptr)
		{
			HitParticleQueue.Enqueue(tempParticle);
			GetWorld()->GetTimerManager().SetTimer(EffectSpawnTimerHandler, this, &ACBattleStaff::DequeueHitParticle, 0.5f);
		}
	}

	return bResult;
}

UParticleSystem* ACBattleStaff::GetWeaponEffect(int e)
{
	return WeaponEffect.IsValidIndex(e) ? WeaponEffect[e] : WeaponEffect[0];
}

USoundBase* ACBattleStaff::GetWeaponSoundEffect(int e)
{
	return WeaponSoundEffect.IsValidIndex(e) ? WeaponSoundEffect[e] : nullptr;
}

TArray<UParticleSystem*>* ACBattleStaff::GetWeaponEffect()
{
	return &(WeaponEffect);
}

UStaticMeshSocket* ACBattleStaff::GetSocket(FName e)
{
	UStaticMesh* SM = StaticMeshComponent->GetStaticMesh();
	return SM->FindSocket(e);
}

UStaticMeshComponent* ACBattleStaff::GetStaticMeshComponent()
{
	return StaticMeshComponent;
}

void ACBattleStaff::GetSocketTransform(FTransform& SocketTransform, FName SocketName)
{
	UStaticMesh* SM = StaticMeshComponent->GetStaticMesh();
	SM->FindSocket(SocketName)->GetSocketTransform(SocketTransform, StaticMeshComponent);
}

//void ACBattleStaff::Combo2(ACPlayerCharacter* PC)
//{
//	PC->SetState(PLAYER_ATTACKING, true);
//	PC->SetState(PLAYER_COMBO_STACK_2, true);
//	PC->MeleeAttackCombo2.ExecuteIfBound();
//}
//
//void ACBattleStaff::Combo3(ACPlayerCharacter* PC)
//{
//	PC->SetState(PLAYER_ATTACKING, true);
//	PC->SetState(PLAYER_COMBO_STACK_3, true);
//	PC->MeleeAttackCombo3.ExecuteIfBound();
//}
UCInventoryItemData* ACBattleStaff::GetItemData(ACharacter* PC)
{
	UCInventoryItemData* ID = NewObject<UCInventoryItemData>(PC, UCInventoryItemData::StaticClass(), WeaponName);
	ID->SetIconTexture(ItemData_IconTexture);
	ID->SetPrice(ItemData_ItemPrice);
	ID->SetDT_RowName(ItemDTRowName);
	//ID->SetAttackType(ItemData_AttackType);
	ID->SetItemType(0);
	//ID->SetAttackDamage(AttackDamage);
	ID->SetItemStats(
		AttackDamage
	);
	ID->SetstrName(WeaponName.ToString());
	ID->SetItemClass(ACBattleStaff::StaticClass());
	return ID;
}

void ACBattleStaff::DequeueHitParticle()
{
	UParticleSystemComponent* temp;
	HitParticleQueue.Dequeue(temp);
	if (temp != nullptr) temp->Deactivate();
}

void ACBattleStaff::CreateParticleSystem()
{
}

//void ACBattleStaff::Combo1Attack(ACPlayerCharacter* PC)
//{
//	PC->StopAnimMontage();
//	if (PC->Combo1Attack.ExecuteIfBound())
//	{
//		PC->SetContinueCombo(true);
//		PC->SetState(PLAYER_ATTACKING, true);
//		DamageScale = 0.2f;
//	}
//}
//
//void ACBattleStaff::Combo2Attack(ACPlayerCharacter* PC)
//{
//}
//
//void ACBattleStaff::Combo3Attack(ACPlayerCharacter* PC)
//{
//}
