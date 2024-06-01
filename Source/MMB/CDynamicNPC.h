// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CStaticNPC.h"
//#include "Animation/AnimSequence.h"
#include "Animation/AnimBlueprint.h"
#include "Animation/AnimInstance.h"
#include "CDynamicNPC.generated.h"

UCLASS()
class MMB_API ACDynamicNPC : public ACStaticNPC
{
	GENERATED_BODY()

	ACDynamicNPC();

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* SKComponent;

	UPROPERTY(EditAnywhere)
	class UAnimBlueprint* NPCAnimBluperint;

	UPROPERTY(EditAnywhere)
	class UAnimSequence* Idle;

	UPROPERTY(EditAnywhere)
	class UAnimSequence* Talking;

	UPROPERTY(EditAnywhere)
	class UAnimSequence* Disappointed;

	UPROPERTY(EditAnywhere)
	class UAnimSequence* Thankful;

	UPROPERTY(EditAnywhere)
	class UAnimSequence* Bow;

	virtual void BeginPlay() override;

	class UCNPCAnimInstance* NPCAnimInstance;

	FTimerHandle PoseTimer;
public:
	// 0 :Idle, 1 : Talking, 2 : Thankful, 3 : Disappointed, 4 : Bow
	void SetNPCAnimation(int32 State);
	virtual void Initialize() override;
};
