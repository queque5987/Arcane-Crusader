#include "CEnemy_Dragon.h"
#include "CEnemyAIController_Dragon.h"
#include "CProjectile.h"

ACEnemy_Dragon::ACEnemy_Dragon() : Super()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> SKFinder(TEXT("/Game/Enemy/MountainDragon/Meshes/SK_MOUNTAIN_DRAGON.SK_MOUNTAIN_DRAGON"));
	if (SKFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SKFinder.Object);
		GetMesh()->SetWorldRotation(FRotator(0.f, -90.f, 0.f));
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -210.f));
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(200.f);
	GetCapsuleComponent()->SetCapsuleRadius(200.f);

	AIControllerClass = ACEnemyAIController_Dragon::StaticClass();
	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	ConstructorHelpers::FObjectFinder<UParticleSystem> FlameThrower(TEXT("/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Fire/P_flamethrower"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> FireBall(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/Fire/combat/P_FireBall_Strong"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> FireBallExplode(TEXT("/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Gruntling/Bomber/P_BomberExplode"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> AttackCharge(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/Fire/combat/P_Shout_Charge_Fire_02"));
	
	EnemyAttackEffect.SetNum(MAX_E_ENEMEYATTACK);
	if (FlameThrower.Succeeded()) EnemyAttackEffect[E_ENEMYATTACK_FLAMETHROWER] = FlameThrower.Object;
	if (FlameThrower.Succeeded()) EnemyAttackEffect[E_ENEMYATTACK_FIREBALL] = FireBall.Object;
	if (FlameThrower.Succeeded()) EnemyAttackEffect[E_ENEMYATTACK_FIREBALL_EXPLODE] = FireBallExplode.Object;
	if (FlameThrower.Succeeded()) EnemyAttackEffect[E_ENEMYATTACK_ATTACK_CHARGE] = AttackCharge.Object;
}

void ACEnemy_Dragon::Land()
{
	StopAnimMontage();
	Delegate_StationaryToLand.ExecuteIfBound();
}

void ACEnemy_Dragon::SetPlayingSequence(bool e)
{
	Delegate_SetPlayingSequence.ExecuteIfBound(e);
}

void ACEnemy_Dragon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FString AnimBPAdderss = "Class'/Game/Enemy/MountainDragon/Blueprint/BP_AnimBP_Dragon.BP_AnimBP_Dragon_C'";
	UClass* tempAnimBP = LoadObject<UClass>(nullptr, *AnimBPAdderss);
	if (!tempAnimBP) return;
	GetMesh()->SetAnimInstanceClass(tempAnimBP);

	BoneNameArr[ENEMY_ATTACK_RHAND		] = FName("MOUNTAIN_DRAGON_-R-Finger12");
	BoneNameArr[ENEMY_ATTACK_RHAND_E	] = FName("MOUNTAIN_DRAGON_-R-Hand");
	BoneNameArr[ENEMY_ATTACK_HEAD		] = FName("");
	BoneNameArr[ENEMY_ATTACK_HEAD_E		] = FName("");
	BoneNameArr[ENEMY_ATTACK_MOUTH		] = FName("MOUNTAIN_DRAGON_-Neck5");
	BoneNameArr[ENEMY_ATTACK_MOUTH_E	] = FName("MOUNTAIN_DRAGON_-Ponytail1");
	BoneNameArr[ENEMY_ATTACK_LHAND		] = FName("MOUNTAIN_DRAGON_-L-Hand");
	BoneNameArr[ENEMY_ATTACK_LHAND_E	] = FName("MOUNTAIN_DRAGON_-L-Finger12");
	BoneNameArr[ENEMY_ATTACK_WINGS		] = FName("");
	BoneNameArr[ENEMY_ATTACK_WINGS_E	] = FName("");
	BoneNameArr[ENEMY_ATTACK_WINGS_R	] = FName("");
	BoneNameArr[ENEMY_ATTACK_WINGS_R_E	] = FName("");

	ArmRadius = 120.f;
	HeadRadius = 80.f;
}

void ACEnemy_Dragon::FreeFall()
{
	bStartedToFall = false;
	Delegate_Fall.ExecuteIfBound();
}

bool ACEnemy_Dragon::IsStartedToFall()
{
	return bStartedToFall;
}

void ACEnemy_Dragon::FreeFall_Init()
{
	bStartedToFall = true;
	Delegate_StationaryToFall.ExecuteIfBound();
}

