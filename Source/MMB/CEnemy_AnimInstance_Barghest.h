#pragma once

#include "CoreMinimal.h"
#include "CEnemyAnimInstance.h"
#include "CEnemy_AnimInstance_Barghest.generated.h"

UCLASS()
class MMB_API UCEnemy_AnimInstance_Barghest : public UCEnemyAnimInstance
{
	GENERATED_BODY()
	
	UCEnemy_AnimInstance_Barghest();

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void AttackMouth() override;
	virtual void HitReact() override;
};
