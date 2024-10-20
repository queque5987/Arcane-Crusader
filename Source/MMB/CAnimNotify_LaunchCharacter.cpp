#include "CAnimNotify_LaunchCharacter.h"
#include "GameFramework/Character.h"

void UCAnimNotify_LaunchCharacter::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACharacter* C = Cast<ACharacter>(MeshComp->GetOwner());
	if (C == nullptr) return;

	FVector Direction;
	
	Direction += C->GetActorForwardVector() * DirectionalVector.X;
	Direction += C->GetActorRightVector() * DirectionalVector.Y;
	Direction += C->GetActorUpVector() * DirectionalVector.Z;

	C->LaunchCharacter(Direction * Power, true, true);
}
