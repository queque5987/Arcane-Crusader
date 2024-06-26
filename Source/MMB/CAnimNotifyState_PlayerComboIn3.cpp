// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotifyState_PlayerComboIn3.h"
#include "PCH.h"

void UCAnimNotifyState_PlayerComboIn3::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (GetPC(MeshComp))
	{
		ResetComboStack();
		PC->SetState(PLAYER_COMBO_STACK_3, true);
	}
}

void UCAnimNotifyState_PlayerComboIn3::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	/*UE_LOG(LogTemp, Log, TEXT("--Stack 3 End--"));
	UE_LOG(LogTemp, Log, TEXT("Stack 1 Check %d"), PC->GetState(PLAYER_COMBO_STACK_1));
	UE_LOG(LogTemp, Log, TEXT("Stack 2 Check %d"), PC->GetState(PLAYER_COMBO_STACK_2));
	UE_LOG(LogTemp, Log, TEXT("Stack 3 Check %d"), PC->GetState(PLAYER_COMBO_STACK_3));*/
	if (GetPC(MeshComp)) ResetComboStack();
	/*UE_LOG(LogTemp, Log, TEXT("After Reset Stack 1 Check %d"), PC->GetState(PLAYER_COMBO_STACK_1));
	UE_LOG(LogTemp, Log, TEXT("After Reset Stack 2 Check %d"), PC->GetState(PLAYER_COMBO_STACK_2));
	UE_LOG(LogTemp, Log, TEXT("After Reset Stack 3 Check %d"), PC->GetState(PLAYER_COMBO_STACK_3));*/
}
