// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "PCH.h"
#include "CNPCConversationButton.generated.h"

UCLASS()
class MMB_API UCNPCConversationButton : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Btn;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> BtnText;

	FSimpleDelegate* ClickDele;

	UFUNCTION()
	void OnClicked();

	//typedef void (UCNPCConversation::* CLICK_FUNC)();
	//CLICK_FUNC* Clickevent;
private:
	UObject* ButtonData;
};
