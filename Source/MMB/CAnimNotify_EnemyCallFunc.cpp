#include "CAnimNotify_EnemyCallFunc.h"
#include "CEnemyCharacter.h"
#include "CEnemy_Dragon.h"
#include "IEnemyStateManager.h"

void UCAnimNotify_EnemyCallFunc::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACEnemyCharacter* C = Cast<ACEnemyCharacter>(MeshComp->GetOwner());
	if (C == nullptr) return;
	switch (ToCallFunc)
	{
	case(0):
		CallFunc0(C);
		break;
	case(1):
		CallFunc1(C);
		break;
	case(2):
		CallFunc2(C);
		break;
	default:
		break;
	}
}

void UCAnimNotify_EnemyCallFunc::CallFunc0(ACEnemyCharacter* Character)
{
	if (Character->IsA(ACEnemy_Dragon::StaticClass()))
	{
		IIEnemyStateManager* Dragon = Cast<IIEnemyStateManager>(Character);
		if (Dragon == nullptr) return;
		if (Dragon->IsStartedToFall()) return; // Dragon Is Falling; Ignore Land Notify
		Character->StopAnimMontage();
		Dragon->Land();
	}
}

void UCAnimNotify_EnemyCallFunc::CallFunc1(ACEnemyCharacter* Character)
{
	if (Character->IsA(ACEnemy_Dragon::StaticClass()))
	{
		IIEnemyStateManager* Dragon = Cast<IIEnemyStateManager>(Character);
		if (Dragon == nullptr) return;
		if (!Dragon->IsStartedToFall()) return; // Dragon Is Landing; Ignore Fall Notify
		Dragon->FreeFall();
	}
}

void UCAnimNotify_EnemyCallFunc::CallFunc2(ACEnemyCharacter* Character)
{
	if (Character->IsA(ACEnemy_Dragon::StaticClass()))
	{
		IIEnemyStateManager* Dragon = Cast<IIEnemyStateManager>(Character);
		if (Dragon == nullptr) return;
		Dragon->BiteGraspEndPlayer();
	}
}
