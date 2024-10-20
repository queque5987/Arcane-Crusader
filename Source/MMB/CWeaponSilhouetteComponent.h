#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "IWeaponSilhouetteComponent.h"
#include "CWeaponSilhouetteComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MMB_API UCWeaponSilhouetteComponent : public USceneComponent, public IIWeaponSilhouetteComponent
{
	GENERATED_BODY()

public:	
	UCWeaponSilhouetteComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* WeaponOraEffect;
	UPROPERTY(EditAnywhere)
	class UMaterialInstanceDynamic* OraEffectMaterial;

	UPROPERTY(EditAnywhere)
	class USplineComponent* SplineComponent;

protected:
	class UParticleSystemComponent* AttachedEffectComponent;
	virtual void BeginPlay() override;
	float TurningOff;

	int32 BoolState;

	static const int32 ThrowingStaff;
	static const int32 ThrowingForward;
	static const int32 RetrieveStaff;

	//bool ThrowingStaff;
	//bool ThrowingForward;
	//bool RetrieveStaff;

	float ThrowingRotateTime;
	float ThrowingSplineTime;
	int32 ThrowingHitStack;
	float ThrowingHitInterval;
	class AActor* AttachedWeapon;

	/* Update Throwing Circular Spline */
	void UpdateSpline(FVector RetrieveLocation);

	bool GetBoolState(int32 StateIndex);
	void SetBoolState(int32 StateIndex, bool b);

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetEffectVisibility(bool e) override;

	virtual void ActivateEffect() override;
	virtual void DeactivateEffect() override;

	virtual FVector GetWeaponLocation(bool IsLeft);

	void ThrowCircular(FVector StartLocation, FVector EndLocation, class AActor* Weapon);
	void ThrowForward(FVector StartLocation, FVector EndLocation, class AActor* Weapon);
	void InstantRetrieveStaff();
};
