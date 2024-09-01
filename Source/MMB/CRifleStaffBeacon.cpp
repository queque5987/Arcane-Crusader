#include "CRifleStaffBeacon.h"
#include "components/SplineComponent.h"
#include "IWeapon.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

ACRifleStaffBeacon::ACRifleStaffBeacon()
{
	PrimaryActorTick.bCanEverTick = true;

	BeaconComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BeaconComponent"));
	RuneWordComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RuneWordComponent"));
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));

	ConstructorHelpers::FObjectFinder<USoundCue> TickingSCFinder(TEXT("/Game/Resources/Sound/Bomb/SC_Ticking"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> BeaconFinder(TEXT("/Game/Resources/Meshes/RifleStaffUltBeacon/RifleStaffBeacon"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> RuneWordFinder(TEXT("/Game/Resources/Meshes/RifleStaffUltBeacon/RifleStaffRundWord"));

	if (BeaconFinder.Succeeded()) BeaconComponent->SetStaticMesh(BeaconFinder.Object);
	if (RuneWordFinder.Succeeded()) RuneWordComponent->SetStaticMesh(RuneWordFinder.Object);
	if (TickingSCFinder.Succeeded()) TickingSoundCue = TickingSCFinder.Object;
	
	//TickingSoundCue

	SetRootComponent(BeaconComponent);
	RuneWordComponent->SetupAttachment(BeaconComponent);
	
	Departure = false;
	OnGround = false;
	RuneWordStretched = false;

	fZoom = 0.f;
	DepartureClock = 0.f;
	AutoDestoryTimer = 10.f;

	BeaconComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BeaconComponent->SetRelativeScale3D(FVector(1.f - FMath::Atan(1.f)));
	RuneWordComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	RuneWordComponent->SetRelativeScale3D(FVector(15.f, 15.f, 1.f));
}

void ACRifleStaffBeacon::BeginPlay()
{
	Super::BeginPlay();
	
	UMaterialInterface* MI = RuneWordComponent->GetMaterial(0);
	if (MI == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Can Not Load RifleStaffBeacon Material"));
		return;
	}
	RuneWordMaterial = UMaterialInstanceDynamic::Create(MI, this);
	RuneWordComponent->SetMaterial(0, RuneWordMaterial);
	RuneWordComponent->SetScalarParameterValueOnMaterials("Zoom", 0.f);
}

void ACRifleStaffBeacon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Departure)
	{
		if (SplineComponent == nullptr) return;
		DepartureClock += DeltaTime / 6.4f * (4 + 5.8f * FMath::Abs(DepartureClock - 0.5f) / 0.5f );
		if (DepartureClock > 1.f)
		{
			DepartureClock = 1.f;
			Departure = false;
			OnGround = true;
		}
		FVector NextLocation = SplineComponent->GetLocationAtTime(DepartureClock, ESplineCoordinateSpace::World);
		SetActorLocation(NextLocation);
	}

	if (!OnGround) return;

	if (RuneWordStretched)
	{
		AutoDestoryTimer -= DeltaTime;
		if (AutoDestoryTimer < 0.f)
		{
			Destroy();
		}
		else if (AutoDestoryTimer < 3.f)
		{
			RuneWordComponent->SetScalarParameterValueOnMaterials("Zoom", AutoDestoryTimer / 3.f);
			BeaconComponent->SetRelativeScale3D(FVector(AutoDestoryTimer / 3.f));
		}
		return;
	}

	if (fZoom >= 1.f)
	{
		//DrawDebugSphere(GetWorld(), SplineComponent->GetLocationAtTime(DepartureClock, ESplineCoordinateSpace::World), 200.f, 32.f, FColor::Red, false, 2.f);
		RuneWordStretched = true;
		fZoom = 1.f;
		if (SummonedRifleStaff == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("ACRifleStaffBeacon : SummonedRifleStaff Is Not Set"));
		}
		SummonedRifleStaff->UltBombArea(SplineComponent->GetLocationAtTime(DepartureClock, ESplineCoordinateSpace::World), 750.f);
	}
	RuneWordComponent->SetScalarParameterValueOnMaterials("Zoom", fZoom);

	BeaconComponent->SetRelativeScale3D(FVector(1.f - FMath::Atan(1.f) + FMath::Atan(fZoom)));
	fZoom += DeltaTime / 1.2f;
}

void ACRifleStaffBeacon::HitGround()
{
	OnGround = true;
}

void ACRifleStaffBeacon::Throw(FVector StartLocation, FVector Destination)
{
	SplineComponent->ClearSplinePoints();
	FVector HighLocation = (StartLocation + Destination) / 2.f;
	HighLocation.Z += 500.f + FVector::Dist2D(StartLocation, Destination) / 10.f;
	SplineComponent->AddSplineWorldPoint(StartLocation);
	SplineComponent->SetSplinePointType(0, ESplinePointType::Curve);
	//DrawDebugSphere(GetWorld(), StartLocation, 200.f, 32.f, FColor::Red, false, 2.f);
	SplineComponent->AddSplineWorldPoint(HighLocation);
	SplineComponent->SetSplinePointType(1, ESplinePointType::Curve);
	//DrawDebugSphere(GetWorld(), HighLocation, 200.f, 32.f, FColor::Yellow, false, 2.f);
	SplineComponent->AddSplineWorldPoint(Destination);
	SplineComponent->SetSplinePointType(2, ESplinePointType::Curve);
	//DrawDebugSphere(GetWorld(), Destination, 200.f, 32.f, FColor::Green, false, 2.f);
	SplineComponent->UpdateSpline();
	Departure = true;
	UGameplayStatics::PlaySound2D(GetWorld(), TickingSoundCue, 1.f);
}

void ACRifleStaffBeacon::SetSummonedRifle(IIWeapon* RifleStaff)
{
	SummonedRifleStaff = RifleStaff;
}

