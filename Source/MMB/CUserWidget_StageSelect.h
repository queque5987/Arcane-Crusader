#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Listview.h"
#include "Components/Image.h"
#include "CUserWidget_StageSelect.generated.h"

UCLASS()
class MMB_API UCUserWidget_StageSelect : public UUserWidget
{
	GENERATED_BODY()

	UCUserWidget_StageSelect(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> StageList;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> MapPreview;
	
};
