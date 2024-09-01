#include "CMainWeaponFloatingSpline.h"
#include "Components/SplineComponent.h"
#include "Math/UnrealMathUtility.h"
#include "LevelInstance/LevelInstanceActor.h"

ACMainWeaponFloatingSpline::ACMainWeaponFloatingSpline()
{
	PrimaryActorTick.bCanEverTick = true;
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
}

void ACMainWeaponFloatingSpline::BeginPlay()
{
	Super::BeginPlay();
	RotateActorsLocation.SetNum(RotateActors.Num());
	for (int i = 0; i < RotateActorsLocation.Num(); i++)
	{
		RotateActorsLocation[i] = 1.f / RotateActorsLocation.Num() * i;
		UE_LOG(LogTemp, Log, TEXT("%f"), RotateActorsLocation[i]);
	}
	FloatingObject->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepWorldTransform);

	FirstLocation = SplineComponent->GetRelativeLocation();
}

void ACMainWeaponFloatingSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (RotateActors.Num() < 1) return;

	//float temp;
	for (int i = 0; i < RotateActors.Num(); i++)
	{
		RotateActorsLocation[i] += DeltaTime * FMath::Max(FMath::Sin(RotateActorsLocation[i] * PI) / 2.f, 0.12f);
		if (RotateActorsLocation[i] > 1.f) RotateActorsLocation[i] -= 1.f;

		RotateActors[i]->SetActorLocation(SplineComponent->GetLocationAtTime(
			RotateActorsLocation[i],
			ESplineCoordinateSpace::World)
		);
		FRotator temp = RotateActors[i]->GetActorRotation();
		temp.Yaw = RotateActorsLocation[i] * 360.f;
		RotateActors[i]->SetActorRotation(temp);
	}
	if (FloatingObject == nullptr) return;
	ClockTicking += DeltaTime * FMath::Max(FMath::Sin((ClockTicking > FloatingTime / 2.f ? FMath::Abs(ClockTicking - FloatingTime) : ClockTicking) / FloatingTime * 2.f * PI) / 2.f, 0.1f);
	if (ClockTicking > FloatingTime) ClockTicking -= FloatingTime;
	FVector NextLocation = FVector(FirstLocation.X, FirstLocation.Y, FirstLocation.Z + (ClockTicking > FloatingTime / 2.f ? FMath::Abs(ClockTicking - FloatingTime) : ClockTicking) * 20.f);
	SplineComponent->SetRelativeLocation(NextLocation);
	
}

