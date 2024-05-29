// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "CStaticNPC.h"
#include "CEthereal.generated.h"
UCLASS()
class MMB_API ACEthereal : public ACStaticNPC
{
	GENERATED_BODY()
	
	ACEthereal();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	TArray<FName> PossessItems;
public:
	//UFUNCTION()
	//void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//UFUNCTION()
	//void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void Initialize() override;
	//virtual TArray<FNPCDialoguesRow*> GetDialogue() override;
};
