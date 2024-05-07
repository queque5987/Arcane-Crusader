// Fill out your copyright notice in the Description page of Project Settings.


#include "CMainUIPawn.h"

// Sets default values
ACMainUIPawn::ACMainUIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	SetRootComponent(CameraComponent);
	//CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void ACMainUIPawn::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(FVector(-125.f, -350.f, 0.f));
	SetActorRotation(FRotator(0.f, 90.f, 0.f));
	
}

// Called every frame
void ACMainUIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACMainUIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

