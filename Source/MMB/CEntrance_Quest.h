// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CEntrance.h"
#include "IEntrance.h"
#include "CEntrance_Quest.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API ACEntrance_Quest : public AActor, public IIEntrance
{
	GENERATED_BODY()
	ACEntrance_Quest();

	UPROPERTY()
	class UBoxComponent* EnterCollider;

	UPROPERTY(EditAnywhere)
	FString CheckQuest;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* CinematicCameraComponent;
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	TArray<UStaticMeshComponent*> StaticMeshComponents;

	
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
	bool DoCinematic;
	int GateNum;
	FTimerHandle CinematicTimerHandle;
	FTransform CinematicCameraFixedTransform;
	UPROPERTY(EditAnywhere)
	float CameraMoveSpeed;

	class ACPlayerCharacter* tempCharacter;
	class ACPlayerController* tempController;
public:

	UFUNCTION()
	void OnGateOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void SetOpenGate(bool e) override;
	virtual bool GetOpenGate() override { return OpenGate; }

	void FocusToGate(class ACPlayerCharacter* PC);
};
