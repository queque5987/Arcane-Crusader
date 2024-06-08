// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CEnemyAnimInstance.h"
#include "CEnemy_AnimInstance_TB.generated.h"

UCLASS()
class MMB_API UCEnemy_AnimInstance_TB : public UCEnemyAnimInstance
{
	GENERATED_BODY()
	UCEnemy_AnimInstance_TB();
protected:
	UPROPERTY(BlueprintReadOnly)
	bool IsOnAir;
	UPROPERTY(BlueprintReadOnly)
	float MaxAltitude;
	UPROPERTY(BlueprintReadOnly)
	float CurrentAltitude;

	UAnimSequenceBase* AnimSequenceFire;
	UAnimSequenceBase* AnimSequenceFlyFire;
	UAnimSequenceBase* AnimSequenceLand;
	UAnimSequenceBase* AnimSequenceTakeOff;


public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void UpdateProperties(float Delta) override;
	virtual void Roar() override;
	virtual void AttackHand() override;
	virtual void AttackMouth() override;

	UFUNCTION()
	void AttackFire();
	UFUNCTION()
	void AttackFlyFire();
	UFUNCTION()
	void Land();
	UFUNCTION()
	void TakeOff();
	//UFUNCTION()
	//void ResetState();

	bool GetIsOnAir() { return IsOnAir; }
	void SetIsOnAir(bool e) { IsOnAir = e; }
};
