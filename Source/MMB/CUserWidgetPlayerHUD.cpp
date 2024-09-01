#include "CUserWidgetPlayerHUD.h"
#include "IPlayerUIController.h"
#include "CInventoryItemData.h"
#include "CUserWidget_CircularProgressBar.h"
#include "CUserWIdget_BattleGauge.h"
#include "Materials/MaterialInstanceDynamic.h"

const FVector UCUserWidgetPlayerHUD::RifleColor(FVector(1.f, 0.f, 0.f));
const FVector UCUserWidgetPlayerHUD::MachineGunColor(FVector(1.f, 0.931461f, 0.078125f));
const FVector UCUserWidgetPlayerHUD::ShotGunColor(FVector(0.002934f, 1.f, 0.039423f));

UCUserWidgetPlayerHUD::UCUserWidgetPlayerHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	InitializeUI();
	EnemyRecentDamage = 0.f;
	CurrAimSpriteColorIndex = 0.f;
	MaxCurrAimSpriteColorIndex = 3.f;
	WeaponChangeReady = true;
	AimSize = 1.f;
	CylinderAngle = 0.f;
	BarrelRollLeft = 0;
	BruteGaugeCooldown = 0.f;
	BruteGaugeCooldownMax = 0.f;
}

void UCUserWidgetPlayerHUD::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);
	if (InVisibility == ESlateVisibility::Visible) InitializeUI();
}

void UCUserWidgetPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (EnemyRecentDamage > 0.f)
	{
		if (bEraseEnemyRecentDamage)
		{
			EnemyRecentDamage -= InDeltaTime * 0.2f;
			EnemyRecentDamage = EnemyRecentDamage < 0.f ? 0.f : EnemyRecentDamage;
		}
		EnemyHPBar_BG->SetPercent(EnemyHPBar->GetPercent() + EnemyRecentDamage);
	}

	// Tab Triggerabliltiy
	if (!WeaponChangeReady)
	{
		if (IsBattleStaffUI) //BattleStaffChangeCheck
		{
			UE_LOG(LogTemp, Log, TEXT("BruteGaugeCooldown : %f , BruteGaugeCooldownMax : %f"), BruteGaugeCooldown, BruteGaugeCooldownMax);
			if (BruteGaugeCooldownMax <= 0.f) return;

			if (BruteGaugeCooldown < BruteGaugeCooldownMax) BruteGaugeCooldown += InDeltaTime;
			if (BruteGaugeCooldown >= BruteGaugeCooldownMax)
			{
				BruteGaugeCooldown = BruteGaugeCooldownMax;
				WeaponChangeReady = true;
			}

			BruteGauge->SetCooldown(BruteGaugeCooldown / BruteGaugeCooldownMax);
		}
		else //RifleStaffChangeCheck
		{
			float Target = ToSetAimSpriteColorIndex;
			if (ToSetAimSpriteColorIndex == 0.f)
			{
				Target = 3.f;
			}
			CurrAimSpriteColorIndex += InDeltaTime * 20.f;

			if (CurrAimSpriteColorIndex >= Target)
			{
				CurrAimSpriteColorIndex = ToSetAimSpriteColorIndex;
				WeaponChangeReady = true;
			}
			AimSpriteMaterial->SetScalarParameterValue("BulletType", CurrAimSpriteColorIndex);
		}
	}

	if (ToSetBlur != CurrBlur)
	{
		CurrBlur += ToSetBlur != 0.f ? InDeltaTime * 20.f : -InDeltaTime * 12.f;
		if ((ToSetBlur != 0.f && CurrBlur > ToSetBlur) ||
			(ToSetBlur == 0.f && CurrBlur < ToSetBlur))
		{
			CurrBlur = ToSetBlur;
		}
		AimSpriteMaterial->SetScalarParameterValue("Blur", CurrBlur);
		//UE_LOG(LogTemp, Log, TEXT("AimSize : %f"), AimSize * (1 + ((10.f - CurrBlur) / 10.f) * 0.5f));
		AimSpriteMaterial->SetScalarParameterValue("AimSize", AimSize * (1 + ((10.f - CurrBlur) / 10.f) * 0.5f));
	}

	if (BarrelRollLeft > 0)
	{
		if (RifleSelectMaterial != nullptr)
		{
			CylinderAngle += BarrelRollLeft % 2 > 0 ? (InDeltaTime * 1.3f) : -(InDeltaTime * 3.5f);

			if (CylinderAngle < -0.5f)
			{
				CylinderAngle = -0.5f;
				BarrelRollLeft--;
			}
			else if (CylinderAngle > 0.f)
			{
				CylinderAngle = 0.f;
				BarrelRollLeft--;
			}
			UE_LOG(LogTemp, Log, TEXT("CylinderAngle : %f"), CylinderAngle);
			RifleSelectMaterial->SetScalarParameterValue("Clock", CylinderAngle);
		}
	}
}

