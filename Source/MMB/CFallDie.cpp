// Fill out your copyright notice in the Description page of Project Settings.


#include "CFallDie.h"
#include "GameFramework/Character.h"
#include "IPlayerState.h"

ACFallDie::ACFallDie()
{
	PrimaryActorTick.bCanEverTick = true;

	LimitBox = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	CinematicCameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");

}

void ACFallDie::BeginPlay()
{
	Super::BeginPlay();
	LimitBox->OnComponentBeginOverlap.AddDynamic(this, &ACFallDie::OnOverlapBegin);
}

void ACFallDie::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* C = Cast<ACharacter>(OtherActor);
	IIPlayerState* PS = Cast<IIPlayerState>(C);
	if (PS != nullptr)
	{
		FVector Bong = FVector::UpVector * 300.f;
		FRotator BongAngle = FRotator(-70.f, FMath::RandRange(0.f, 359.f), 0.f);
		Bong = BongAngle.RotateVector(Bong);
		CinematicCameraComponent->SetWorldLocation(C->GetActorLocation() + Bong);
		CinematicCameraComponent->SetWorldRotation(BongAngle);
		PS->FallToRevivalPoint(CinematicCameraComponent->GetOwner(), Damage);
	}
}

void ACFallDie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

