// Fill out your copyright notice in the Description page of Project Settings.


#include "CWeaponSilhouette_Gauntlet.h"

UCWeaponSilhouette_Gauntlet::UCWeaponSilhouette_Gauntlet(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;

	WeaponOraEffect = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponOraEffectComponent"));
	WeaponOraEffect_L = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponOraEffect_LComponent"));

	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> GraspAnimFinder(TEXT("/Game/Resources/Meshes/BattleStaff_Gauntlet/daedric-gauntlet-skyrim-fanart/source/GraspAnim"));
	ConstructorHelpers::FObjectFinder<UAnimSequenceBase> UnGraspAnimFinder(TEXT("/Game/Resources/Meshes/BattleStaff_Gauntlet/daedric-gauntlet-skyrim-fanart/source/GraspAnim_R"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_GauntletFinder(TEXT("/Game/Resources/Meshes/BattleStaff_Gauntlet/daedric-gauntlet-skyrim-fanart/source/FBX"));

	if (SK_GauntletFinder.Succeeded())
	{
		WeaponOraEffect->SetSkeletalMesh(SK_GauntletFinder.Object);
		WeaponOraEffect->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
		WeaponOraEffect->SetRelativeLocation(FVector(-15.f, 10.f, -38.f));
		WeaponOraEffect->SetRelativeScale3D(FVector(5.f, 2.5f, 3.5f));

		WeaponOraEffect_L->SetSkeletalMesh(SK_GauntletFinder.Object);
		WeaponOraEffect_L->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
		WeaponOraEffect_L->SetRelativeLocation(FVector(15.f, -10.f, 38.f));
		WeaponOraEffect_L->SetRelativeScale3D(FVector(-5.f, -2.5f, -3.5f));
	}

	if (GraspAnimFinder.Succeeded())
	{
		GraspAnim = GraspAnimFinder.Object;
	}
	if (UnGraspAnimFinder.Succeeded())
	{
		UnGraspAnim = UnGraspAnimFinder.Object;
	}
	
	TurningOff = 0.f;
}

void UCWeaponSilhouette_Gauntlet::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TurningOff > 0.f)
	{
		TurningOff -= DeltaTime * 0.5f;
		if (TurningOff < 0.f) TurningOff = 0.f;

		if (OraEffectMaterial != nullptr) OraEffectMaterial->SetScalarParameterValue("Attacking", TurningOff);
		if (OraEffectMaterial_L != nullptr) OraEffectMaterial_L->SetScalarParameterValue("Attacking", TurningOff);
	}

	//if (WeaponOraEffect != nullptr)		DrawDebugSphere(GetWorld(), WeaponOraEffect->GetComponentLocation(), 100.f, 32.f, FColor::Green);
	//if (WeaponOraEffect_L != nullptr)	DrawDebugSphere(GetWorld(), WeaponOraEffect_L->GetComponentLocation(), 100.f, 32.f, FColor::Green);
}

void UCWeaponSilhouette_Gauntlet::SetEffectVisibility(bool e)
{
	WeaponOraEffect->SetVisibility(e);
	WeaponOraEffect_L->SetVisibility(e);
}

void UCWeaponSilhouette_Gauntlet::ActivateEffect()
{
	TurningOff = 0.f;

	if (OraEffectMaterial == nullptr) return;
	OraEffectMaterial->SetScalarParameterValue("Attacking", 1.f);

	if (OraEffectMaterial_L == nullptr) return;
	OraEffectMaterial_L->SetScalarParameterValue("Attacking", 1.f);

	GraspFist(true);
	//WeaponOraEffect->PlayAnimation();
}

void UCWeaponSilhouette_Gauntlet::DeactivateEffect()
{
	TurningOff = 1.f;

	GraspFist(false);
}

void UCWeaponSilhouette_Gauntlet::SetCharge(float e, bool IsLeft)
{
	if (IsLeft && OraEffectMaterial_L != nullptr)
	{
		OraEffectMaterial_L->SetScalarParameterValue("Charge", e);
	}
	else if(!IsLeft && OraEffectMaterial != nullptr)
	{
		OraEffectMaterial->SetScalarParameterValue("Charge", e);
	}
}

FVector UCWeaponSilhouette_Gauntlet::GetWeaponLocation(bool IsLeft)
{
	if (!IsLeft && WeaponOraEffect != nullptr)
	{
		return WeaponOraEffect->GetComponentLocation();
	}
	else if (IsLeft && WeaponOraEffect_L != nullptr)
	{
		return WeaponOraEffect_L->GetComponentLocation();
	}
	return FVector();
}

void UCWeaponSilhouette_Gauntlet::GraspFist(bool e)
{
	if (WeaponOraEffect == nullptr || WeaponOraEffect_L == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot Play Grasp Animation - WeaponOraEffect Not Found"));
		return;
	}
	if (GraspAnim == nullptr || UnGraspAnim == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot Play Grasp Animation - GraspAnim Not Found"));
	}

	WeaponOraEffect->PlayAnimation(e ? GraspAnim : UnGraspAnim, false);
	WeaponOraEffect_L->PlayAnimation(e ? GraspAnim : UnGraspAnim, false);
}

void UCWeaponSilhouette_Gauntlet::BeginPlay()
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

	if (WeaponOraEffect_L != nullptr)
	{
		UMaterialInterface* MI = WeaponOraEffect_L->GetMaterial(0);
		if (MI != nullptr)
		{
			OraEffectMaterial_L = Cast<UMaterialInstanceDynamic>(MI);
			if (!OraEffectMaterial_L)
			{
				OraEffectMaterial_L = UMaterialInstanceDynamic::Create(MI, this);

				WeaponOraEffect_L->SetMaterial(0, OraEffectMaterial_L);
			}
		}
	}

}
