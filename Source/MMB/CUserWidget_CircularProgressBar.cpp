#include "CUserWidget_CircularProgressBar.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
//#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetMaterialLibrary.h"

UCUserWidget_CircularProgressBar::UCUserWidget_CircularProgressBar(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ProgressTextureIndex = 0.f;
	bEraseRecentDamage = false;
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

	if (bEraseRecentDamage && RecentDamageSum > 0.f)
	{
		RecentDamageSum -= RecentDamageSum * InDeltaTime * 0.6f;
		RecentDamageSum = RecentDamageSum < 0.f ? 0.f : RecentDamageSum;
	}
}

void UCUserWidget_CircularProgressBar::NativeConstruct()
{
	Super::NativeConstruct();

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
	if (CenterGaugeText == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CenterGaugeText Not Found"));
		return;
	}
	CenterGaugeText->SetText(FText::FromString("0%"));
}

void UCUserWidget_CircularProgressBar::SetProgress(float NewProgress)
{
	if (CircularProgressBarMPCInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CircularProgressBarMPCInstance Can Not Found"));
		return;
	}

	if (NewProgress <= 0.f)
	{
		bEraseRecentDamage = true;
		NewProgress = 0.f;
	}

	CircularProgressBarMPCInstance->SetScalarParameterValue(FName("Progress"), NewProgress);
	CircularProgressBarMPCInstance->SetScalarParameterValue(FName("RecentDamage"), RecentDamageSum);

}

void UCUserWidget_CircularProgressBar::GetProgress(float& CurrProgress)
{
	//TODO
}

void UCUserWidget_CircularProgressBar::SetStaminaProgress(float NewProgress)
{
	if (CircularProgressBarMPCInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CircularProgressBarMPCInstance Can Not Found"));
		return;
	}
	CircularProgressBarMPCInstance->SetScalarParameterValue(FName("StaminaProgress"), NewProgress);
}

void UCUserWidget_CircularProgressBar::SetSegments(float NewSegments)
{
	if (CircularProgressBarMPCInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CircularProgressBarMPCInstance Can Not Found"));
		return;
	}
	CircularProgressBarMPCInstance->SetScalarParameterValue(FName("Segments"), NewSegments);
}

void UCUserWidget_CircularProgressBar::GetSegments(float& CurrSegments)
{
	//TODO
}

void UCUserWidget_CircularProgressBar::SetStaminaSegments(float NewSegments)
{
	if (CircularProgressBarMPCInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CircularProgressBarMPCInstance Can Not Found"));
		return;
	}
	CircularProgressBarMPCInstance->SetScalarParameterValue(FName("StaminaSegments"), NewSegments);
}

void UCUserWidget_CircularProgressBar::AddRecentDamage(float Damage)
{
	RecentDamageSum += Damage;
	bEraseRecentDamage = false;
	GetWorld()->GetTimerManager().ClearTimer(RecentDamageTimer);
	GetWorld()->GetTimerManager().SetTimer(RecentDamageTimer, FTimerDelegate::CreateLambda([&] {
		bEraseRecentDamage = true;
		}), 2.f, false
	);
}

void UCUserWidget_CircularProgressBar::SetCenterProgress(float NewProgress)
{
	if (CircularProgressBarMPCInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CircularProgressBarMPCInstance Can Not Found"));
		return;
	}
	if (CenterGaugeText == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CenterGaugeText Not Found"));
		return;
	}
	CircularProgressBarMPCInstance->SetScalarParameterValue(FName("CenterProgress"), NewProgress);
	
	CenterGaugeText->SetText(FText::FromString(FString::FromInt(FMath::Floor(NewProgress * 100.f)) + "%"));
}
