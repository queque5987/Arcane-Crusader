#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_EnemyCallFunc.generated.h"

UCLASS()
class MMB_API UCAnimNotify_EnemyCallFunc : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	/*0 : Dragon, 1 : */
	UPROPERTY(EditAnywhere)
	int32 MonsterType;
	/*0 : Land, 1: Fall, 2 : GraspReleasePlayer?*/
	UPROPERTY(EditAnywhere)
	int32 ToCallFunc;
private:
	void CallFunc0(class ACEnemyCharacter* Character);
	void CallFunc1(class ACEnemyCharacter* Character);
	void CallFunc2(class ACEnemyCharacter* Character);
};
