#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_RSUltThrowBeacon.generated.h"

//Deprecated 20240914 Use CAnimNotify_WeaponCallFunc

UCLASS()
class MMB_API UCAnimNotify_RSUltThrowBeacon : public UAnimNotify
{
	GENERATED_BODY()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
public:
	UPROPERTY(EditAnywhere)
	bool ToLeft;
	UPROPERTY(EditAnywhere)
	bool ThrowBeacon;
};