void UCUserWidgetPlayerHUD::InitializeUI()
{
	bContinueRevive = false;

	if (DieUI == nullptr) return;
	DieUI->SetVisibility(ESlateVisibility::Hidden);

	FLinearColor Color = FLinearColor(1.f, 0.f, 0.f, 0.1f);
	DieBG->SetColorAndOpacity(Color);
	//DieBG->GetColorAndOpacity().A = 0.1f;

	//DieText->GetFont().LetterSpacing = 0.f;
	FSlateFontInfo Font = DieText->GetFont();
	Font.LetterSpacing = 0.f;
	DieText->SetFont(Font);

	DieSubText->SetVisibility(ESlateVisibility::Hidden);
	DieSubText->SetRenderOpacity(0.0f);

	QuickSlot_1->OnPressed.AddDynamic(this, &UCUserWidgetPlayerHUD::OnClickQuickSlot1);
	QuickSlot_2->OnPressed.AddDynamic(this, &UCUserWidgetPlayerHUD::OnClickQuickSlot2);
	QuickSlot_3->OnPressed.AddDynamic(this, &UCUserWidgetPlayerHUD::OnClickQuickSlot3);

	RifleUIPanel->SetVisibility(ESlateVisibility::Hidden);
	BruteGauge->SetVisibility(ESlateVisibility::Hidden);
}

void UCUserWidgetPlayerHUD::ShowDieUI(bool b)
{
	DieUI->SetVisibility(b ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	if (!b) InitializeUI();
}

void UCUserWidgetPlayerHUD::Tick_DieUIAnim(float DeltaTime)
{
	if (DieBG->GetColorAndOpacity().A <= 0.3f)
	{
		FLinearColor Color = DieBG->GetColorAndOpacity();
		Color.A += 0.05 * DeltaTime;
		DieBG->SetColorAndOpacity(Color);
	}
	if (DieText->GetFont().LetterSpacing <= 1200.f)
	{
		FSlateFontInfo Font = DieText->GetFont();
		Font.LetterSpacing += 300.f * DeltaTime;
		DieText->SetFont(Font);
	}
	if (DieText->GetFont().LetterSpacing > 1000.f)
	{
		if (DieSubText->GetVisibility() == ESlateVisibility::Hidden) DieSubText->SetVisibility(ESlateVisibility::Visible);
		float DieSubTextOpacity = DieSubText->GetRenderOpacity();
		if (DieSubTextOpacity >= 1.f) return;
		if (!bContinueRevive && DieSubTextOpacity >= 0.6f) bContinueRevive = true;
		DieSubText->SetRenderOpacity(DieSubTextOpacity += 0.35f * DeltaTime);
	}
}

void UCUserWidgetPlayerHUD::OnClickQuickSlot1()
{
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController == nullptr) return;

	UCInventoryItemData* QuickSlot1Item = UIController->GetQuickSlot();
	
	QuickSlot_1_Tile->ClearListItems();
	if (QuickSlot1Item != nullptr) QuickSlot_1_Tile->AddItem(QuickSlot1Item);
}

void UCUserWidgetPlayerHUD::OnClickQuickSlot2()
{
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController == nullptr) return;

	UCInventoryItemData* QuickSlot2Item = UIController->GetQuickSlot();
	
	QuickSlot_2_Tile->ClearListItems();
	if (QuickSlot2Item != nullptr) QuickSlot_2_Tile->AddItem(QuickSlot2Item);
}

void UCUserWidgetPlayerHUD::OnClickQuickSlot3()
{
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController == nullptr) return;

	UCInventoryItemData* QuickSlot3Item = UIController->GetQuickSlot();
	
	QuickSlot_3_Tile->ClearListItems();
	if (QuickSlot3Item != nullptr) QuickSlot_3_Tile->AddItem(QuickSlot3Item);
}

FString UCUserWidgetPlayerHUD::GetItemDataOnQuickSlot(int32 QuickSlotNum)
{
	//IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	//if (UIController == nullptr) return "";

	UCInventoryItemData* tempID = nullptr;
	switch (QuickSlotNum)
	{
	case(1):
		tempID = Cast<UCInventoryItemData>(QuickSlot_1_Tile->GetItemAt(0));
		break;
	case(2):
		tempID = Cast<UCInventoryItemData>(QuickSlot_2_Tile->GetItemAt(0));
		break;
	case(3):
		tempID = Cast<UCInventoryItemData>(QuickSlot_3_Tile->GetItemAt(0));
		break;
	default:
		break;
	}
	if (tempID == nullptr) return "";
	return tempID->GetstrName();
}

