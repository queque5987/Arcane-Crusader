#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_LaunchCharacter.generated.h"

UCLASS()
class MMB_API UCAnimNotify_LaunchCharacter : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
public:
	UPROPERTY(EditAnywhere)
	float Power;

	/*X : Forward Vector, Y : Right Vecto,r Z : Up Vector (0 < x : inverse)*/
	UPROPERTY(EditAnywhere)
	FVector DirectionalVector;
};
