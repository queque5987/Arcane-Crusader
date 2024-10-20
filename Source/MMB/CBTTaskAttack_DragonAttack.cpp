#include "CBTTaskAttack_DragonAttack.h"
#include "CEnemy_Dragon.h"
#include "IEnemyStateManager.h"
#include "CEnemyAIController_Dragon.h"

UCBTTaskAttack_DragonAttack::UCBTTaskAttack_DragonAttack() : Super()
{
}

EBTNodeResult::Type UCBTTaskAttack_DragonAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) return EBTNodeResult::Failed;
	IIEnemyStateManager* EC = Cast<IIEnemyStateManager>(ControllingPawn);
	if (EC == nullptr) return EBTNodeResult::Failed;
	//ACEnemyAIController_Dragon* ECC = Cast<ACEnemyAIController_Dragon>(EC->GetController());
	//if (!IsValid(ECC)) return EBTNodeResult::Failed;

	DoAttack(EC);
	return EBTNodeResult::Succeeded;
}

void UCBTTaskAttack_DragonAttack::DoAttack(IIEnemyStateManager* EC)
{
	UE_LOG(LogTemp, Log, TEXT("UCBTTaskAttack_DragonAttack : %d"), AttackMode);
	EC->DoAttack(AttackMode * 2);
}
