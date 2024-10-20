#pragma once

#include "CoreMinimal.h"
#include "CEnemyAnimInstance.h"
#include "CEnemy_AnimInstance_Dragon.generated.h"

UCLASS()
class MMB_API UCEnemy_AnimInstance_Dragon : public UCEnemyAnimInstance
{
	GENERATED_BODY()

	UCEnemy_AnimInstance_Dragon();

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void UpdateProperties(float Delta) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bFalling;
	UPROPERTY(BlueprintReadOnly)
	bool PlayingSequence;
	UPROPERTY(BlueprintReadOnly)
	float FallCounter;

	FTimerHandle FallSafeTimer;

	UAnimSequenceBase* AnimSequenceFall;
	UAnimSequenceBase* AnimSequenceStationayToFall;
	UAnimSequenceBase* AnimSequenceStationayToLand;

	UAnimSequenceBase* AnimSequenceClawCombo;
	UAnimSequenceBase* AnimSequenceLeftClaw;
	UAnimSequenceBase* AnimSequenceRightClaw;
	UAnimSequenceBase* AnimSequenceBite;
	UAnimSequenceBase* AnimSequenceBiteGrasp;
	UAnimSequenceBase* AnimSequenceFireBall;
	UAnimSequenceBase* AnimSequenceFireBreath;

	UAnimSequenceBase* AnimSequenceTurnLeft;
	UAnimSequenceBase* AnimSequenceTurnRight;

	UAnimSequenceBase* AnimSequenceSpitFireBall;
	UAnimSequenceBase* AnimSequenceBreathFire;

	UFUNCTION()
	void SetPlayingSequence(bool e);

public:
	bool GetbFalling() { return bFalling; }
};
