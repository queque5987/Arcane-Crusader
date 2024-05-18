// Fill out your copyright notice in the Description page of Project Settings.


#include "CSavePoint.h"
#include "IPlayerState.h"

ACSavePoint::ACSavePoint()
{
	PrimaryActorTick.bCanEverTick = true;
	SavePointComponent = CreateDefaultSubobject<USphereComponent>(FName("SavePointCollider"));
	TempPlayerSpawnPointCheck = CreateDefaultSubobject<UCapsuleComponent>(FName("PlayerSpawnCheck"));
	SetRootComponent(TempPlayerSpawnPointCheck);
	SavePointComponent->SetupAttachment(TempPlayerSpawnPointCheck);
}

void ACSavePoint::BeginPlay()
{
	Super::BeginPlay();
	SavePointComponent->OnComponentBeginOverlap.AddDynamic(this, &ACSavePoint::OnOverlapBegin);
}

void ACSavePoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IIPlayerState* PC = Cast<IIPlayerState>(OtherActor);
	if (PC == nullptr) return;
	PC->SetRevivalPoint(TempPlayerSpawnPointCheck->GetComponentLocation());
}
