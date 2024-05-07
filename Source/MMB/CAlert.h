// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "CAlert.generated.h"
UCLASS()
class MMB_API UCAlert : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> AlertMessage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> AlertWindow;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> AlertWindowBtn;

	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
public:
	void SetAlertMessage(FText e) { AlertMessage->SetText(e); }
	void SetWindowLocation(FVector2D e);
	FVector2D GetWindowLocation() { return AlertWindow->GetRenderTransform().Translation; }

	virtual void SetVisibility(ESlateVisibility InVisibility) override;

	UFUNCTION()
	void OnClickedEvent() { SetVisibility(ESlateVisibility::Hidden); }
private:
	float DestructCount;
};
