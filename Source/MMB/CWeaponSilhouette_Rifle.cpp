#include "CWeaponSilhouette_Rifle.h"
#include "Materials/MaterialInstanceDynamic.h"

UCWeaponSilhouette_Rifle::UCWeaponSilhouette_Rifle()
{
	PrimaryComponentTick.bCanEverTick = true;
	SniperRifleSMComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SniperRifleSMComponent"));
	ShotGunSMComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShotGunSMComponent"));
	MachineGunSMComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MachineGunSMComponent"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> SRFinder(TEXT("/Game/Resources/Meshes/RifleStaff_Sniper/Gaus_M13_export"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> SGFinder(TEXT("/Game/Resources/Meshes/RifleStaff_ShotGun/M1014/M4"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> MGFinder(TEXT("/Game/Resources/Meshes/RifleStaff_Machingun/FN_Scar_L/scarL"));

	if (SRFinder.Succeeded()) SniperRifleSMComponent->SetStaticMesh(SRFinder.Object);
	if (SGFinder.Succeeded()) ShotGunSMComponent->SetStaticMesh(SGFinder.Object);
	if (MGFinder.Succeeded()) MachineGunSMComponent->SetStaticMesh(MGFinder.Object);

	SniperRifleSMComponent->SetupAttachment(this);
	ShotGunSMComponent->SetupAttachment(this);
	MachineGunSMComponent->SetupAttachment(this);

	SniperRifleSMComponent->SetRelativeLocation(FVector(0.f, 50.f, -8.f));
	SniperRifleSMComponent->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));
	ShotGunSMComponent->SetRelativeLocation(FVector(0.f, 34.f, -28.f));
	ShotGunSMComponent->SetRelativeScale3D(FVector(2.f, -2.f, 2.f));
	MachineGunSMComponent->SetRelativeLocation(FVector(-5.f, 9.f, -30.f));
	MachineGunSMComponent->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));

	CurrEffect = 0;
}


void UCWeaponSilhouette_Rifle::BeginPlay()
{
	Super::BeginPlay();

	if (SniperRifleSMComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SniperRifleEffect Is Not Loaded"));
		return;
	}
	if (ShotGunSMComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SniperRifleEffect Is Not Loaded"));
		return;
	}
	if (MachineGunSMComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SniperRifleEffect Is Not Loaded"));
		return;
	}

	UMaterialInterface* MI = SniperRifleSMComponent->GetMaterial(0);
	if (MI != nullptr)
	{
		SniperRifleMaterial = Cast<UMaterialInstanceDynamic>(MI);
		if (!SniperRifleMaterial)
		{
			SniperRifleMaterial = UMaterialInstanceDynamic::Create(MI, this);
			SniperRifleSMComponent->SetMaterial(0, SniperRifleMaterial);
		}
	}
	MI = ShotGunSMComponent->GetMaterial(0);
	if (MI != nullptr)
	{
		ShotGunMaterial = Cast<UMaterialInstanceDynamic>(MI);
		if (!ShotGunMaterial)
		{
			ShotGunMaterial = UMaterialInstanceDynamic::Create(MI, this);
			ShotGunSMComponent->SetMaterial(0, ShotGunMaterial);
		}
	}
	MI = MachineGunSMComponent->GetMaterial(0);
	if (MI != nullptr)
	{
		MachineGunMaterial = Cast<UMaterialInstanceDynamic>(MI);
		if (!MachineGunMaterial)
		{
			MachineGunMaterial = UMaterialInstanceDynamic::Create(MI, this);
			MachineGunSMComponent->SetMaterial(0, MachineGunMaterial);
		}
	}
}


void UCWeaponSilhouette_Rifle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TurningOff > 0.f)
	{
		TurningOff -= DeltaTime * 0.5f;
		if (TurningOff < 0.f) TurningOff = 0.f;

		SetParameter_Attacking(TurningOff);
	}
}

void UCWeaponSilhouette_Rifle::ActivateEffect()
{
	SetParameter_Attacking(1.f);
}

void UCWeaponSilhouette_Rifle::DeactivateEffect()
{
	TurningOff = 1.f;
}

void UCWeaponSilhouette_Rifle::SetCharge(float e, bool IsLeft)
{
	SniperRifleMaterial->SetScalarParameterValue("Charge", e);
}

void UCWeaponSilhouette_Rifle::SetWeaponEffect(int32 Index)
{
	CurrEffect = Index;

	SniperRifleSMComponent->SetVisibility(Index == 0 ? true : false);
	ShotGunSMComponent->SetVisibility(Index == 1 ? true : false);
	MachineGunSMComponent->SetVisibility(Index == 2 ? true : false);
}

void UCWeaponSilhouette_Rifle::SetParameter_Attacking(float NewAttacking)
{
	switch (CurrEffect)
	{
	case(0):
		if (SniperRifleMaterial == nullptr) return;
		SniperRifleMaterial->SetScalarParameterValue("Attacking", NewAttacking);
		break;
	case(1):
		if (ShotGunMaterial == nullptr) return;
		ShotGunMaterial->SetScalarParameterValue("Attacking", NewAttacking);
		break;
	case(2):
		if (MachineGunMaterial == nullptr) return;
		MachineGunMaterial->SetScalarParameterValue("Attacking", NewAttacking);
		break;
	default:
		break;
	}
}

