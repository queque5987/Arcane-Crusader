// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CEnemyAnimInstance.h"

const FName ACEnemyAIController::HomePosKey(TEXT("HomePos"));
const FName ACEnemyAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ACEnemyAIController::bSeePlayer(TEXT("bSeePlayer"));
const FName ACEnemyAIController::PlayerPos(TEXT("PlayerPos"));
const FName ACEnemyAIController::bHostile(TEXT("bHostile"));
const FName ACEnemyAIController::bBusy(TEXT("bBusy"));
const FName ACEnemyAIController::PlayerCharacter(TEXT("PlayerCharacter"));

ACEnemyAIController::ACEnemyAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//RepeatInterval = 3.f;
	PlayerLoseInterval = 5.f;
	RoarCooldown = 30.f;
	CanRoar = true;

	//ConstructorHelpers::FObjectFinder<UBehaviorTree>BTAssetFinder(TEXT("/Game/Enemy/NightMare/AIController/BT_Enemy.BT_Enemy"));
	//ConstructorHelpers::FObjectFinder<UBlackboardData>BBAssetFinder(TEXT("/Game/Enemy/NightMare/AIController/BB_Enemy.BB_Enemy"));
	//if (BTAssetFinder.Succeeded())
	//{
	//	BTAsset = BTAssetFinder.Object;
	//}
	//if (BBAssetFinder.Succeeded())
	//{
	//	BBAsset = BBAssetFinder.Object;
	//}
	
	SetPerceptionSystem();
}

void ACEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(InPawn))
	{
		if (UCEnemyAnimInstance* EA = Cast<UCEnemyAnimInstance>(EC->GetMesh()->GetAnimInstance()))
		{
			EA->OnMontageStarted.AddDynamic(this, &ACEnemyAIController::SetbBusyUnFree);
			EA->OnMontageEnded.AddDynamic(this, &ACEnemyAIController::SetbBusyFree);
		}
	}
}

void ACEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ACEnemyAIController::OnTargetDetected(AActor* actor, FAIStimulus const Stimulus)
{
	if (auto const player = Cast<ACPlayerCharacter>(actor))
	{
		Blackboard->SetValueAsBool(bSeePlayer, Stimulus.WasSuccessfullySensed());
		Blackboard->SetValueAsVector(PlayerPos, player->GetActorLocation());
		UE_LOG(LogTemp, Log, TEXT("Update Player %s Vector"), *player->GetName());
		if (Stimulus.WasSuccessfullySensed())
		{
			GetWorld()->GetTimerManager().ClearTimer(PlayerLoseTimerHandle);
			ChasingPlayer = player;

			if (ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(GetPawn()))
			{
				EC->SetbHostile(true);
				Blackboard->SetValueAsBool(bHostile, true);
				Blackboard->SetValueAsObject(PlayerCharacter, player);
			}
		}
		else
		{
			Blackboard->SetValueAsObject(PlayerCharacter, nullptr);
			GetWorld()->GetTimerManager().SetTimer(PlayerLoseTimerHandle, this, &ACEnemyAIController::OnPlayerLoseTimer, PlayerLoseInterval);
		}
	}
}

void ACEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//void ACEnemyAIController::SetPerceptionComponent(UAIPerceptionComponent& InPerceptionComponent)
void ACEnemyAIController::SetPerceptionSystem()
{
	SightConfig = CreateOptionalDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateOptionalDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception")));

	SightConfig->SightRadius = 3000.f;
	SightConfig->LoseSightRadius = 500.f;
	SightConfig->PeripheralVisionAngleDegrees = 120.f;
	SightConfig->SetMaxAge(5.f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 900.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ACEnemyAIController::OnTargetDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

void ACEnemyAIController::SetbBusyFree(UAnimMontage* Montage, bool bInterrupted)
{
	SetbBusy(false);
}

void ACEnemyAIController::SetbBusyUnFree(UAnimMontage* Montage)
{
	SetbBusy(true);
}

FVector ACEnemyAIController::GetChasingPlayerPos()
{
	return ChasingPlayer!= nullptr ? ChasingPlayer->GetActorLocation() : Blackboard->GetValueAsVector(PlayerPos);
}

void ACEnemyAIController::SetbBusy(bool e)
{
	Blackboard->SetValueAsBool(bBusy, e);
}

bool ACEnemyAIController::GetbBusy()
{
	return Blackboard->GetValueAsBool(bBusy);
}

void ACEnemyAIController::SetRoarCooldownTimer()
{
	GetWorld()->GetTimerManager().SetTimer(RoarTimerHandle, this, &ACEnemyAIController::RoarCooldownTimer, RoarCooldown);
}

void ACEnemyAIController::OnPlayerLoseTimer()
{
	//UE_LOG(LogTemp, Log, TEXT("Player Lost"));
	ChasingPlayer = nullptr;
	if (ACEnemyCharacter* EC = Cast<ACEnemyCharacter>(GetPawn()))
	{
		EC->SetbHostile(false);
		Blackboard->SetValueAsBool(bHostile, false);
	}
}