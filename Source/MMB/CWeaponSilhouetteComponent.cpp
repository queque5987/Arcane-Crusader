#include "CWeaponSilhouetteComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/SplineComponent.h"
#include "IWeapon.h"

UCWeaponSilhouetteComponent::UCWeaponSilhouetteComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	WeaponOraEffect = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponOraEffectComponent"));

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("StaffThrowProjectSpline"));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> SKFinder(TEXT("/Game/Resources/Meshes/BattleStaff_HammerEffect/SK_Blunt_IceElemental"));
	if (SKFinder.Succeeded())
	{
		WeaponOraEffect->SetSkeletalMesh(SKFinder.Object);
		WeaponOraEffect->SetRelativeRotation(FRotator(90.f, 0.f, 90.f));
		WeaponOraEffect->SetRelativeLocation(FVector(0.f, -38.f, -5.f));
		WeaponOraEffect->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
	}
	WeaponOraEffect->SetupAttachment(this);

	ThrowingStaff = false;
	ThrowingSplineTime = 0.f;
	ThrowingHitStack = 0;
	ThrowingHitInterval = 0.02f;
}

void UCWeaponSilhouetteComponent::BeginPlay()
{
	Super::BeginPlay();

	if (WeaponOraEffect != nullptr)
	{
		UMaterialInterface* MI = WeaponOraEffect->GetMaterial(0);
		if (MI != nullptr)
		{
			OraEffectMaterial = Cast<UMaterialInstanceDynamic>(MI);
			if (!OraEffectMaterial)
			{
				OraEffectMaterial = UMaterialInstanceDynamic::Create(MI, this);
				
				WeaponOraEffect->SetMaterial(0, OraEffectMaterial);
			}
		}
	}
}

void UCWeaponSilhouetteComponent::UpdateSpline(FVector RetrieveLocation)
{
	FVector EndLocation = SplineComponent->GetLocationAtSplinePoint(2, ESplineCoordinateSpace::World);

	FVector Direction = (EndLocation - RetrieveLocation).GetSafeNormal();
	FVector HorizontalDirection = FVector(Direction.Y, -Direction.X, Direction.Z);
	float HorizontalDistance = FVector::Distance(EndLocation, RetrieveLocation) / 2.f;
	FVector MidLocation = RetrieveLocation + (Direction * HorizontalDistance) - (HorizontalDirection * (HorizontalDistance / 2.f));


	SplineComponent->SetLocationAtSplinePoint(3, MidLocation, ESplineCoordinateSpace::World);
	SplineComponent->SetSplinePointType(3, ESplinePointType::Curve);

	SplineComponent->SetLocationAtSplinePoint(4, RetrieveLocation, ESplineCoordinateSpace::World);
	SplineComponent->SetSplinePointType(4, ESplinePointType::Curve);

	SplineComponent->UpdateSpline();

	//DrawDebugSphere(GetWorld(), EndLocation, 30.f, 32, FColor::Green);
	//DrawDebugSphere(GetWorld(), MidLocation, 30.f, 32, FColor::Yellow);
	//DrawDebugSphere(GetWorld(), RetrieveLocation, 30.f, 32, FColor::Red);
}

void UCWeaponSilhouetteComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TurningOff > 0.f && !ThrowingStaff)
	{
		TurningOff -= DeltaTime * 0.5f;
		if (TurningOff < 0.f) TurningOff = 0.f;

		if (OraEffectMaterial == nullptr) return;
		OraEffectMaterial->SetScalarParameterValue("Attacking", TurningOff);
	}

	if (ThrowingStaff)
	{
	// Hit
		bool DidItHit = false;
		if (ThrowingSplineTime > ThrowingHitStack * ThrowingHitInterval)
		{
			ThrowingHitStack += 1;
			if (AttachedWeapon == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("AttachedWeapon Is Not Correct Weapon Type"));
				return;
			}
			IIWeapon* IW = Cast<IIWeapon>(AttachedWeapon);
			if (IW != nullptr) DidItHit = IW->MeleeAttackHitCheck(3);
		}
	// Move
		FVector ThrowLocation = SplineComponent->GetLocationAtTime(ThrowingSplineTime, ESplineCoordinateSpace::World);
		ThrowingSplineTime += DidItHit ? DeltaTime / 64.f : DeltaTime / 4.f;

		if (ThrowingSplineTime > 0.5f && AttachedWeapon != nullptr)
		{
			UpdateSpline(AttachedWeapon->GetActorLocation());
		}

		WeaponOraEffect->SetWorldLocation(ThrowLocation);
		WeaponOraEffect->SetRelativeRotation(FRotator(90.f, 0.f, ThrowingSplineTime * 360.f * 8.f));
	// Retrieve
		if (ThrowingSplineTime > 1.f)
		{
			if (AttachedWeapon == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("AttachedWeapon Is Not Correct Weapon Type"));
				return;
			}
			IIWeapon* IW = Cast<IIWeapon>(AttachedWeapon);
			if (IW == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("AttachedWeapon Is Not Correct Weapon Type"));
				return;
			}
			ThrowingSplineTime = 0.f;
			ThrowingHitStack = 0;
			ThrowingStaff = false;
			AttachToComponent(IW->GetStaffStaticMeshComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			WeaponOraEffect->SetRelativeRotation(FRotator(90.f, 0.f, 90.f));
			WeaponOraEffect->SetRelativeLocation(FVector(0.f, -38.f, -5.f));
			DeactivateEffect();
		}
	}
}

