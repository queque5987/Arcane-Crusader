#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskAttack_DragonAttack.generated.h"

UCLASS()
class MMB_API UCBTTaskAttack_DragonAttack : public UBTTaskNode
{
	GENERATED_BODY()

	UCBTTaskAttack_DragonAttack();

	UPROPERTY(EditAnywhere)
	int32 AttackMode;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	void DoAttack(class IIEnemyStateManager* EC);

};