void ACEnemy_Dragon::DoAttack(int32 AttackType)
{
	if (bAttacking) return;
	
	switch (AttackType)
	{
	case(ENEMY_ATTACK_MOUTH):
		if (Delegate_BiteAttack.ExecuteIfBound()) SetbAttacking(true);
		break;
	case(ENEMY_ATTACK_LHAND):
		if (Delegate_LClawAttack.ExecuteIfBound()) SetbAttacking(true);
		break;
	case(ENEMY_ATTACK_RHAND):
		if (Delegate_RClawAttack.ExecuteIfBound()) SetbAttacking(true);
		break;
	case(ENEMY_ATTACK_WINGS): //4 Combo
		if (Delegate_ClawComboAttack.ExecuteIfBound()) SetbAttacking(true);
		break;
	case(ENEMY_ATTACK_TURN_L):
		if (Delegate_TurnLeft.ExecuteIfBound()) SetbAttacking(true);
		break;
	case(ENEMY_ATTACK_TURN_R):
		if (Delegate_TurnRight.ExecuteIfBound())  SetbAttacking(true);
		break;
	case(16):
		if (Delegate_FireBallAttack.ExecuteIfBound())  SetbAttacking(true);
		break;
	case(18):
		if (Delegate_FireBreathAttack.ExecuteIfBound())  SetbAttacking(true);
		break;
	default:
		break;
	}
}

void ACEnemy_Dragon::BiteGraspPlayer()
{
	ACharacter* TargetPlayer = GetDealingPlayer();
	if (TargetPlayer == nullptr) return;
	IIPlayerState* PS = Cast<IIPlayerState>(TargetPlayer);
	if (PS == nullptr || PS->GetState(PLAYER_RAGDOLL)) return;

	bAttacking_Comboing = true;
	if (Delegate_BiteGrasp.ExecuteIfBound()) SetbAttacking(true);
	PS->Grasped(*this, BoneNameArr[ENEMY_ATTACK_MOUTH]);
}

void ACEnemy_Dragon::BiteGraspEndPlayer()
{
	ACharacter* TargetPlayer = GetDealingPlayer();
	if (TargetPlayer == nullptr) return;
	IIPlayerState* PS = Cast<IIPlayerState>(TargetPlayer);
	if (PS == nullptr) return;

	PS->UnGrasp();
	//PS->SetState(PLAYER_ROLLING, false);
	//PS->OnHitDown();

	TargetPlayer->GetMesh()->SetAllPhysicsLinearVelocity(TargetPlayer->GetMesh()->GetPhysicsLinearVelocity() / 100.f + FVector::DownVector * 500.f);
	//TargetPlayer->LaunchCharacter(FVector::DownVector * 500.f, true, true);
}

UParticleSystem* ACEnemy_Dragon::GetParticleSystem(int e)
{
	return EnemyAttackEffect.IsValidIndex(e) ? EnemyAttackEffect[e] : nullptr;
}

bool ACEnemy_Dragon::IsBusy()
{
	return Super::IsBusy() || bStartedToFall;
}

void ACEnemy_Dragon::SpitFireBall(bool bFireImmediate)
{
	if (bFireImmediate)
	{
		ACharacter* DealingCharacter = GetDealingPlayer();
		FVector TargetLocation = DealingCharacter != nullptr ? DealingCharacter->GetActorLocation() : GetActorLocation() + GetActorForwardVector() * 1500.f;
		FVector MouthLocation = GetMesh()->GetBoneLocation("MOUNTAIN_DRAGON_-Head");

		FVector Direction = (TargetLocation - MouthLocation).GetSafeNormal();

		ACProjectile* Proj = GetWorld()->SpawnActor<ACProjectile>(
			ACProjectile::StaticClass(), MouthLocation, Direction.Rotation()
		);
		Proj->SetLaunch(
			this,
			EnemyAttackEffect[E_ENEMYATTACK_FIREBALL],
			EnemyAttackEffect[E_ENEMYATTACK_FIREBALL_EXPLODE],
			nullptr,
			nullptr,
			20.f,
			4500.f,
			90.f,
			3.f,
			nullptr,
			false,
			false,
			false
		);
		Proj->SetProjectileScae(FVector(5.f));
		Proj->SetProjCollisionScale(150.f);
	}
	else
	{
		UGameplayStatics::SpawnEmitterAttached(
			EnemyAttackEffect[E_ENEMYATTACK_ATTACK_CHARGE],
			GetMesh(),
			"MOUNTAIN_DRAGON_-Head"
		);
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EnemyAttackEffect[E_ENEMYATTACK_ATTACK_CHARGE],
		//	GetMesh()->GetBoneTransform(GetMesh()->GetBoneIndex("MOUNTAIN_DRAGON_-Head"))
		//);
	}
}
