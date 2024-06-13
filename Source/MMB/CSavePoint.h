// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "CSavePoint.generated.h"

UCLASS()
class MMB_API ACSavePoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSavePoint();

	UPROPERTY(EditAnywhere)
	class USphereComponent* SavePointComponent;
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* TempPlayerSpawnPointCheck;

	FVector GetSavePointPos();
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
