// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_AdjustPlayRate.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCAnimNotifyState_AdjustPlayRate : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	float PlayerAttackSpeed;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool AbsoluteSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InPlayRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OutPlayRate;
};