void UCWeaponSilhouetteComponent::SetEffectVisibility(bool e)
{
	WeaponOraEffect->SetVisibility(e);
}

void UCWeaponSilhouetteComponent::ActivateEffect()
{
	if (OraEffectMaterial == nullptr) return;
	OraEffectMaterial->SetScalarParameterValue("Attacking", 1.f);
}

void UCWeaponSilhouetteComponent::DeactivateEffect()
{
	TurningOff = 1.f;
}

FVector UCWeaponSilhouetteComponent::GetWeaponLocation(bool IsLeft)
{
	//if (WeaponOraEffect != nullptr) DrawDebugSphere(GetWorld(), WeaponOraEffect->GetComponentLocation(), 300.f, 32, FColor::Yellow, false, 2.f);

	return (WeaponOraEffect != nullptr) ? WeaponOraEffect->GetComponentLocation() : FVector();
}

void UCWeaponSilhouetteComponent::ThrowForward(FVector StartLocation, FVector EndLocation, class AActor* Weapon)
{
	FVector Direction = (EndLocation - StartLocation).GetSafeNormal();
	FVector HorizontalDirection = FVector(Direction.Y, -Direction.X, Direction.Z);
	float HorizontalDistance = FVector::Distance(StartLocation, EndLocation) / 2.f;
	FVector MidLocation_L = StartLocation + (Direction * HorizontalDistance) + (HorizontalDirection * (HorizontalDistance / 2.f));
	FVector MidLocation_R = StartLocation + (Direction * HorizontalDistance) - (HorizontalDirection * (HorizontalDistance / 2.f));
	float TangentScale = 2.f;

	AttachedWeapon = Weapon;

	SplineComponent->ClearSplinePoints();

	SplineComponent->AddSplinePoint(StartLocation, ESplineCoordinateSpace::World);
	SplineComponent->SetSplinePointType(0, ESplinePointType::Curve);

	SplineComponent->AddSplinePoint(MidLocation_L, ESplineCoordinateSpace::World);
	SplineComponent->SetSplinePointType(1, ESplinePointType::Curve);

	SplineComponent->AddSplinePoint(EndLocation, ESplineCoordinateSpace::World);
	SplineComponent->SetSplinePointType(2, ESplinePointType::Curve);

	SplineComponent->AddSplinePoint(MidLocation_R, ESplineCoordinateSpace::World);
	SplineComponent->SetSplinePointType(3, ESplinePointType::Curve);

	SplineComponent->AddSplinePoint(StartLocation, ESplineCoordinateSpace::World);
	SplineComponent->SetSplinePointType(4, ESplinePointType::Curve);

	SplineComponent->UpdateSpline();

	//DrawDebugSphere(GetWorld(), StartLocation, 30.f, 32, FColor::Green, false, 2.f);
	//DrawDebugSphere(GetWorld(), MidLocation_L, 30.f, 32, FColor::Yellow, false, 2.f);
	//DrawDebugSphere(GetWorld(), MidLocation_R, 30.f, 32, FColor::Yellow, false, 2.f);
	//DrawDebugSphere(GetWorld(), EndLocation, 30.f, 32, FColor::Red, false, 2.f);
	ThrowingStaff = true;
	ActivateEffect();
}

void UCWeaponSilhouetteComponent::RetrieveStaff()
{
}

