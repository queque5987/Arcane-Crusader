// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PCH.h"
#include "CPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	UCPlayerAnimInstance();
public:
	virtual void NativeInitializeAnimation() override;
protected:
	UPROPERTY(BlueprintReadOnly)
	APawn* Pawn;
	UPROPERTY(BlueprintReadOnly)
	bool IsAir;
	UPROPERTY(BlueprintReadOnly)
	float MovementSpeed;
	UPROPERTY(BlueprintReadOnly)
	float ZSpeed;
	UPROPERTY(BlueprintReadOnly)
	float PawnAnimRadian;
	UPROPERTY(BlueprintReadOnly)
	bool RopeClimbing;
	UPROPERTY(BlueprintReadOnly)
	bool bHitDown;
	UPROPERTY(BlueprintReadOnly)
	bool Died;

	class IIPlayerState* PlayerCharacterStateInterface;

	UAnimSequenceBase* AnimSequenceLMBAttack;
	UAnimSequenceBase* AnimSequenceRMBCastStart;
	UAnimSequenceBase* AnimSequenceRMBCastOngoing;
	UAnimSequenceBase* AnimSequenceMeleeCombo;

	UAnimSequenceBase* AnimSequenceMeleeCombo1;
	UAnimSequenceBase* AnimSequenceMeleeCombo2;
	UAnimSequenceBase* AnimSequenceMeleeCombo3;

	UAnimSequenceBase* AnimSequenceMeleeFinishAttack;
	UAnimSequenceBase* AnimSequenceMelee1ComboAttack;
	UAnimSequenceBase* AnimSequenceMelee2ComboAttack;
	UAnimSequenceBase* AnimSequenceStandToRoll;
	UAnimSequenceBase* AnimSequenceHitDown;
	UAnimSequenceBase* AnimSequenceHitDownRecover;
	UAnimSequenceBase* AnimSequenceDizzy;

	UAnimSequenceBase* AnimSequenceRopeClimb;

	UAnimSequenceBase* AnimSequenceJumpPointReady;
	UAnimSequenceBase* AnimSequenceJumpPointJump;
	UAnimSequenceBase* AnimSequenceJumpPointLand;
	UAnimSequenceBase* AnimSequenceDie;
	UAnimSequenceBase* AnimSequenceHitReact;

	UFUNCTION(BlueprintCallable)
	void UpdateProperties(float Delta);
	UFUNCTION()
	void LMBAttack();
	UFUNCTION()
	void RMBAttack();
	UFUNCTION()
	void RMBCastOngoing();
	UFUNCTION()
	void MeleeAttackCombo();
	UFUNCTION()
	void MeleeAttackCombo1();
	UFUNCTION()
	void MeleeAttackCombo2();
	UFUNCTION()
	void MeleeAttackCombo3();
	UFUNCTION()
	void FinishAttack();
	UFUNCTION()
	void Combo1Attack();
	UFUNCTION()
	void Combo2Attack();
	UFUNCTION()
	void StandToRoll();
	UFUNCTION()
	void HitDown();
	UFUNCTION()
	void HitDownRecover();
	UFUNCTION()
	void Dizzy();
	UFUNCTION()
	void RopeClimb();
	UFUNCTION()
	void JumpPoint_Ready();
	UFUNCTION()
	void JumpPoint_Jump(float e);
	UFUNCTION()
	void JumpPoint_Land();
	UFUNCTION()
	void Die();
	UFUNCTION()
	void HitReact();
};
