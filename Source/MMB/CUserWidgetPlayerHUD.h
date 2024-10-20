#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Listview.h"
#include "Components/TileView.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "CUserWidgetPlayerHUD.generated.h"

UCLASS()
class MMB_API UCUserWidgetPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UCUserWidgetPlayerHUD(const FObjectInitializer& ObjectInitializer);
	virtual void SetVisibility(ESlateVisibility InVisibility) override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCUserWidget_CircularProgressBar> CircularHPBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> EnemyHPBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> EnemyHPBar_BG;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> QuestList;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> QuickSlot_1_Tile;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> QuickSlot_2_Tile;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> QuickSlot_3_Tile;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuickSlot_1;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuickSlot_2;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuickSlot_3;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> DieUI;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> DieBG;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DieText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DieSubText;
// Battle Staff
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> BattleUIPanel;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCUserWIdget_BattleGauge> BruteGauge;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> BruteModeRoundUI;
	
// Rifle Staff
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> RifleUIPanel;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> RifleSelect;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> AimSpot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> AimSprite;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> AimCharge;

	void InitializeUI();
	void ShowDieUI(bool b);
	void Tick_DieUIAnim(float DeltaTime);
	bool GetContinueRevive() { return bContinueRevive; }

	FString GetItemDataOnQuickSlot(int32 QuickSlotNum);

	/*Changes All RifleStaff UI Visibility*/
	void SetAimVisibility(bool e);

	void SetQuickSlot1(class UCInventoryItemData* QuickItem);
	void SetQuickSlot2(class UCInventoryItemData* QuickItem);
	void SetQuickSlot3(class UCInventoryItemData* QuickItem);

	void SetEnemyRecentDamage(float Damage);
// Battle Staff UI
	void SetBattleVIsibility(bool e);
	void SetBruteMode(bool e);
	void SetBruteGauge(float Percent);
	void SetBruteCooldown(float Percent);
	void SetBruteCooldownParam(float NewMaxCooldown);
// Rifle Staff UI
	void SetAimSpriteColorOverlay(float Index);
	void AddAimSpriteColorOverlayIndex(float Delta);
	float GetAimSpriteColorOverlay() { return CurrAimSpriteColorIndex; }
	bool GetWeaponChangeReady() { return WeaponChangeReady; }
	void SetAimSpriteBlur(float NewBlur) { ToSetBlur = NewBlur; }
	void SetAimProgressBarPercent(float NewPercent);
	void SetRifleSelectSequence(FVector NewSequence);
	void SetRifleBullets(FVector NewBullets);
	void DoRifleSelectBarrelRoll();
private:
	
	virtual void NativeOnInitialized() override;

	bool IsBattleStaffUI;
// Battle Sprite
	float BruteGaugeCooldown;
	float BruteGaugeCooldownMax;

// Rifle Select Sprite
	static const FVector RifleColor;
	static const FVector MachineGunColor;
	static const FVector ShotGunColor;

	class UMaterialInstanceDynamic* RifleSelectMaterial;
	FVector GetRifleBulletTypeColor(int32 BulletType);
	int32 BarrelRollLeft;
	float CylinderAngle;
// Aim Sprite
	class UMaterialInstanceDynamic* AimSpriteMaterial;

	float AimSize;

	float ToSetBlur;
	float CurrBlur;

	float MaxCurrAimSpriteColorIndex;
	float CurrAimSpriteColorIndex;
	float ToSetAimSpriteColorIndex;
	bool WeaponChangeReady;
// Aim Sprite End
	bool bContinueRevive;
	float EnemyRecentDamage;
	bool bEraseEnemyRecentDamage;
	FTimerHandle RecentDamageTimerHandler;

	UFUNCTION()
	void OnClickQuickSlot1();
	UFUNCTION()
	void OnClickQuickSlot2();
	UFUNCTION()
	void OnClickQuickSlot3();


};
