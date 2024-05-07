// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "CMainUIPawn.generated.h"

UCLASS()
class MMB_API ACMainUIPawn : public APawn
{
	GENERATED_BODY()

	/*UPROPERTY()
	class USpringArmComponent* SpringArmComponent;*/
	UPROPERTY()
	class UCameraComponent* CameraComponent;

public:
	// Sets default values for this pawn's properties
	ACMainUIPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
