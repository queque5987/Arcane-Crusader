#include "CBTTaskAttack.h"
#include "CEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CEnemyCharacter.h"

UCBTTaskAttack::UCBTTaskAttack()
{
}

EBTNodeResult::Type UCBTTaskAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) return EBTNodeResult::Failed;
	ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(ControllingPawn);
	if (!IsValid(EC)) return EBTNodeResult::Failed;
	ACEnemyAIController* ECC = Cast<ACEnemyAIController>(EC->GetController());
	if (!IsValid(ECC)) return EBTNodeResult::Failed;

	DoAttack(EC);
	return EBTNodeResult::Succeeded;
}

void UCBTTaskAttack::DoAttack(ACEnemyCharacter* EC)
{
	EC->DoAttackHand.ExecuteIfBound();
}
