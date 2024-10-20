#include "CAnimNotifyState_EnemyAtk_Mouth.h"
#include "IEnemyStateManager.h"

void UCAnimNotifyState_EnemyAtk_Mouth::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (ContinueAttack) return;
	// Grasped Player
	if (EC != nullptr)
	{
		EC->BiteGraspPlayer();
	}
}
