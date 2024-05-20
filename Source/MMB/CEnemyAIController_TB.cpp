// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyAIController_TB.h"
#include "CEnemy_AnimInstance_TB.h"
#include "CEnemy_TerrorBringer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "IEnemyBBState.h"

const FName ACEnemyAIController_TB::bIsOnAir(TEXT("IsOnAir"));

ACEnemyAIController_TB::ACEnemyAIController_TB(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructorHelpers::FObjectFinder<UBehaviorTree>BTAssetFinder(TEXT("/Game/Enemy/TerrorBringer/AIController/BT_Enemy_TB.BT_Enemy_TB"));
	ConstructorHelpers::FObjectFinder<UBlackboardData>BBAssetFinder(TEXT("/Game/Enemy/TerrorBringer/AIController/BB_Enemy_TB.BB_Enemy_TB"));

	if (BTAssetFinder.Succeeded())
	{
		BTAsset = BTAssetFinder.Object;
	}
	if (BBAssetFinder.Succeeded())
	{
		BBAsset = BBAssetFinder.Object;
	}


	FlyingSightConfig = CreateOptionalDefaultSubobject<UAISenseConfig_Sight>(TEXT("Flying Sight Config"));

	FlyingSightConfig->SightRadius = 9000.f;
	FlyingSightConfig->LoseSightRadius = 1500.f;
	FlyingSightConfig->PeripheralVisionAngleDegrees = 240.f;
	FlyingSightConfig->SetMaxAge(15.f);
	FlyingSightConfig->AutoSuccessRangeFromLastSeenLocation = 1800.f;
	FlyingSightConfig->DetectionByAffiliation.bDetectEnemies = true;
	FlyingSightConfig->DetectionByAffiliation.bDetectNeutrals = true;
}

void ACEnemyAIController_TB::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BB = Blackboard;
	if (UseBlackboard(BBAsset, BB))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogTemp, Log, TEXT("AIController coudn't run behavior tree!"));
		}
	}
}

void ACEnemyAIController_TB::SwitchFlyMode()
{
	ACEnemy_TerrorBringer* EC = Cast<ACEnemy_TerrorBringer>(GetCharacter());
	UCEnemy_AnimInstance_TB* Anim = Cast<UCEnemy_AnimInstance_TB>(
		GetCharacter()->GetMesh()->GetAnimInstance()
	);
	if (Anim == nullptr) return;
	
	IIEnemyBBState* AIController = Cast<IIEnemyBBState>(EC->GetController());
	if (AIController == nullptr) return;

	bool IsOnAir = Anim->GetIsOnAir();
	if (IsOnAir)
	{
		UE_LOG(LogTemp, Log, TEXT("Free FlyMode"));
		//Anim->SetIsOnAir(false);
		Blackboard->SetValueAsBool(bIsOnAir, false);
		EC->SetIsFlying(false);
		AIController->SetbBusy(true);
		Anim->Land();

		SightConfig->SightRadius = 3000.f;
		SightConfig->LoseSightRadius = 500.f;
		SightConfig->PeripheralVisionAngleDegrees = 120.f;
		SightConfig->SetMaxAge(5.f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 900.f;

		//GetPerceptionComponent()->ConfigureSense(*SightConfig);
		return;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Set to FlyMode"));
		Anim->SetIsOnAir(true);
		Blackboard->SetValueAsBool(bIsOnAir, true);
		EC->SetIsFlying(true);
		AIController->SetbBusy(true);
		Anim->TakeOff();

		SightConfig->SightRadius = 9000.f;
		SightConfig->LoseSightRadius = 1500.f;
		SightConfig->PeripheralVisionAngleDegrees = 240.f;
		SightConfig->SetMaxAge(15.f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 1800.f;

		//GetPerceptionComponent()->ConfigureSense(*FlyingSightConfig);
		return;
	}
}

bool ACEnemyAIController_TB::GetIsOnAir()
{
	return Blackboard->GetValueAsBool(bIsOnAir);
}

FVector ACEnemyAIController_TB::GetFlyPatrolPos()
{
	return Blackboard->GetValueAsVector(PatrolPosKey);
}
