// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "IWeapon.h"
#include "CAnimNotify_SpawnEmitter.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCAnimNotify_SpawnEmitter : public UAnimNotify
{
	GENERATED_BODY()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
protected:
	class ACPlayerCharacter* PC;
	//class ACWeapon* WP;
	AActor* WP;
	FTransform FireSocketTransform;
	bool GetPlayerCharacter(USkeletalMeshComponent* MeshComp);
};
