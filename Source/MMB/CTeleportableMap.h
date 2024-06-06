// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "IWidgetInteract.h"
#include "CTeleportableMapData.h"
#include "CTeleportableMap.generated.h"

UCLASS()
class MMB_API UCTeleportableMap : public UUserWidget, public IUserObjectListEntry, public IIWidgetInteract
{
	GENERATED_BODY()
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void SwitchPressed(bool Pressed) override;
	virtual bool GetbPressed() override;

	virtual void NativeOnInitialized() override;
protected:
	class UCTeleportableMapData* MapData;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MapName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnMapPreview;

	UFUNCTION(BlueprintCallable)
	void OnButtonClicked();

	const FSlateBrush* SB_Normal;
	const FSlateBrush* SB_Pressed;
	bool bPressed;
};
