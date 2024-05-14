// Fill out your copyright notice in the Description page of Project Settings.


#include "CJumpPoints.h"
#include "PCH.h"

// Sets default values
ACJumpPoints::ACJumpPoints()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ArrivalPoint0 = CreateDefaultSubobject<USphereComponent>(TEXT("ArrivalPoint0Component"));
	ArrivalPoint1 = CreateDefaultSubobject<USphereComponent>(TEXT("ArrivalPoint1Component"));
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	ArrivalPoint0->SetSphereRadius(100.f);
	ArrivalPoint1->SetSphereRadius(100.f);

	SetRootComponent(SplineComponent);
	ArrivalPoint0->SetupAttachment(SplineComponent);
	ArrivalPoint1->SetupAttachment(SplineComponent);
}

// Called when the game starts or when spawned
void ACJumpPoints::BeginPlay()
{
	Super::BeginPlay();
	//ArrivalPoint0Pos = ArrivalPoint0->GetComponentLocation();
	//ArrivalPoint1Pos = ArrivalPoint1->GetComponentLocation();

	//ExpectedTime = (ArrivalPoint0Pos - ArrivalPoint1Pos).Size() / JumpSpeed;

	ArrivalPoint0->OnComponentBeginOverlap.AddDynamic(this, &ACJumpPoints::OnPoint0BeginOverlap);
	ArrivalPoint1->OnComponentBeginOverlap.AddDynamic(this, &ACJumpPoints::OnPoint1BeginOverlap);
	ArrivalPoint0->OnComponentEndOverlap.AddDynamic(this, &ACJumpPoints::OnEndOverlap);
	ArrivalPoint1->OnComponentEndOverlap.AddDynamic(this, &ACJumpPoints::OnEndOverlap);
}

void ACJumpPoints::OnPoint0BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(OtherActor);
	if (PC == nullptr) return;
	if (PC->GetState(PLAYER_JUMPING_POINTS)) return;
	ACPlayerController* PCC = Cast<ACPlayerController>(PC->GetController());
	if (PCC == nullptr) return;

	PCC->JumpPointsInteract_ShowAndInputReady(this, 0);
}

void ACJumpPoints::OnPoint1BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(OtherActor);
	if (PC == nullptr) return;
	if (PC->GetState(PLAYER_JUMPING_POINTS)) return;
	ACPlayerController* PCC = Cast<ACPlayerController>(PC->GetController());
	if (PCC == nullptr) return;

	PCC->JumpPointsInteract_ShowAndInputReady(this, 1);
}

void ACJumpPoints::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(OtherActor);
	if (PC == nullptr) return;
	if (PC->GetState(PLAYER_JUMPING_POINTS)) return;
	ACPlayerController* PCC = Cast<ACPlayerController>(PC->GetController());
	if (PCC == nullptr) return;
	PCC->NPCInteract_UnShow();
}

void ACJumpPoints::EndJump()
{
	UE_LOG(LogTemp, Log, TEXT("JumpPoints : End Of Jump"));
	TransferingCharacter->SetState(PLAYER_JUMPING_POINTS, false);
	TransferingCharacter = nullptr;
}

// Called every frame
void ACJumpPoints::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TransferringFrom < 0 || TransferingCharacter == nullptr) return;


	TimeElapsed += DeltaTime;

	if (TimeElapsed < 0.f) return;
	if (!FlagJump)
	{
		TransferingCharacter->JumpPointJump.ExecuteIfBound(TotalTime);
		FlagJump = true;
	}

	float TimePercent = TimeElapsed / TotalTime;

	if (TimePercent >= 1.0f)
	{
		TimeElapsed = 0.f;
		TransferringFrom = -1;
		TransferingCharacter->JumpPointLand.ExecuteIfBound();
		GetWorld()->GetTimerManager().SetTimer(LandTimerHandle, this, &ACJumpPoints::EndJump, 1.2f);
		return;
	}
	float Distance = SplineComponent->GetSplineLength() * ((TransferringFrom > 0) ? (1 - TimeElapsed / TotalTime) : (TimeElapsed / TotalTime));

	FVector Position = SplineComponent->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	TransferingCharacter->SetActorLocation(Position);


	FVector Direction = SplineComponent->GetDirectionAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);

	FRotator Rotator = TransferingCharacter->GetActorRotation();
	Rotator.Yaw = (TransferringFrom > 0) ? FRotationMatrix::MakeFromX(-Direction).Rotator().Yaw : FRotationMatrix::MakeFromX(Direction).Rotator().Yaw;
	TransferingCharacter->SetActorRotation(Rotator);
}

void ACJumpPoints::TransferCharacter(ACPlayerCharacter* PC, int JumpStartPoint)
{
	TransferingCharacter = PC;
	TransferringFrom = JumpStartPoint;
	FlagJump = false;
	PC->JumpPointReady.ExecuteIfBound();
	PC->SetState(PLAYER_JUMPING_POINTS, true);
	TimeElapsed = -0.8f;

	float Distance = SplineComponent->GetSplineLength() * JumpStartPoint;

	FVector Position = SplineComponent->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	TransferingCharacter->SetActorLocation(Position);

	FVector Direction = SplineComponent->GetDirectionAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);

	FRotator Rotator = TransferingCharacter->GetActorRotation();
	Rotator.Yaw = (TransferringFrom > 0) ? FRotationMatrix::MakeFromX(-Direction).Rotator().Yaw : FRotationMatrix::MakeFromX(Direction).Rotator().Yaw;
	TransferingCharacter->SetActorRotation(Rotator);
}