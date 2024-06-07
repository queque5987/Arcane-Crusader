// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTTask_Rotate.h"
#include "IEnemyBBState.h"
#include "AIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "IEnemyBBState.h"

UCBTTask_Rotate::UCBTTask_Rotate()
{
	bNotifyTick = true;
	NodeName = "Rotate To";
}

EBTNodeResult::Type UCBTTask_Rotate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		UObject* KeyValue = MyBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
		AActor* TargetActor = Cast<AActor>(KeyValue);
		UE_LOG(LogTemp, Log, TEXT("Execute task : BlackBoard"));
		if (TargetActor)
		{
			UE_LOG(LogTemp, Log, TEXT("Execute task : TargetActor"));
			ACharacter* OwnerCharacter = OwnerComp.GetAIOwner()->GetCharacter();
			if (OwnerCharacter == nullptr) return EBTNodeResult::Aborted;

			FVector CurrPos = OwnerCharacter->GetActorLocation();
			FRotator CurrRot = OwnerCharacter->GetActorRotation();
			FVector TargetDirection = (TargetActor->GetActorLocation() - CurrPos).GetSafeNormal();
			FRotator TargetRot = FRotationMatrix::MakeFromX(TargetDirection).Rotator();


			if (FMath::Abs(CurrRot.Yaw - TargetRot.Yaw) >= RotateBoundary)
			{
				int32 DirectionalWeight = (FMath::Abs(CurrRot.Yaw - TargetRot.Yaw) > 180.f ? -1 : 1) * (CurrRot.Yaw > TargetRot.Yaw ? -1 : 1);
				float ToRotateWeight = (FMath::Abs(CurrRot.Yaw - TargetRot.Yaw) >= RotateSpeed ? RotateSpeed : FMath::Abs(CurrRot.Yaw - TargetRot.Yaw));
				CurrRot.Yaw += DirectionalWeight * ToRotateWeight;
				OwnerCharacter->SetActorRotation(CurrRot);
				UE_LOG(LogTemp, Log, TEXT("Execute task : Lotating to %s"), *CurrRot.ToString());

				IIEnemyBBState* BBState = Cast<IIEnemyBBState>(OwnerComp.GetAIOwner());
w				if (BBState != nullptr)
				{
					BBState->SetIsStrafe(DirectionalWeight * ToRotateWeight / RotateSpeed);
				}
			}

			return EBTNodeResult::Succeeded;
		}
		//else
		//{
			//UE_VLOG(MyController, LogBehaviorTree, Warning, TEXT("UBTTask_MoveTo::ExecuteTask tried to go to actor while BB %s entry was empty"), *BlackboardKey.SelectedKeyName.ToString());
		//}
	}
	return EBTNodeResult::Failed;
}

void UCBTTask_Rotate::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	//const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	//UObject* KeyValue = MyBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
	//AActor* TargetActor = Cast<AActor>(KeyValue);

	//ACharacter* OwnerCharacter = OwnerComp.GetAIOwner()->GetCharacter();
	//if (TargetActor == nullptr || OwnerCharacter == nullptr) return;

	//FVector CurrPos = OwnerCharacter->GetActorLocation();
	//FRotator CurrRot = OwnerCharacter->GetActorRotation();
	//FVector TargetDirection = (TargetActor->GetActorLocation() - CurrPos).GetSafeNormal();
	//FRotator TargetRot = FRotationMatrix::MakeFromX(TargetDirection).Rotator();



	//OwnerCharacter->SetActorRotation(FMath::RInterpTo(CurrRot, TargetRot, DeltaSeconds, RotateSpeed));

	////if (FMath::Abs(CurrRot.Yaw - TargetRot.Yaw) <= RotateBoundary)
	////{
	////	AbortTask(OwnerComp, NodeMemory);
	////	UE_LOG(LogTemp, Log, TEXT("Tick task : Abort"));
	////	return;
	////}

	//ExecuteTask(OwnerComp, NodeMemory);
	//UE_LOG(LogTemp, Log, TEXT("Tick task : Rotate"));

}
