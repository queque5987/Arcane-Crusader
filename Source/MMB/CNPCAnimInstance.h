// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CNPCAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCNPCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	int32 NPCPose;
	// 0 :Idle, 1 : Talking, 2 : Thankful, 3 : Disappointed, 4 : Bow
	void SetNPCPose(int32 e) { NPCPose = e; }
};
