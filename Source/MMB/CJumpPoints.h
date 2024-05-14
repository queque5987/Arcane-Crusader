// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/SplineComponent.h"
#include "CJumpPoints.generated.h"

UCLASS()
class MMB_API ACJumpPoints : public AActor
{
	GENERATED_BODY()
	
public:	
	ACJumpPoints();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	class USplineComponent* SplineComponent;
	UPROPERTY(EditAnywhere)
	class USphereComponent* ArrivalPoint0;
	UPROPERTY(EditAnywhere)
	class USphereComponent* ArrivalPoint1;
	float TimeElapsed = 0.f;
	UPROPERTY(EditAnywhere)
	float TotalTime;
	bool FlagJump;
	FTimerHandle LandTimerHandle;
	class ACPlayerCharacter* TransferingCharacter;

	UFUNCTION()
	void OnPoint0BeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnPoint1BeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	void EndJump();
	int TransferringFrom = -1;
public:	
	virtual void Tick(float DeltaTime) override;

	void TransferCharacter(class ACPlayerCharacter* PC, int JumpStartPoint);
};
