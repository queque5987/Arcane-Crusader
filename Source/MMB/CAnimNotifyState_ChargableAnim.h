#pragma once

#include "CoreMinimal.h"
#include "CAnimNotifyState_AdjustPlayRate.h"
#include "CAnimNotifyState_ChargableAnim.generated.h"

UCLASS()
class MMB_API UCAnimNotifyState_ChargableAnim : public UCAnimNotifyState_AdjustPlayRate
{
	GENERATED_BODY()

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	bool ChargeFinished;

public:
	UPROPERTY(EditAnywhere)
	bool IsLMB;
};
