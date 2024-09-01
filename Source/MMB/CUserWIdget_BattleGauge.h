#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "CUserWIdget_BattleGauge.generated.h"

UCLASS()
class MMB_API UCUserWIdget_BattleGauge : public UUserWidget
{
	GENERATED_BODY()
	
	UCUserWIdget_BattleGauge(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> StateOrb;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ProgressBar;

	class UMaterialInstanceDynamic* M_StateOrb;
	class UMaterialInstanceDynamic* M_ProgressBar;

public:
	void SetBruteMode(bool e);
	void SetProgress(float Percent);
	void SetCooldown(float Percent);
};
