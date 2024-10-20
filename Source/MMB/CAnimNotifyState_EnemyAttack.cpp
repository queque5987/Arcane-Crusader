#include "CAnimNotifyState_EnemyAttack.h"
#include "IEnemyStateManager.h"

void UCAnimNotifyState_EnemyAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	ContinueAttack = true;
	EC = Cast<IIEnemyStateManager>(MeshComp->GetOwner());
	if (AttackType < 6) return;
	if (EC == nullptr) return;

	EC->SpitFireBall(false);
}

void UCAnimNotifyState_EnemyAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	if (!ContinueAttack) return;
	if (AttackType > 5) return;
	if (EC == nullptr) return;

	ContinueAttack = !EC->AttackHitCheck(AttackType * 2, DamageScale);
}

void UCAnimNotifyState_EnemyAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (AttackType < 6) return;
	if (EC == nullptr) return;

	EC->SpitFireBall(true);
}
