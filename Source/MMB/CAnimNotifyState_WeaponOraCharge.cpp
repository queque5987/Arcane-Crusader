#include "CAnimNotifyState_WeaponOraCharge.h"
#include "IPlayerState.h"

void UCAnimNotifyState_WeaponOraCharge::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Charging = 0.f;
	Length = TotalDuration;

	PlayerState = Cast<IIPlayerState>(MeshComp->GetOwner());
	if (PlayerState == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UCAnimNotifyState_WeaponOraCharge Player Can Not Find"));
		return;
	}
	PlayerState->SetWeaponEffectCharge(0.f, IsLeft);
}

void UCAnimNotifyState_WeaponOraCharge::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (PlayerState == nullptr) return;
	
	Charging += FrameDeltaTime * ChargingSpeed;

	PlayerState->SetWeaponEffectCharge(Charging / Length, IsLeft);
}

void UCAnimNotifyState_WeaponOraCharge::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (PlayerState == nullptr) return;
}
