#include "CAttackEndNotify.h"
#include "IPlayerState.h"

void UCAttackEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	
	PC = Cast<IIPlayerState>(MeshComp->GetOwner());
	if (PC != nullptr)
	{
		PC->SetState(PLAYER_ATTACKING, false);
		PC->SetState(PLAYER_ULT_INVINCIBLE, false);
		PC->SetState(PLAYER_COMBO_STACK_1, false);
		PC->SetState(PLAYER_COMBO_STACK_2, false);
		PC->SetState(PLAYER_COMBO_STACK_3, false);
		PC->SetState(PLAYER_ATTACK_CANCLE_UNLOCK, false);
		PC->WeaponEffectDeactivate();
	}
}
