#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "IWidgetInteract.h"
#include "CUserWidget_ListedStage.generated.h"

DECLARE_DELEGATE_OneParam(FOnStageSelected, FString);

UCLASS()
class MMB_API UCUserWidget_ListedStage : public UUserWidget, public IUserObjectListEntry, public IIWidgetInteract
{
	GENERATED_BODY()

	FString MapName;
	bool bPressed;
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void SwitchPressed(bool Pressed) override;
	virtual bool GetbPressed() override { return bPressed; }

	FOnStageSelected OnStageSelected;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StageButton;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> StageBG;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StageName;

	UFUNCTION()
	void OnButtonClicked();
	FString GetMapName() { return MapName; };
};
