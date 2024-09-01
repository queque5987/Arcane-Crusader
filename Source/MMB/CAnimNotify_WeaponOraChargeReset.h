#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_WeaponOraChargeReset.generated.h"

UCLASS()
class MMB_API UCAnimNotify_WeaponOraChargeReset : public UAnimNotify
{
	GENERATED_BODY()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(EditAnywhere)
	bool IsLeft;
};