void UCUserWidgetPlayerHUD::SetAimVisibility(bool e)
{
	if (RifleUIPanel == nullptr) return;
	RifleUIPanel->SetVisibility(e ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
	IsBattleStaffUI = !e;
	if (e) BruteGaugeCooldownMax = 0.f;
}

void UCUserWidgetPlayerHUD::SetQuickSlot1(UCInventoryItemData* QuickItem)
{
	QuickSlot_1_Tile->ClearListItems();
	QuickSlot_1_Tile->AddItem(QuickItem);
}

void UCUserWidgetPlayerHUD::SetQuickSlot2(UCInventoryItemData* QuickItem)
{
	QuickSlot_2_Tile->ClearListItems();
	QuickSlot_2_Tile->AddItem(QuickItem);
}

void UCUserWidgetPlayerHUD::SetQuickSlot3(UCInventoryItemData* QuickItem)
{
	QuickSlot_3_Tile->ClearListItems();
	QuickSlot_3_Tile->AddItem(QuickItem);
}

void UCUserWidgetPlayerHUD::SetEnemyRecentDamage(float Damage)
{
	if (EnemyRecentDamage < 0.f) EnemyRecentDamage = 0.f;
	EnemyRecentDamage += Damage;
	UE_LOG(LogTemp, Log, TEXT("UCUserWidgetPlayerHUD AddRecentDamage : %f"), Damage);
	UE_LOG(LogTemp, Log, TEXT("UCUserWidgetPlayerHUD RecentDamageSum : %f"), EnemyRecentDamage);
	bEraseEnemyRecentDamage = false;
	GetWorld()->GetTimerManager().ClearTimer(RecentDamageTimerHandler);
	GetWorld()->GetTimerManager().SetTimer(RecentDamageTimerHandler, FTimerDelegate::CreateLambda([&] {
		bEraseEnemyRecentDamage = true;
		}), 1.f, false
	);
}

void UCUserWidgetPlayerHUD::SetBattleVIsibility(bool e)
{
	if (BruteGauge == nullptr) return;
	BruteGauge->SetVisibility(e ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
	IsBattleStaffUI = e;
}

void UCUserWidgetPlayerHUD::SetBruteMode(bool e)
{
	BruteGauge->SetBruteMode(e);
}

void UCUserWidgetPlayerHUD::SetBruteGauge(float Percent)
{
	BruteGauge->SetProgress(Percent);
}

void UCUserWidgetPlayerHUD::SetBruteCooldown(float Percent)
{
	BruteGauge->SetCooldown(Percent);
}

void UCUserWidgetPlayerHUD::SetBruteCooldownParam(float NewMaxCooldown)
{
	BruteGaugeCooldownMax = NewMaxCooldown;
}

void UCUserWidgetPlayerHUD::SetAimSpriteColorOverlay(float Index)
{
	if (!WeaponChangeReady) return;
	WeaponChangeReady = false;
	if (Index < 0) BruteGaugeCooldown = 0.f;
	ToSetAimSpriteColorIndex = Index;
	return;
}

void UCUserWidgetPlayerHUD::AddAimSpriteColorOverlayIndex(float Delta)
{
	float NewAinSpriteColorIndex = CurrAimSpriteColorIndex + Delta;
	
	if (FMath::Floor(NewAinSpriteColorIndex) != FMath::Floor(CurrAimSpriteColorIndex))
	{
		CurrAimSpriteColorIndex = FMath::Floor(NewAinSpriteColorIndex);
	}
	else
	{
		CurrAimSpriteColorIndex = NewAinSpriteColorIndex;
	}

	if (NewAinSpriteColorIndex >= MaxCurrAimSpriteColorIndex) CurrAimSpriteColorIndex = 0.f;
}

void UCUserWidgetPlayerHUD::SetAimProgressBarPercent(float NewPercent)
{
	if (AimSprite == nullptr) return;
	AimSpriteMaterial->SetScalarParameterValue("Progress", NewPercent);
}

void UCUserWidgetPlayerHUD::SetRifleSelectSequence(FVector NewSequence)
{
	if (RifleSelectMaterial == nullptr) return;
	RifleSelectMaterial->SetVectorParameterValue("WeaponShadow", NewSequence);
	RifleSelectMaterial->SetVectorParameterValue("OverlayColor0", GetRifleBulletTypeColor(NewSequence.X));
	RifleSelectMaterial->SetVectorParameterValue("OverlayColor1", GetRifleBulletTypeColor(NewSequence.Y));
	RifleSelectMaterial->SetVectorParameterValue("OverlayColor2", GetRifleBulletTypeColor(NewSequence.Z));
}

void UCUserWidgetPlayerHUD::SetRifleBullets(FVector NewBullets)
{
	if (RifleSelectMaterial == nullptr) return;
	RifleSelectMaterial->SetVectorParameterValue("WeaponBullet", NewBullets);
}

void UCUserWidgetPlayerHUD::DoRifleSelectBarrelRoll()
{
	if (BarrelRollLeft > 0) return;
	BarrelRollLeft += 2;
}

void UCUserWidgetPlayerHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (AimSprite != nullptr) AimSpriteMaterial = AimSprite->GetDynamicMaterial();
	else UE_LOG(LogTemp, Error, TEXT("AimSprite Not Found"));

	if (RifleSelect != nullptr) RifleSelectMaterial = RifleSelect->GetDynamicMaterial();
	else UE_LOG(LogTemp, Error, TEXT("RifleSelect Not Found"));
}

FVector UCUserWidgetPlayerHUD::GetRifleBulletTypeColor(int32 BulletType)
{
	switch (BulletType)
	{
	case(0):
		return RifleColor;
	case(1):
		return ShotGunColor;
	case(2):
	default:
		return MachineGunColor;
	}
	return FVector::ZeroVector;
}
