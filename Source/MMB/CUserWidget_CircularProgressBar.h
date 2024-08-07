#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "CUserWidget_CircularProgressBar.generated.h"

UCLASS()
class MMB_API UCUserWidget_CircularProgressBar : public UUserWidget
{
	GENERATED_BODY()

	UCUserWidget_CircularProgressBar(const FObjectInitializer& ObjectInitializer);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeConstruct() override;

	float ProgressTextureIndex;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> CircularProgressBar;

	//class UMaterialInstanceDynamic* CircularProgressBarMaterial;
	//class UMaterialParameterCollection* CircularProgressBarMPC;
	class UMaterialParameterCollectionInstance* CircularProgressBarMPCInstance;

public:
	void SetProgress(float NewProgress);
	void GetProgress(float& CurrProgress);
	void SetSegments(float NewSegments);
	void GetSegments(float& CurrSegments);
};
