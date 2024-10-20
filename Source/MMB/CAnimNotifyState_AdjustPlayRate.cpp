#include "CAnimNotifyState_AdjustPlayRate.h"
#include "PCH.h"

void UCAnimNotifyState_AdjustPlayRate::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	UAnimInstance* AnimInst = MeshComp->GetAnimInstance();
	if (AnimInst == nullptr) return;
	ACharacter* C = Cast<ACharacter>(MeshComp->GetOwner());
	if (C == nullptr) return;

	PlayerAttackSpeed = 1.f;
	if (!AbsoluteSpeed)
	{
		IIPlayerUIController* UIController = Cast<IIPlayerUIController>(C->GetController());
		if (UIController)
		{
			ItemStat tempStat;
			UIController->EquippedItemStat(tempStat);
			PlayerAttackSpeed += tempStat._AttackSpeed;
		}
	}

	AnimInst->Montage_SetPlayRate(C->GetCurrentMontage(), InPlayRate * PlayerAttackSpeed);
}

void UCAnimNotifyState_AdjustPlayRate::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UAnimInstance* AnimInst = MeshComp->GetAnimInstance();
	if (AnimInst == nullptr) return;
	ACharacter* C = Cast<ACharacter>(MeshComp->GetOwner());
	if (C == nullptr) return;

	AnimInst->Montage_SetPlayRate(C->GetCurrentMontage(), OutPlayRate * PlayerAttackSpeed);
}
