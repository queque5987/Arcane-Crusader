// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "CQuestData.h"
#include "IWidgetInteract.h"
#include "CListedQuest.generated.h"

UCLASS()
class MMB_API UCListedQuest : public UUserWidget, public IUserObjectListEntry, public IIWidgetInteract
{
	GENERATED_BODY()

	UCListedQuest(const FObjectInitializer& ObjectInitializer);
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void SwitchPressed(bool Pressed) override;
	virtual bool GetbPressed() override { return bPressed; }

protected:
	bool bPressed;
	virtual void NativeOnInitialized() override;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> QuestName;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BtnQuest;

	UObject* QuestData;

	FSlateBrush SB_Normal;
	FSlateBrush SB_Pressed;

	TArray<const FSlateColor*> QuestState_BackGroundColorArr;
	UINT32 QuestState;
	//const FSlateBrush* SB_Pressed;
	//const FSlateBrush* SB_Pressed;

	UFUNCTION()
	void OnButtonClicked();

public:
	UObject* GetQuestData() { return QuestData; }
	void ResumeButtonStyle();
	UINT32 GetQuestState() { return QuestState; }
};
