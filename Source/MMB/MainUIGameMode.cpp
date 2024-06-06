// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUIGameMode.h"
#include "CMainUIPawn.h"
#include "CustomDataTables.h"
#include "CInventoryItemData.h"
#include "CGameInstance.h"
#include "AssetRegistry/AssetRegistryModule.h"

AMainUIGameMode::AMainUIGameMode()
{
	DefaultPawnClass = ACMainUIPawn::StaticClass();
	PlayerControllerClass = ACPlayerController::StaticClass();

	FSoftObjectPath path = FSoftObjectPath("/Game/Resources/Levels/Startlevel.Startlevel");
	TSoftObjectPtr<UWorld> testlevel(path);
	LevelToLoad = testlevel;


	ConstructorHelpers::FObjectFinder<UDataTable> ItemTableFinder(TEXT("/Game/Resources/DataTables/DT_ItemTable"));
	if (ItemTableFinder.Succeeded())	ItemTable = ItemTableFinder.Object;


	ConstructorHelpers::FObjectFinder<UTexture2D>DroppedItemIconFinder(TEXT("/Game/Resources/Texture_DroppedItem"));

	if (DroppedItemIconFinder.Succeeded()) DefaultIconDroppedItem = DroppedItemIconFinder.Object;

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	FARFilter Filter;
	Filter.PackagePaths.Add("/Game/CraftResourcesIcons/Textures/");
	AssetRegistryModule.Get().GetAssets(Filter, AssetData);
	UTexture2D* tempTexture;
	for (FAssetData Dat : AssetData)
	{
		tempTexture = Cast<UTexture2D>(Dat.GetAsset());
		if (tempTexture == nullptr) continue;
		PreLoadedTextureMap.Add(Dat.AssetName.ToString(), tempTexture);
	}
}

void AMainUIGameMode::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UCGameInstance>(GetGameInstance());
}

UTexture2D* AMainUIGameMode::IconGetter(FString IconAssetName)
{
	return PreLoadedTextureMap.Contains(IconAssetName) ? PreLoadedTextureMap[IconAssetName] : DefaultIconDroppedItem;
}

UCInventoryItemData* AMainUIGameMode::GetItem(FName ItemRowName, int Count)
{
	FItemTableRow* Row = ItemTable->FindRow<FItemTableRow>(ItemRowName, FString(""));

	if (Row == nullptr) return nullptr;

	UCInventoryItemData* D = NewObject<UCInventoryItemData>(GetWorld(), UCInventoryItemData::StaticClass(), *(Row->ItemName + FString::FromInt(Count)));
	D->SetDT_RowName(ItemRowName);
	D->SetIconTexture(Row->IconTexture);
	D->SetItemClass(StaticLoadClass(UObject::StaticClass(), nullptr, *Row->ItemClass));
	D->SetItemCount(Count);
	D->SetstrName(Row->ItemName);
	//D->SetAttackDamage(Row->AttackDamage);
	D->SetPrice(Row->ItemPrice);
	D->SetItemType(Row->ItemType);
	D->SetRarity(Row->Rarity);
	D->SetItemStats(
		Row->AttackDamage,
		Row->Defence,
		Row->AttackSpeed
	);

	return D;
}

//void AMainUIGameMode::BeginPlay()
//{
//	/*MainUI = Cast<UCMainUI>(CreateWidget<UUserWidget>(this, UCMainUI::StaticClass()));
//	if (IsValid(MainUI))
//	{
//		MainUI->AddToViewport();
//		MainUI->SetVisibility(ESlateVisibility::Hidden);
//	}*/
//
//}