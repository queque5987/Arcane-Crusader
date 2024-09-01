#include "CAnimNotifyState_ChargableAnim.h"
#include "PCH.h"

void UCAnimNotifyState_ChargableAnim::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ChargeFinished = false;
}

void UCAnimNotifyState_ChargableAnim::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	IIPlayerState* PlayerState = Cast<IIPlayerState>(MeshComp->GetOwner());
	if (PlayerState == nullptr) return;

	if (!ChargeFinished && !PlayerState->GetKeyState(IsLMB ? PLAYER_INPUT_LMB : PLAYER_INPUT_RMB))
	{
		UE_LOG(LogTemp, Log, TEXT("!ChargeFinished && !PlayerState->GetKeyState(IsLMB ? PLAYER_INPUT_LMB : PLAYER_INPUT_RMB)"));

		ChargeFinished = true;

		UAnimInstance* AnimInst = MeshComp->GetAnimInstance();
		if (AnimInst == nullptr) return;
		ACharacter* C = Cast<ACharacter>(MeshComp->GetOwner());
		if (C == nullptr) return;

		PlayerAttackSpeed = 1.f;
		IIPlayerUIController* UIController = Cast<IIPlayerUIController>(C->GetController());
		if (UIController)
		{
			ItemStat tempStat;
			UIController->EquippedItemStat(tempStat);
			PlayerAttackSpeed += tempStat._AttackSpeed;
		}

		AnimInst->Montage_SetPlayRate(C->GetCurrentMontage(), OutPlayRate * PlayerAttackSpeed * 2.f);
	}
}

void UCAnimNotifyState_ChargableAnim::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UAnimInstance* AnimInst = MeshComp->GetAnimInstance();
	if (AnimInst == nullptr) return;
	ACharacter* C = Cast<ACharacter>(MeshComp->GetOwner());
	if (C == nullptr) return;

	AnimInst->Montage_SetPlayRate(C->GetCurrentMontage(), OutPlayRate * PlayerAttackSpeed);
}
