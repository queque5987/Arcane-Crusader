// Fill out your copyright notice in the Description page of Project Settings.


#include "CClimbableRope.h"
#include "PCH.h"

// Sets default values
ACClimbableRope::ACClimbableRope()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	UpArrivalPoint = CreateDefaultSubobject<UCapsuleComponent>(TEXT("UpArrivalPointComponent"));
	DownArrivalPoint = CreateDefaultSubobject<UCapsuleComponent>(TEXT("DownArrivalPointComponent"));
	UpPoint = CreateDefaultSubobject<USphereComponent>(TEXT("UpPointComponent"));
	DownPoint = CreateDefaultSubobject<USphereComponent>(TEXT("DownPointComponent"));

	SetRootComponent(StaticMeshComponent);
	UpPoint->SetupAttachment(StaticMeshComponent);
	UpPoint->InitSphereRadius(100.f);
	UpArrivalPoint->SetupAttachment(UpPoint);
	UpArrivalPoint->SetCapsuleHalfHeight(88.f);
	UpArrivalPoint->SetCapsuleRadius(88.f);

	DownPoint->SetupAttachment(StaticMeshComponent);
	DownPoint->InitSphereRadius(100.f);
	DownArrivalPoint->SetupAttachment(DownPoint);
	DownArrivalPoint->SetCapsuleHalfHeight(88.f);
	DownArrivalPoint->SetCapsuleRadius(88.f);
}

// Called when the game starts or when spawned
void ACClimbableRope::BeginPlay()
{
	Super::BeginPlay();

	UpArrivalPoint->OnComponentBeginOverlap.AddDynamic(this, &ACClimbableRope::OnUpPointBeginOverlap);
	UpArrivalPoint->OnComponentEndOverlap.AddDynamic(this, &ACClimbableRope::OnEndOverlap);

	DownArrivalPoint->OnComponentBeginOverlap.AddDynamic(this, &ACClimbableRope::OnDownPointBeginOverlap);
	DownArrivalPoint->OnComponentEndOverlap.AddDynamic(this, &ACClimbableRope::OnEndOverlap);

	UpLocation = UpPoint->GetComponentLocation();
	DownLocation = DownPoint->GetComponentLocation();
	UpTransform = UpPoint->GetComponentTransform();
	DownTransform = DownPoint->GetComponentTransform();
}

void ACClimbableRope::PlayerSetOnRope(ACPlayerCharacter* PC)
{
	PC->SetActorLocation(GetIsUpWard() ? DownLocation : UpLocation);
}

//void ACClimbableRope::ClimbUp(FVector CurrLocation, FVector& NextTickLocation, float ClimbSpeed)
void ACClimbableRope::ClimbUp(FVector& NextTickClimbPos, bool& Result)
{
	Result = (UpLocation.Z < NextTickClimbPos.Z);
	if (UpLocation.Z < NextTickClimbPos.Z) NextTickClimbPos = UpArrivalPoint->GetComponentLocation();
}

void ACClimbableRope::ClimbDown(FVector& NextTickClimbPos, bool& Result)
{
	Result = (DownLocation.Z > NextTickClimbPos.Z);
	if (DownLocation.Z > NextTickClimbPos.Z) NextTickClimbPos = DownArrivalPoint->GetComponentLocation();
}

void ACClimbableRope::OnUpPointBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PopInteractButton(OtherActor, false);
}

void ACClimbableRope::OnDownPointBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PopInteractButton(OtherActor, true);
}

void ACClimbableRope::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(OtherActor))
	{
		if (ACPlayerController* PCC = Cast<ACPlayerController>(PC->GetController()))
		{
			PCC->NPCInteract_UnShow();
		}
	}
}

void ACClimbableRope::PopInteractButton(AActor* OtherActor, bool IsUpWard)
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(OtherActor);
	if (PC == nullptr) return;
	if (PC->GetState(PLAYER_CLIMBING_ROPE)) return;
	ACPlayerController* PCC = Cast<ACPlayerController>(PC->GetController());
	if (PCC == nullptr) return;

	bIsUpWard = IsUpWard;
	PCC->ClimbRopeInteract_ShowAndInputReady(this);
}

