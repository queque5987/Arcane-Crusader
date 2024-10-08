// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "CStaticNPC.h"
#include "CButtonAction.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCButtonAction : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ButtonText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> NPCName;

	class ACStaticNPC* NPC;
	class ACClimbableRope* Rope;
	class ACJumpPoints* JumpPoints;
	int ButtonMode;
public:
	void SetNPC(class ACStaticNPC* e);
	class ACStaticNPC* GetNPC() { return NPC; }

	void SetRope(class ACClimbableRope* e);
	class ACClimbableRope* GetRope() { return Rope; }

	void SetJumpPoints(class ACJumpPoints* e);
	class ACJumpPoints* GetJumpPoints() { return JumpPoints; }

	void SetButtonMode(int e);
	int GetButtonMode() { return ButtonMode; }

	UFUNCTION()
	void OnButtonTriggered();
};
