#pragma once

#include "CoreMinimal.h"
#include "CAnimNotifyState_PlayerComboWait.h"
#include "CAnimNotifyState_PlayerComboIn2.generated.h"

UCLASS()
class MMB_API UCAnimNotifyState_PlayerComboIn2 : public UCAnimNotifyState_PlayerComboWait
{
	GENERATED_BODY()
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
