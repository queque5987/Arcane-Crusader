#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IStageMaterialManager.generated.h"

UINTERFACE(MinimalAPI)
class UIStageMaterialManager : public UInterface
{
	GENERATED_BODY()
};

class MMB_API IIStageMaterialManager
{
	GENERATED_BODY()

public:

	virtual void UpdatePlayerCharacterPos(FVector Pos) {};
	virtual void UpdateRadius(float e) {};

	virtual float GetPostProcessRadius() { return 0.f; };
	virtual void PostProcessZoom(bool IsStart, FVector ZoomPos) {};
	virtual void ExecutePlayerDodgedEvent() {};
	virtual void ExecutePlayerDodgedEndEvent() {};

	virtual void SpawnParticle(class UParticleSystem* SpawnParticle, float LifeSpan, FVector Location, FRotator Rotation = FRotator::ZeroRotator, FVector Scale = FVector(1.f), class USceneComponent* ToAttachComponent = nullptr) {};
};
