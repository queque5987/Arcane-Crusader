#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_WeaponCallFunc.generated.h"

UCLASS()
class MMB_API UCAnimNotify_WeaponCallFunc : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	/*0 : BattleStaff, 1 : RifleStaff*/
	UPROPERTY(EditAnywhere)
	int32 WeaponType;
	/*0 : { BS : ThrowStaff, RS : SwitchLHand } 1 : { BS : TurnBruteMode , RS : ThrowBeacon } 2 : { RS : SwitchRHand }*/
	UPROPERTY(EditAnywhere)
	int32 ToCallFunc;
};
