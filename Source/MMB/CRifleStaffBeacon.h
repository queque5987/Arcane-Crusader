#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CRifleStaffBeacon.generated.h"

UCLASS()
class MMB_API ACRifleStaffBeacon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACRifleStaffBeacon();

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* BeaconComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* RuneWordComponent;

	class USplineComponent* SplineComponent;
protected:
	class USoundCue* TickingSoundCue;

	class UMaterialInstanceDynamic* RuneWordMaterial;

	class IIWeapon* SummonedRifleStaff;

	virtual void BeginPlay() override;

	bool Departure;
	bool OnGround;
	bool RuneWordStretched;
	float DepartureClock;
	float fZoom;
	float AutoDestoryTimer;
public:	
	virtual void Tick(float DeltaTime) override;
	void HitGround();
	void Throw(FVector StartLocation, FVector Destination);
	void SetSummonedRifle(class IIWeapon* RifleStaff);
};
