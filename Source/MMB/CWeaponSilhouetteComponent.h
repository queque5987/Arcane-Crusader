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
	virtual void BeginPlay() override;
	float TurningOff;
	bool ThrowingStaff;
	float ThrowingSplineTime;
	int32 ThrowingHitStack;
	float ThrowingHitInterval;
	class AActor* AttachedWeapon;

	void UpdateSpline(FVector RetrieveLocation);
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetEffectVisibility(bool e) override;

	virtual void ActivateEffect() override;
	virtual void DeactivateEffect() override;

	virtual FVector GetWeaponLocation(bool IsLeft);

	void ThrowForward(FVector StartLocation, FVector EndLocation, class AActor* Weapon);
	void RetrieveStaff();
};
