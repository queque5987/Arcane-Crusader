#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_EnemyTurn.generated.h"

UCLASS()
class MMB_API UCAnimNotifyState_EnemyTurn : public UAnimNotifyState
{
	GENERATED_BODY()

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	float TotalClock;
	float ElipsedTime;
	class IIEnemyStateManager* ESM;
	class AActor* Owner;
	class AActor* TurnDestinationCharacter;
	FVector TurnDestination;
	FRotator InitRotation;
};
