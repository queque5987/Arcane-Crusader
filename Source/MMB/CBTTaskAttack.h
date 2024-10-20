#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskAttack.generated.h"

UCLASS()
class MMB_API UCBTTaskAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCBTTaskAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY(EditAnywhere)
	int32 AttackType;
protected:
	virtual void DoAttack(class ACEnemyCharacter* EC);
};
