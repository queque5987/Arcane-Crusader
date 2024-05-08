// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "CClimbableRope.generated.h"

UCLASS()
class MMB_API ACClimbableRope : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACClimbableRope();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* UpArrivalPoint;
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* DownArrivalPoint;

	UPROPERTY(EditAnywhere)
	class USphereComponent* UpPoint;
	UPROPERTY(EditAnywhere)
	class USphereComponent* DownPoint;
	FVector UpLocation;
	FVector DownLocation;
	bool bIsUpWard;
	//float ClimbSpeed;
public:	
	//virtual void Tick(float DeltaTime) override;
	void ClimbUp(FVector& NextTickClimbPos, bool& Result);
	//void ClimbUp(FVector& NextRelativeLocation, float ClimbSpeed);

	void ClimbDown(FVector& NextTickClimbPos, bool& Result);
	UFUNCTION()
	void OnUpPointBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnDownPointBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool GetIsUpWard() { return bIsUpWard; }
	FVector GetUpLocation() { return UpLocation; }
	FVector GetDownLocation() { return DownLocation; }
private:
	void PopInteractButton(AActor* OtherActor, bool IsUpWard);
	//float SetClimbSpeed(float e) { ClimbSpeed = e; }
};
