#include "CUserWidget_CircularProgressBar.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
//#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetMaterialLibrary.h"

UCUserWidget_CircularProgressBar::UCUserWidget_CircularProgressBar(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ProgressTextureIndex = 0.f;
	//if (CircularProgressBar != nullptr) CircularProgressBarMaterial = CircularProgressBar->GetDynamicMaterial();
}

void UCUserWidget_CircularProgressBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (CircularProgressBarMPCInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CircularProgressBarMPCInstance Can Not Found"));
		return;
	}
	ProgressTextureIndex += 10 * InDeltaTime;
	if (ProgressTextureIndex > 24) ProgressTextureIndex = 0.f;
	CircularProgressBarMPCInstance->SetScalarParameterValue(FName("ProgressTextureIndex"), ProgressTextureIndex);
}

void UCUserWidget_CircularProgressBar::NativeConstruct()
{
	Super::NativeConstruct();
	//if (CircularProgressBar != nullptr) CircularProgressBarMaterial = CircularProgressBar->GetDynamicMaterial();
	UMaterialParameterCollection* MPC = LoadObject<UMaterialParameterCollection>(nullptr, TEXT("/Game/Player/UI/CustomUI/MPC_CircularProgressBar"));
	if (MPC == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CircularProgressBar-MPC Can Not Found"));
		return;
	}
	CircularProgressBarMPCInstance = GetWorld()->GetParameterCollectionInstance(MPC);
	if (CircularProgressBarMPCInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CircularProgressBar-MPC Instance Can Not Found"));
		return;
	}
}

void UCUserWidget_CircularProgressBar::SetProgress(float NewProgress)
{
	if (CircularProgressBarMPCInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CircularProgressBarMPCInstance Can Not Found"));
		return;
	}
	CircularProgressBarMPCInstance->SetScalarParameterValue(FName("Progress"), NewProgress);
	//UKismetMaterialLibrary::SetScalarParameterValue(GetWolrd(), nullptr, "Progress", NewProgress);
	//CircularProgressBarMaterial->SetScalarParameterValue("Progress", NewProgress);
}

void UCUserWidget_CircularProgressBar::GetProgress(float& CurrProgress)
{
	//TODO
}

void UCUserWidget_CircularProgressBar::SetSegments(float NewSegments)
{
	//if (CircularProgressBarMaterial == nullptr) return;
	//CircularProgressBarMaterial->SetScalarParameterValue("Segments", NewSegments);
}

void UCUserWidget_CircularProgressBar::GetSegments(float& CurrSegments)
{
	//TODO
}
