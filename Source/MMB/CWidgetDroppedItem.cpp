#include "CWidgetDroppedItem.h"
#include "Materials/MaterialInstanceDynamic.h"

void UCWidgetDroppedItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (UCInventoryItemData* D = Cast<UCInventoryItemData>(ListItemObject))
	{
		ItemName->SetText(FText::FromString(D->GetstrName()));
		if (AMMBGameModeBase* GM = Cast<AMMBGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			UTexture2D* T = GM->IconGetter(D->GetIconTexture());
			ItemImage->SetBrushFromTexture(T);
		}
		Rarity = D->GetRarity();
	}

	if (ItemGlowingSpriteMaterial != nullptr)
	{
		FVector RarityColor;
		switch (Rarity)
		{
		case(ITEM_RARE):
			RarityColor = RGB_RARE;
			break;
		case(ITEM_EPIC):
			RarityColor = RGB_EPIC;
			break;
		case(ITEM_LEGENDARY):
			RarityColor = RGB_LEGENDARY;
			break;
		case(ITEM_NORMAL):
		default:
			RarityColor = RGB_NORMAL;
			break;
		}
		ItemGlowingSpriteMaterial->SetVectorParameterValue("TextureColorOverride", RarityColor);
		UE_LOG(LogTemp, Log, TEXT("TextureColorOverride %s Set %s"), *ItemName->GetText().ToString(), *RarityColor.ToString());
	}
}

void UCWidgetDroppedItem::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CurrentTextureIndex = 0.f;

	if (ItemGlowingSprite != nullptr) ItemGlowingSpriteMaterial = ItemGlowingSprite->GetDynamicMaterial();
	if (ItemGlowingSpriteMaterial == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ItemGlowingSpriteMaterial Not Found"));
	}

}

void UCWidgetDroppedItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (ItemGlowingSpriteMaterial != nullptr)
	{
		ItemGlowingSpriteMaterial->SetScalarParameterValue("TextureIndex", CurrentTextureIndex);

		CurrentTextureIndex += InDeltaTime * 10.f;
	}

}
