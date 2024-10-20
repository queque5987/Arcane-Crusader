#pragma once

#include "CoreMinimal.h"
#include "Particles/ParticleSystemComponent.h"
#include "CParticleSystemComponent_Extent.generated.h"

UCLASS()
class MMB_API UCParticleSystemComponent_Extent : public UParticleSystemComponent
{
	GENERATED_BODY()

	FORCEINLINE bool operator <(const UCParticleSystemComponent_Extent* Other) const;

	//FORCEINLINE bool operator()(T* A, T* B) const
	//{
	//	return Predicate(*A, *B);
	//}
	UCParticleSystemComponent_Extent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float LifeSpan;

public:
	float GetLifeSpan() const { return LifeSpan; }
	void SetLifeSpan(float e) { LifeSpan = e; }
	//virtual void Activate(bool bReset = false) override;
};
