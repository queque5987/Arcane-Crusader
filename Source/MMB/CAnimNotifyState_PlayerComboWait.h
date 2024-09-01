#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CPlayerCharacter.h"
#include "CAnimNotifyState_PlayerComboWait.generated.h"

UCLASS()
class MMB_API UCAnimNotifyState_PlayerComboWait : public UAnimNotifyState
{
	GENERATED_BODY()
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
protected:
	ACPlayerCharacter* PC;
	void ResetComboStack();
	bool GetPC(USkeletalMeshComponent* MeshComp);
};
