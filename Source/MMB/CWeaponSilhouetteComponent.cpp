#include "CWeaponSilhouetteComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SplineComponent.h"
#include "IWeapon.h"

const int32 UCWeaponSilhouetteComponent::ThrowingStaff(1 << 0);
const int32 UCWeaponSilhouetteComponent::ThrowingForward(1 << 1);
const int32 UCWeaponSilhouetteComponent::RetrieveStaff(1 << 2);

UCWeaponSilhouetteComponent::UCWeaponSilhouetteComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	WeaponOraEffect = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponOraEffectComponent"));

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("StaffThrowProjectSpline"));
	AttachedEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("AttachedEffectComponent"));

	ConstructorHelpers::FObjectFinder<UParticleSystem> RotatingEffectFinder(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_Whirlwind/P_Whirlwind_Lightning_Veng_01"));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> SKFinder(TEXT("/Game/Resources/Meshes/BattleStaff_HammerEffect/SK_Blunt_IceElemental"));
	if (SKFinder.Succeeded())
	{
		WeaponOraEffect->SetSkeletalMesh(SKFinder.Object);
		WeaponOraEffect->SetRelativeRotation(FRotator(90.f, 0.f, 90.f));
		WeaponOraEffect->SetRelativeLocation(FVector(0.f, -38.f, -5.f));
		WeaponOraEffect->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
	}
	if (RotatingEffectFinder.Succeeded()) AttachedEffectComponent->SetTemplate(RotatingEffectFinder.Object);

	WeaponOraEffect->SetupAttachment(this);
	AttachedEffectComponent->SetupAttachment(WeaponOraEffect);
	AttachedEffectComponent->bAutoActivate = false;
	AttachedEffectComponent->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	AttachedEffectComponent->SetRelativeScale3D(FVector(0.6f));
	BoolState = 0;

	ThrowingSplineTime = 0.f;
	ThrowingHitStack = 0;
	ThrowingHitInterval = 0.02f;

	WeaponOraEffect->SetRenderCustomDepth(true);
	WeaponOraEffect->SetCustomDepthStencilValue(1);
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
	if (GetBoolState(ThrowingForward))
	{
		UE_LOG(LogTemp, Log, TEXT("RetrieveLocation : %s"), *RetrieveLocation.ToString());

		SplineComponent->SetLocationAtSplinePoint(2, RetrieveLocation, ESplineCoordinateSpace::World);
		SplineComponent->SetSplinePointType(2, ESplinePointType::Linear);
	}
	else
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
	}

	SplineComponent->UpdateSpline();
}

bool UCWeaponSilhouetteComponent::GetBoolState(int32 StateIndex)
{
	if (BoolState & StateIndex) return true;
	else return false;
}

void UCWeaponSilhouetteComponent::SetBoolState(int32 StateIndex, bool b)
{
	if (GetBoolState(StateIndex) ^ b)
	{
		if (b) BoolState += StateIndex;
		else BoolState -= StateIndex;
	}
}

void UCWeaponSilhouetteComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TurningOff > 0.f && !GetBoolState(ThrowingStaff))
	{
		TurningOff -= DeltaTime * 0.5f;
		if (TurningOff < 0.f) TurningOff = 0.f;

		if (OraEffectMaterial == nullptr) return;
		OraEffectMaterial->SetScalarParameterValue("Attacking", TurningOff);
	}

	if (GetBoolState(ThrowingStaff))
	{
		UE_LOG(LogTemp, Log, TEXT("ThrowingForward : %s"), GetBoolState(ThrowingForward) && GetBoolState(RetrieveStaff) ? TEXT("True") : TEXT("False"));
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
			if (IW != nullptr)
			{
				DidItHit = IW->MeleeAttackHitCheck(3);
				IW->OnAttackSwingEnd();
			}
		}
	// Move
		FVector ThrowLocation = SplineComponent->GetLocationAtTime(ThrowingSplineTime, ESplineCoordinateSpace::World);

		float NextPos = DidItHit ? DeltaTime / 64.f : DeltaTime / 4.f;
		if (GetBoolState(ThrowingForward) && (DidItHit || ThrowingSplineTime > 0.45f))
		{
			float Weight = 5.f;
			float D = FMath::Atan((0.5f - ThrowingSplineTime) / 0.05f * Weight) / FMath::Atan(Weight);
			NextPos *= GetBoolState(RetrieveStaff) ? 3.f : D;
		}
		ThrowingSplineTime += NextPos;

		if ((AttachedWeapon != nullptr) && (
			GetBoolState(ThrowingForward) && GetBoolState(RetrieveStaff) || //ThrowingForward_Retrieving or
			!GetBoolState(ThrowingForward) && ThrowingSplineTime > 0.5f		//ThrowingCircular_Returning
			))
		{
			UpdateSpline(AttachedWeapon->GetActorLocation());
		}
		if (GetBoolState(ThrowingForward)) ThrowingRotateTime += DeltaTime;
		WeaponOraEffect->SetWorldLocation(ThrowLocation);
		WeaponOraEffect->SetRelativeRotation(FRotator(90.f, 0.f, (GetBoolState(ThrowingForward) ? ThrowingRotateTime * 360.f * 4.f : ThrowingSplineTime * 360.f * 8.f)));
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
			SetBoolState(ThrowingStaff, false);
			SetBoolState(ThrowingForward, false);
			SetBoolState(RetrieveStaff, false);
			AttachToComponent(IW->GetStaffStaticMeshComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			WeaponOraEffect->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			WeaponOraEffect->SetRelativeRotation(FRotator(90.f, 0.f, 90.f));
			WeaponOraEffect->SetRelativeLocation(FVector(0.f, -38.f, -5.f));
			DeactivateEffect();
			//AttachedEffectComponent->Deactivate();
			AttachedEffectComponent->DeactivateImmediate();
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

void UCWeaponSilhouetteComponent::ThrowCircular(FVector StartLocation, FVector EndLocation, class AActor* Weapon)
{
	WeaponOraEffect->DetachFromParent();

	FVector Direction = (EndLocation - StartLocation).GetSafeNormal();
	FVector HorizontalDirection = FVector(Direction.Y, -Direction.X, Direction.Z);
	float HorizontalDistance = FVector::Distance(StartLocation, EndLocation) / 2.f;
	FVector MidLocation_L = StartLocation + (Direction * HorizontalDistance) + (HorizontalDirection * (HorizontalDistance / 2.f));
	FVector MidLocation_R = StartLocation + (Direction * HorizontalDistance) - (HorizontalDirection * (HorizontalDistance / 2.f));
	//float TangentScale = 2.f;

	AttachedEffectComponent->Activate();

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

	SetBoolState(ThrowingStaff, true);
	SetBoolState(ThrowingForward, false);
	ActivateEffect();
}

void UCWeaponSilhouetteComponent::ThrowForward(FVector StartLocation, FVector EndLocation, AActor* Weapon)
{
	WeaponOraEffect->DetachFromParent();

	//FVector Direction = (EndLocation - StartLocation).GetSafeNormal();
	//FVector HorizontalDirection = FVector(Direction.Y, -Direction.X, Direction.Z);
	//float HorizontalDistance = FVector::Distance(StartLocation, EndLocation) / 2.f;
	//FVector MidLocation_L = StartLocation + (Direction * HorizontalDistance) + (HorizontalDirection * (HorizontalDistance / 2.f));
	//FVector MidLocation_R = StartLocation + (Direction * HorizontalDistance) - (HorizontalDirection * (HorizontalDistance / 2.f));

	AttachedEffectComponent->Activate();

	AttachedWeapon = Weapon;
	ThrowingRotateTime = 0.f;

	SplineComponent->ClearSplinePoints();

	SplineComponent->AddSplinePoint(StartLocation, ESplineCoordinateSpace::World);
	SplineComponent->SetSplinePointType(0, ESplinePointType::Linear);

	SplineComponent->AddSplinePoint(EndLocation, ESplineCoordinateSpace::World);
	SplineComponent->SetSplinePointType(1, ESplinePointType::Linear);

	SplineComponent->AddSplinePoint(StartLocation, ESplineCoordinateSpace::World);
	SplineComponent->SetSplinePointType(2, ESplinePointType::Linear);

	SplineComponent->UpdateSpline();

	SetBoolState(ThrowingStaff, true);
	SetBoolState(ThrowingForward, true);
	ActivateEffect();
}

void UCWeaponSilhouetteComponent::InstantRetrieveStaff()
{
	SetBoolState(RetrieveStaff, true);
}
