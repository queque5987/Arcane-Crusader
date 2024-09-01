#pragma once

#include "CoreMinimal.h"
#include "CAnimNotifyState_PlayerComboWait.h"
#include "CAnimNotifyState_PlayerComboIn1.generated.h"

UCLASS()
class MMB_API UCAnimNotifyState_PlayerComboIn1 : public UCAnimNotifyState_PlayerComboWait
{
	GENERATED_BODY()
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
