// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "CEntrance.h"
#include "IEntrance.h"
#include "CEntrance_Cinematic.generated.h"

UCLASS()
class MMB_API ACEntrance_Cinematic : public AActor, public IIEntrance
{
	GENERATED_BODY()
	ACEntrance_Cinematic();

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

	class USoundCue* OpeningSoundEffect;
	TArray<class UAudioComponent*> OpeningSEArr;
	virtual void BeginPlay() override;
public:

	UFUNCTION()
	void OnGateOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void SetOpenGate(bool e) override;
	virtual bool GetOpenGate() override { return OpenGate; }



	UPROPERTY()
	class UBoxComponent* EnterCollider;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* CinematicCameraComponent;

	UPROPERTY(EditAnywhere)
	float CameraMoveSpeed = 0.5f;

	UPROPERTY(EditAnywhere)
	float CinematicTimelapse;

public:
	//virtual void Tick(float DeltaTime) override;
	//virtual void BeginPlay() override;
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnCinematicCameraArrived();

private:
	class ACPlayerCharacter* PC;
	//ACharacter* AC;

	//ACPlayerController* PCC;
	FTransform CinematicCameraFixedTransform;
	bool DoCinematic = false;
	FTimerHandle CinematicTimerHandle;

	bool Used = false;
};
