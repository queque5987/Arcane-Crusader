// Fill out your copyright notice in the Description page of Project Settings.


#include "CBattleStaff.h"

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





	ConstructorHelpers::FObjectFinder<UStaticMesh> BattleStaffMeshFinder(TEXT("/Game/BattleWizardPolyart/Meshes/MagicStaffs/Staff01SM.Staff01SM"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> MeleeAttackCombo_ExplodeEffect(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_RockBurst/P_RBurst_Default_Burst_Area_01.P_RBurst_Default_Burst_Area_01"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> MeleeAttackCombo_FinalAttackExplode(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_RockBurst/P_RBurst_Default_Burst_SinkH_01.P_RBurst_Default_Burst_SinkH_01"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> MeleeAttackCombo_FinalAttackBonusExplode(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_RockBurst/P_RBurst_Default_Burst_Stalag_01.P_RBurst_Default_Burst_Stalag_01"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> MeleeAttackCombo_Combo2AttackExplode(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_RockBurst/P_RBurst_Default_Charge_Slam_01.P_RBurst_Default_Charge_Slam_01"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> MeleeAttackHitEffect(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_RockBurst/P_RBurst_Base_Charge_01.P_RBurst_Base_Charge_01"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> MeleeAttackCombo_Combo1AttackProjectileEffect(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/combat/P_ProjectileLob_Bomblet_Untyped.P_ProjectileLob_Bomblet_Untyped"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> MeleeAttackCombo_Combo1AttackProjectileExplode(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/combat/P_ProjectileLob_Explo_Untyped.P_ProjectileLob_Explo_Untyped"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> MeleeAttackCombo_Combo1AttackProjectileLaunchEffect(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/combat/P_Shout_00.P_Shout_00"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> MeleeAttackCombo_Combo1AttackProjectileSpawnEffect(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/combat/P_Shout_Charge_00.P_Shout_Charge_00"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> MeleeAttackCombo_Combo2AttackProjectileEffect(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/combat/P_LineToPoint_Projectile_Untyped.P_LineToPoint_Projectile_Untyped"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> WeaponAttackingEffect(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/Fire/P_Beam_Laser_Dot.P_Beam_Laser_Dot"));
	//ConstructorHelpers::FObjectFinder<UParticleSystem> WeaponAttackingEffect(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_WeaponThrow/P_Skill_Throw_Fire_Charge_01.P_Skill_Throw_Fire_Charge_01"));


	//ParticleSystemExplode = ExplodeFinder.Object;
	StaticMeshComponent->SetStaticMesh(BattleStaffMeshFinder.Object);

	//WeaponEffect[E_MELEEATTACKCOMBO_3_EXPLODE] = MeleeAttackCombo_FinalAttackExplode.Object;
	WeaponEffect[E_MELEEATTACKCOMBO_3_EXPLODE] = MeleeAttackCombo_Combo2AttackExplode.Object;;
	WeaponEffect[E_MELEEATTACKCOMBO_3_FINALATTACK_EXPLODE] = MeleeAttackCombo_ExplodeEffect.Object;
	WeaponEffect[E_MELEEATTACKCOMBO_3_FINALATTACK_BONUS_EXPLODE] = MeleeAttackCombo_FinalAttackBonusExplode.Object;
	WeaponEffect[E_MELEEATTACKCOMBO_2_EXPLODE] = MeleeAttackCombo_Combo2AttackExplode.Object;
	WeaponEffect[E_MELEEATTACK_HITEFFECT] = MeleeAttackHitEffect.Object;
	WeaponEffect[E_MELEEATTACKCOMBO_1_PROJECTILE] = MeleeAttackCombo_Combo1AttackProjectileEffect.Object;
	WeaponEffect[E_MELLEATTACKCOMBO_1_PROJECTILE_EXPLODE] = MeleeAttackCombo_Combo1AttackProjectileExplode.Object;
	WeaponEffect[E_MELLEATTACKCOMBO_1_PROJECTILE_LAUNCH] = MeleeAttackCombo_Combo1AttackProjectileLaunchEffect.Object;
	WeaponEffect[E_MELLEATTACKCOMBO_1_PROJECTILE_SPAWN] = MeleeAttackCombo_Combo1AttackProjectileSpawnEffect.Object;
	WeaponEffect[E_MELLEATTACKCOMBO_2_PROJECTILE] = MeleeAttackCombo_Combo2AttackProjectileEffect.Object;
	WeaponEffect[E_MELLEWEAPON_ATTACKING_EFFECT] = WeaponAttackingEffect.Object;

	FireSocketEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireSocketEffet"));
	FireSocketEffectComponent->SetupAttachment(StaticMeshComponent);
	FireSocketEffectComponent->AttachToComponent(StaticMeshComponent, FAttachmentTransformRules::KeepRelativeTransform, "FireSocket");
	FireSocketEffectComponent->SetTemplate(WeaponAttackingEffect.Object);
	FireSocketEffectComponent->SetAutoActivate(false);
	//StaticMeshComponent->GetStaticMesh()->FindSocket("FireSocket");
	//FireSocketEffectComponent->SetRelativeTransform();

	tempDamage0 = 2.8f;
	tempDamage1 = 3.2f;
	tempDamage2 = 3.5f;

	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACBattleStaff::OnPickUp);
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
	//AttackResult.StaminaUsed = Stamina;

	//float Stamina = 0.f;

	//ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	//if (!IsValid(PC)) return;

	//if (PC->GetState(PLAYER_ATTACKING))
	//{
	//	PC->SetState(PLAYER_COMBO_CONTINUE, true);
	//}

	//if (!PC->GetState(PLAYER_ATTACKING) && !PC->GetState(PLAYER_ROLLING) && !PC->GetMovementComponent()->IsFalling())
	//{
	//	int CurrCombo = PC->GetState(PLAYER_COMBO_STACK_1) + PC->GetState(PLAYER_COMBO_STACK_2) + PC->GetState(PLAYER_COMBO_STACK_3);
	//	switch (CurrCombo)
	//	{
	//	case(0):
	//		PC->SetState(PLAYER_ATTACKING, true);
	//		PC->SetState(PLAYER_COMBO_STACK_1, true);
	//		PC->MeleeAttackCombo1.ExecuteIfBound();
	//		break;
	//	case(1):
	//		if (PC->GetState(PLAYER_COMBO_CONTINUE))FComboContinue = &ACBattleStaff::Combo2;
	//		break;
	//	case(2):
	//		if (PC->GetState(PLAYER_COMBO_CONTINUE)) FComboContinue = &ACBattleStaff::Combo3;
	//		break;
	//	}
	//	Stamina = 6.f;
	//}
	//AttackResult.StaminaUsed = Stamina;
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
	//else
	//{
	//	UE_LOG(LogTemp, Log, TEXT("Combo 0 Stack"));
	//}
	//return AttackResult();
}

//void ACBattleStaff::ComboContinue()
//{
//	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
//	if (!IsValid(PC)) return;
//
//	if (FComboContinue != nullptr) (this->*FComboContinue)(PC);
//}

float ACBattleStaff::GettempDamage0()
{
	return AttackDamage*tempDamage0;
}

float ACBattleStaff::GettempDamage1()
{
	return AttackDamage*tempDamage1;
}

float ACBattleStaff::GettempDamage2()
{
	return AttackDamage*tempDamage2;
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
	UStaticMeshSocket* FireSocket = StaticMeshComponent->GetStaticMesh()->FindSocket("FireSocket");
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
}

bool ACBattleStaff::MeleeAttackHitCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, GetAttachParentActor());
	//FCollisionObjectQueryParams OQP(ECollisionChannel::ECC_Pawn);
	FCollisionObjectQueryParams OQP(PlayerAttackChannel);
	//FVector FireSocketLocation = 
	FTransform FireSocketTransform;
	UStaticMesh* SM = StaticMeshComponent->GetStaticMesh();
	UStaticMeshSocket* FireSocket = SM->FindSocket("FireSocket");
	FireSocket->GetSocketTransform(FireSocketTransform, StaticMeshComponent);

	/*bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		FireSocketTransform.GetLocation(),
		FireSocketTransform.GetLocation(),
		FQuat::Identity,
		PlayerAttackChannel,
		FCollisionShape::MakeSphere(30.f),
		Params
	);*/

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
		UE_LOG(LogTemp, Log, TEXT("Attack Damage : %f, Damage Scale : %f"), AttackDamage, DamageScale);

		EC->HitDamage(AttackDamage * DamageScale, *PC, HitResult.Location);
	}

	return bResult;
}

UParticleSystem* ACBattleStaff::GetWeaponEffect(int e)
{
	return WeaponEffect.IsValidIndex(e) ? WeaponEffect[e] : WeaponEffect[0];
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
	ID->SetAttackType(ItemData_AttackType);
	ID->SetAttackDamage(AttackDamage);
	ID->SetstrName(WeaponName.ToString());
	ID->SetItemClass(ACBattleStaff::StaticClass());
	return ID;
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
