#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "IWeaponSilhouetteComponent.h"
#include "CWeaponSilhouette_Gauntlet.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MMB_API UCWeaponSilhouette_Gauntlet : public USceneComponent, public IIWeaponSilhouetteComponent
{
	GENERATED_BODY()
	UCWeaponSilhouette_Gauntlet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* WeaponOraEffect;
	UPROPERTY(EditAnywhere)
	class UMaterialInstanceDynamic* OraEffectMaterial;
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* WeaponOraEffect_L;
	UPROPERTY(EditAnywhere)
	class UMaterialInstanceDynamic* OraEffectMaterial_L;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* ChargeEffect;
	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* ChargeEffect_L;
protected:
	virtual void BeginPlay() override;
	float TurningOff;
	bool bGrasping;

	class UAnimSequenceBase* GraspAnim;
	class UAnimSequenceBase* UnGraspAnim;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetEffectVisibility(bool e) override;

	virtual void ActivateEffect() override;
	virtual void DeactivateEffect() override;
	virtual void SetCharge(float e, bool IsLeft = false) override;
	virtual FVector GetWeaponLocation(bool IsLeft) override;
public:
	void GraspFist(bool e);
};
