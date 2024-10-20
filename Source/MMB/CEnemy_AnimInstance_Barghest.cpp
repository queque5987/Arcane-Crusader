#include "CEnemy_AnimInstance_Barghest.h"
#include "CEnemyCharacter.h"

UCEnemy_AnimInstance_Barghest::UCEnemy_AnimInstance_Barghest()
{
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> BiteFinder(TEXT("/Game/Enemy/Barghest/Animation/BARGHEST_biteAggressive"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> HitReactFinder(TEXT("/Game/Enemy/Barghest/Animation/BARGHEST_getHitNormal"));

	if (BiteFinder.Succeeded())			AnimSequenceAttackMouth = BiteFinder.Object;
	if (HitReactFinder.Succeeded())		AnimSequenceHitReact = HitReactFinder.Object;
}

void UCEnemy_AnimInstance_Barghest::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	EnemyCharacter = Cast<ACEnemyCharacter>(TryGetPawnOwner());
	if (EnemyCharacter != nullptr)
	{
		//EnemyCharacter->DoRoar.BindUFunction(this, TEXT("Roar"));
		//EnemyCharacter->DoAttackHand.BindUFunction(this, TEXT("AttackHand"));
		//EnemyCharacter->DoAttackHead.BindUFunction(this, TEXT("AttackHead"));
		EnemyCharacter->DoAttackMouth.BindUFunction(this, TEXT("AttackMouth"));
		EnemyCharacter->DoHitReact.BindUFunction(this, TEXT("HitReact"));
	}

}

void UCEnemy_AnimInstance_Barghest::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UCEnemy_AnimInstance_Barghest::AttackMouth()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceAttackMouth, "DefaultSlot", 0.25f, 0.25f, PlayRate);
}

void UCEnemy_AnimInstance_Barghest::HitReact()
{
	PlaySlotAnimationAsDynamicMontage(AnimSequenceHitReact, "DefaultSlot", 0.25f, 0.25f, PlayRate);
}
