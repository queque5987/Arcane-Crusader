#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMainWeaponFloatingSpline.generated.h"

UCLASS()
class MMB_API ACMainWeaponFloatingSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	ACMainWeaponFloatingSpline();
	UPROPERTY(EditAnywhere)
	class USplineComponent* SplineComponent;
	UPROPERTY(EditAnywhere)
	TArray<AActor*> RotateActors;
	TArray<float> RotateActorsLocation;
	UPROPERTY(EditAnywhere)
	class AActor* FloatingObject;
	UPROPERTY(EditAnywhere)
	float FloatingTime;
protected:
	virtual void BeginPlay() override;
	float ClockTicking;
	FVector FirstLocation;
public:	
	virtual void Tick(float DeltaTime) override;

};
