#include "CAnimNotify_SKMeshStopAnim.h"


void UCAnimNotify_SKMeshStopAnim::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp == nullptr) return;
	MeshComp->Stop();
}
