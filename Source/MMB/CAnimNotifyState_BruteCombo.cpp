#include "CAnimNotifyState_BruteCombo.h"
#include "PCH.h"
//#include "IPlayerState.h"

void UCAnimNotifyState_BruteCombo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	IIPlayerState* PlayerState = Cast<IIPlayerState>(MeshComp->GetOwner());
	if (PlayerState == nullptr) return;
	PlayerState->SetState(PLAYER_BRUTEMODE_COMBO_IN, true);
}

void UCAnimNotifyState_BruteCombo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	IIPlayerState* PlayerState = Cast<IIPlayerState>(MeshComp->GetOwner());
	if (PlayerState == nullptr) return;
	PlayerState->SetState(PLAYER_BRUTEMODE_COMBO_IN, false);
}
