#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IWeaponSilhouetteComponent.generated.h"

UINTERFACE(MinimalAPI)
class UIWeaponSilhouetteComponent : public UInterface
{
	GENERATED_BODY()
};

class MMB_API IIWeaponSilhouetteComponent
{
	GENERATED_BODY()

public:
	virtual void SetEffectVisibility(bool e) {};
	virtual void ActivateEffect() {};
	virtual void DeactivateEffect() {};
	virtual void SetCharge(float e, bool IsLeft = false) {};
	virtual FVector GetWeaponLocation(bool IsLeft) { return FVector(); };
};
