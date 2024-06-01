// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "CFallDie.generated.h"

UCLASS()
class MMB_API ACFallDie : public AActor
{
	GENERATED_BODY()
	
public:	
	ACFallDie();

protected:
	UPROPERTY(EditAnywhere)
	float Damage = 0.f;
	UPROPERTY(EditAnywhere)
	class UBoxComponent* LimitBox;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* CinematicCameraComponent;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	virtual void Tick(float DeltaTime) override;

};
