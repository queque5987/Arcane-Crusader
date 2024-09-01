#include "CAnimNotify_BSUltStaffThrow.h"
#include "IPlayerState.h"

void UCAnimNotify_BSUltStaffThrow::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	IIPlayerState* PlayerState = Cast<IIPlayerState>(MeshComp->GetOwner());
	if (PlayerState == nullptr) return;
	if (bThrow) PlayerState->ThrowStaffEffect();
	else PlayerState->TurnBruteMode();
}
