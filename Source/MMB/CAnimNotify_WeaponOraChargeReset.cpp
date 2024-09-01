#include "CAnimNotify_WeaponOraChargeReset.h"
#include "IPlayerState.h"

void UCAnimNotify_WeaponOraChargeReset::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	IIPlayerState* PlayerState = Cast<IIPlayerState>(MeshComp->GetOwner());
	if (PlayerState == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UCAnimNotify_WeaponOraChargeReset Player Can Not Find"));
		return;
	}
	PlayerState->SetWeaponEffectCharge(0.f, IsLeft);
}
