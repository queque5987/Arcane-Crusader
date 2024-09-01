#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "IWeaponSilhouetteComponent.h"
#include "CWeaponSilhouette_Rifle.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MMB_API UCWeaponSilhouette_Rifle : public USceneComponent, public IIWeaponSilhouetteComponent
{
	GENERATED_BODY()

public:	
	UCWeaponSilhouette_Rifle();
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* SniperRifleSMComponent;
	class UMaterialInstanceDynamic* SniperRifleMaterial;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ShotGunSMComponent;
	class UMaterialInstanceDynamic* ShotGunMaterial;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MachineGunSMComponent;
	class UMaterialInstanceDynamic* MachineGunMaterial;
protected:
	virtual void BeginPlay() override;
	int32 CurrEffect;
	float TurningOff;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void ActivateEffect() override;
	virtual void DeactivateEffect() override;
	virtual void SetCharge(float e, bool IsLeft = false) override;

	void SetWeaponEffect(int32 Index);

private:
	void SetParameter_Attacking(float NewAttacking);
};
