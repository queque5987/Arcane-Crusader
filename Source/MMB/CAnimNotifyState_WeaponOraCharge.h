#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_WeaponOraCharge.generated.h"

UCLASS()
class MMB_API UCAnimNotifyState_WeaponOraCharge : public UAnimNotifyState
{
	GENERATED_BODY()

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	float Length;
	float Charging;
	class IIPlayerState* PlayerState;
public:
	UPROPERTY(EditAnywhere)
	bool IsLeft;
	UPROPERTY(EditAnywhere)
	float ChargingSpeed = 1.f;
};
