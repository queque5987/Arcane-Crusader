#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IEnemyAITactics.generated.h"

UINTERFACE(MinimalAPI)
class UIEnemyAITactics : public UInterface
{
	GENERATED_BODY()
};

class MMB_API IIEnemyAITactics
{
	GENERATED_BODY()

public:
	virtual ACharacter* GetPlayer() { return nullptr; }
	virtual bool IsPlayerAttacking() { return false; }
	virtual float GetPlayerDistance() { return 0.f; }
	virtual FVector GetPlayerVelocity() { return FVector(); }
	virtual FVector GetPlayerLocation() { return FVector(); }
	virtual bool IsEnemyBusy() { return false; }
};
