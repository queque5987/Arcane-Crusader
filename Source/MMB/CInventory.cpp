// Fill out your copyright notice in the Description page of Project Settings.


#include "CInventory.h"
#include "CInventoryItemData.h"

UCInventory::UCInventory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	/*UUserWidget* Test = CreateWidget(this, UCInventoryItem::StaticClass(), TEXT("test Item"));
	UObject* TestWidget = Cast<UObject>(Test);
	ItemList->AddItem(TestWidget);*/
	//UE_LOG(LogTemp, Log, TEXT("ButtonAdd"));
	/*UCInventoryItemData* RawMeat = CreateDefaultSubobject<UCInventoryItemData>(TEXT("test"));
	UObject* T = Cast<UObject>(RawMeat);*/
	//UCInventoryItemData* RawMeat = NewObject<UCInventoryItemData>(this, UCInventoryItemData::StaticClass());
	/*RawMeat->SetItemIndex(0);
	RawMeat->SetItemCount(0);
	RawMeat->SetItemName(TEXT("Raw Meat"));
	RawMeat->SetIconTexture(TEXT("Texture2D'/Game/CraftResourcesIcons/Textures/Tex_meat_03.Tex_meat_03'"));*/
	//ItemList->AddItem(T);
}

void UCInventory::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);
	if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwningPlayer()->GetCharacter()))
	{
		PlayerGold->SetText(FText::FromString(FString::FromInt(PC->GetPlayerGold())));
	}
}
