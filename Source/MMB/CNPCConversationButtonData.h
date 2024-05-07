// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/NoExportTypes.h"
#include "PCH.h"
#include "CNPCConversationButtonData.generated.h"

DECLARE_DELEGATE(FClickEvent);

UCLASS()
class MMB_API UCNPCConversationButtonData : public UObject
{
	GENERATED_BODY()
	UCNPCConversationButtonData(const FObjectInitializer& ObjectInitializer);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FName BtnName;
	FSimpleDelegate* ClickDele;
	//FClickEvent ClickEvent;

	//typedef void (UCNPCConversation::*CLICK_FUNC)();
	//CLICK_FUNC* ClickEvent;
public:
	void SetBtnName(FName e) { BtnName = e; }
	FName GetBtnName() { return BtnName; }
	void SetClickDele(FSimpleDelegate* e) { ClickDele = e; }
	FSimpleDelegate* GetClickDele() { return ClickDele; }
	//void SetClickEvent(CLICK_FUNC e) { ClickEvent = &e; }
	//CLICK_FUNC* GetClickEvent() { return ClickEvent; }
	//typedef void (UUserWidget::* CallBackFunction)();
	//CallBackFunction* PressedFunctionPtr;
//
//public:
//	void SetClickPtr(CLICK_FUNC* e) { PressedEvent = e; }
//	CLICK_FUNC GetClickPtr() { return *PressedEvent; }
};
