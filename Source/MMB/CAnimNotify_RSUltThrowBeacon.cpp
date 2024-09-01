#include "CAnimNotify_RSUltThrowBeacon.h"
#include "IPlayerState.h"

void UCAnimNotify_RSUltThrowBeacon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	IIPlayerState* PlayerState = Cast<IIPlayerState>(MeshComp->GetOwner());
	if (PlayerState == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UCAnimNotify_RSUltThrowBeacon Player Can Not Find"));
		return;
	}
	if (ThrowBeacon)
	{
		PlayerState->ThrowBeacon();
		return;
	}

	PlayerState->SwitchWeaponHoldingHand(ToLeft);
	if (ToLeft)
	{
		PlayerState->SpawnAndGraspBeacon();
	}
}
