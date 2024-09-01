#include "CAnimNotifyState_PlayerComboIn1.h"
#include "PCH.h"

void UCAnimNotifyState_PlayerComboIn1::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (GetPC(MeshComp))
	{
		ResetComboStack();
		PC->SetState(PLAYER_COMBO_STACK_1, true);
	}
}

void UCAnimNotifyState_PlayerComboIn1::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	/*UE_LOG(LogTemp, Log, TEXT("--Stack 1 End--"));
	UE_LOG(LogTemp, Log, TEXT("Stack 1 Check %d"), PC->GetState(PLAYER_COMBO_STACK_1));
	UE_LOG(LogTemp, Log, TEXT("Stack 2 Check %d"), PC->GetState(PLAYER_COMBO_STACK_2));
	UE_LOG(LogTemp, Log, TEXT("Stack 3 Check %d"), PC->GetState(PLAYER_COMBO_STACK_3));*/
	if (GetPC(MeshComp)) ResetComboStack();
	/*UE_LOG(LogTemp, Log, TEXT("After Reset Stack 1 Check %d"), PC->GetState(PLAYER_COMBO_STACK_1));
	UE_LOG(LogTemp, Log, TEXT("After Reset Stack 2 Check %d"), PC->GetState(PLAYER_COMBO_STACK_2));
	UE_LOG(LogTemp, Log, TEXT("After Reset Stack 3 Check %d"), PC->GetState(PLAYER_COMBO_STACK_3));*/
}
