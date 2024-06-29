// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PCH.h"
#include "CDroppedItem.generated.h"

UCLASS()
class MMB_API ACDroppedItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACDroppedItem();
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere)
	class USphereComponent* Collider;
protected:
	virtual void BeginPlay() override;

	class UCInventoryItemData* PossessingItem;

	void CheckSweepCharacter();

	class ACPlayerCharacter* OverlapingPlayerCharacter;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetPossessingItem(class UCInventoryItemData& ItemData);
	class UCInventoryItemData* GetPossessingItem() { return PossessingItem; }
};
