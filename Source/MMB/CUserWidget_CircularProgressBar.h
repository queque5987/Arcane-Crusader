#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "CUserWidget_CircularProgressBar.generated.h"

UCLASS()
class MMB_API UCUserWidget_CircularProgressBar : public UUserWidget
{
	GENERATED_BODY()

	UCUserWidget_CircularProgressBar(const FObjectInitializer& ObjectInitializer);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeConstruct() override;

	float ProgressTextureIndex;
	float RecentDamageSum;
	bool bEraseRecentDamage;
	FTimerHandle RecentDamageTimer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> CircularProgressBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CenterGaugeText;

	class UMaterialParameterCollectionInstance* CircularProgressBarMPCInstance;

public:
	void SetProgress(float NewProgress);
	void GetProgress(float& CurrProgress);
	void SetStaminaProgress(float NewProgress);
	//void GetProgress(float& CurrProgress);
	void SetSegments(float NewSegments);
	void GetSegments(float& CurrSegments);
	void SetStaminaSegments(float NewSegments);
	//void GetStaminaSegments(float& CurrSegments);
	void AddRecentDamage(float Damage);
	void SetRecentDamageSum(float NewRecentDamageSum) { RecentDamageSum = NewRecentDamageSum; }
	float GetRecentDamageSum() { return RecentDamageSum; };
	void SetCenterProgress(float NewProgress);
};
