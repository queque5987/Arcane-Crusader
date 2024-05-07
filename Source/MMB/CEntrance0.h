// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "CEntrance.h"
#include "IEntrance.h"
#include "CEntrance0.generated.h"

UCLASS()
class MMB_API ACEntrance0 : public AActor, public IIEntrance
{
	GENERATED_BODY()
	
	ACEntrance0();


	TArray<UStaticMeshComponent*> StaticMeshComponents;

	virtual void Tick(float DeltaTime) override;
	UPROPERTY()
	class UBoxComponent* Collider;
	UPROPERTY(EditAnywhere)
	bool OpenGate = false;

	UPROPERTY(EditAnywhere)
	class UDataTable* DialogueTable;
	UPROPERTY(EditAnywhere)
	TArray<int> DialogueIndex;
	UPROPERTY(EditAnywhere)
	bool bPrintDialogueRandom;

	int CurrentDialogue = 0;

protected:
	TArray<float*> RandomGateOpenSequence;
	UPROPERTY(EditAnywhere)
	float OpenGateSpeed;
	float GateWidth;
	int GateNum;

	virtual void BeginPlay() override;
public:
	UFUNCTION()
	void OnGateOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
	class UBoxComponent* EnterCollider;
	//UPROPERTY()
	//class UBoxComponent* ExitCollider;

public:
	virtual void SetOpenGate(bool e) override;
	virtual bool GetOpenGate() override;


	//virtual void BeginPlay() override;
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
