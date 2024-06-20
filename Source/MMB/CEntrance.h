// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundCue.h"
#include "PCH.h"
#include "CEntrance.generated.h"
UCLASS()
class MMB_API ACEntrance : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ACEntrance();

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

	void SetOpenGate(bool e);
	bool GetOpenGate() { return OpenGate; }
};
