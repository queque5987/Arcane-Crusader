// Copyright Epic Games, Inc. All Rights Reserved.


#include "MMBGameModeBase.h"
#include "CEthereal.h"
#include "CEntrance0.h"
#include "CWeapon.h"
#include "CStaff.h"
#include "CBattleStaff.h"
#include "Modules/ModuleManager.h"
#include "CInventoryItemData.h"
#include "CGameInstance.h"
#include "Sound/SoundBase.h"
//#include "CEnemyCharacter.h"
#include "FMonsterConfigure.h"
#include "AssetRegistry/AssetRegistryModule.h"

AMMBGameModeBase::AMMBGameModeBase()
{
	DefaultPawnClass = ACPlayerCharacter::StaticClass();
	PlayerControllerClass = ACPlayerController::StaticClass();
	//PlayerStateClass = ACPlayerState::StaticClass();

	PreLoadedTextures.SetNum(MAX_PRELOADED_TEXTURES_NUM);
	DropItemMaterialsRarity.SetNum(MAX_ITEM_RARITY_NUM);
	//SlateBrushArr.SetNum(MAX_SB_NUM);

	ConstructorHelpers::FObjectFinder<UTexture2D>StaffIconFinder(TEXT("/Game/Resources/staff"));
	ConstructorHelpers::FObjectFinder<UTexture2D>BattleStaffIconFinder(TEXT("/Game/Resources/Textrue_BattleStaff"));
	ConstructorHelpers::FObjectFinder<UTexture2D>DroppedItemIconFinder(TEXT("/Game/Resources/Texture_DroppedItem"));

	if (StaffIconFinder.Succeeded())		PreLoadedTextures[TEXTURE_STAFF]		= (StaffIconFinder.Object);
	if (BattleStaffIconFinder.Succeeded())	PreLoadedTextures[TEXTURE_BATTLESTAFF]	= (BattleStaffIconFinder.Object);
	if (DroppedItemIconFinder.Succeeded())	PreLoadedTextures[TEXTURE_DROPPEDITEM]	= (DroppedItemIconFinder.Object);

	DefaultIconDroppedItem = DroppedItemIconFinder.Object;

	ConstructorHelpers::FObjectFinder<UMaterialInstance> NormalMat(TEXT("/Game/Resources/Material/MI_Normal"));
	ConstructorHelpers::FObjectFinder<UMaterialInstance> RareMat(TEXT("/Game/Resources/Material/MI_Rare"));
	ConstructorHelpers::FObjectFinder<UMaterialInstance> EpicMat(TEXT("/Game/Resources/Material/MI_Epic"));
	ConstructorHelpers::FObjectFinder<UMaterialInstance> LegendaryMat(TEXT("/Game/Resources/Material/MI_Legendary"));
	
	if (NormalMat.Succeeded())		DropItemMaterialsRarity[ITEM_NORMAL] = NormalMat.Object;
	if (RareMat.Succeeded())		DropItemMaterialsRarity[ITEM_RARE] = RareMat.Object;
	if (EpicMat.Succeeded())		DropItemMaterialsRarity[ITEM_EPIC] = EpicMat.Object;
	if (LegendaryMat.Succeeded())	DropItemMaterialsRarity[ITEM_LEGENDARY] = LegendaryMat.Object;

	//ConstructorHelpers::FObjectFinder<USlateBrushAsset>SB_DesertFinder(TEXT("/Game/Resources/Image/SB_Desert.SB_Desert"));
	//if (SB_DesertFinder.Succeeded())	SlateBrushArr[SB_DESERT] = SB_DesertFinder.Object;

	ConstructorHelpers::FObjectFinder<UDataTable> ItemTableFinder(TEXT("/Game/Resources/DataTables/DT_ItemTable"));
	if (ItemTableFinder.Succeeded())	ItemTable = ItemTableFinder.Object;
	ConstructorHelpers::FObjectFinder<UDataTable> MonsterTableFinder(TEXT("/Game/Resources/DataTables/MonsterConfig/DT_MonsterConfig"));
	if (MonsterTableFinder.Succeeded())	MonsterConfigTable = MonsterTableFinder.Object;

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

	TArray<FAssetData> AssetData_BGM;
	FARFilter Filter_BGM;
	Filter_BGM.PackagePaths.Add("/Game/Resources/Sound/BGM/");
	AssetRegistryModule.Get().GetAssets(Filter_BGM, AssetData_BGM);
	USoundBase* tempBGM;
	for (FAssetData Dat : AssetData_BGM)
	{
		tempBGM = Cast<USoundBase>(Dat.GetAsset());
		if (tempBGM == nullptr) continue;
		PreBGMMap.Add(Dat.AssetName.ToString(), tempBGM);
	}

	ItemGetCounter = 0;
}

void AMMBGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("Gamemode BeginPlay"));
	//FVector location = FVector(7145.f, 495.f, 100.f);
	//GetWorld()->SpawnActor<ACEthereal>(ACEthereal::StaticClass, location);
	//GetWorld()->SpawnActor<ACEthereal>(ACEthereal::StaticClass(), location, FRotator::ZeroRotator);

	TArray<AActor*> Entrances;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACStaticNPC::StaticClass(), Entrances);

	GameInstance = Cast<UCGameInstance>(GetGameInstance());

	UE_LOG(LogTemp, Log, TEXT("Loaded Map : %s"), *GetWorld()->GetName());
	if (PreBGMMap.Contains(GetWorld()->GetName()))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), PreBGMMap[GetWorld()->GetName()]);
	}
	/*for (auto& NPC : NPCs)
	{
		ACStaticNPC* NPCt = Cast<ACStaticNPC>(NPC);
		if (IsValid(NPCt))
		{
			NPCt->Initialize();
		}
	}*/

	ItemGetCounter = 0;
}

UTexture2D* AMMBGameModeBase::GetPreLoadedTexture(int32 e)
{
	return PreLoadedTextures.Num() > e? PreLoadedTextures[e] : nullptr;
}

UClass* AMMBGameModeBase::GetItemClass(int32 e)
{
	switch(e)
	{
	case(-1):	return nullptr;
	case(0):	return ACStaff::StaticClass();
	case(1):	return ACBattleStaff::StaticClass();
	default:	return nullptr;
	}
}

UMaterialInstance* AMMBGameModeBase::GetDropItemMaterial(int32 Rarity)
{
	return DropItemMaterialsRarity.Num() > Rarity? DropItemMaterialsRarity[Rarity] : nullptr;
}

UTexture2D* AMMBGameModeBase::IconGetter(FString IconAssetName)
{
	//return PreLoadedTextureMap.Find(IconAssetName);
	return PreLoadedTextureMap.Contains(IconAssetName) ? PreLoadedTextureMap[IconAssetName] : DefaultIconDroppedItem;
}

UCInventoryItemData* AMMBGameModeBase::GetItem(FName ItemRowName, int Count)
{
	FItemTableRow* Row = ItemTable->FindRow<FItemTableRow>(ItemRowName, FString(""));

	UE_LOG(LogTemp, Log, TEXT("Loading Item : %s"), *ItemRowName.ToString())
	if (Row == nullptr) return nullptr;
	UCInventoryItemData* D = NewObject<UCInventoryItemData>(GetWorld(), UCInventoryItemData::StaticClass(), *(Row->ItemName + FString::FromInt(ItemGetCounter++)));
	D->SetDT_RowName(ItemRowName);
	D->SetIconTexture(Row->IconTexture);
	D->SetItemClass(StaticLoadClass(UObject::StaticClass(), nullptr, *Row->ItemClass));
	D->SetItemCount(Count);
	D->SetstrName(Row->ItemName);
	D->SetPrice(Row->ItemPrice);
	D->SetItemType(Row->ItemType);
	D->SetRarity(Row->Rarity);
	D->SetItemDetail(FText::FromString(Row->ItemDetail));
	D->SetItemStats(
		Row->AttackDamage,
		Row->Defence,
		Row->AttackSpeed,
		Row->Potion_HealPoint
	);
	D->SetBulletType(Row->BulletType);
	
	return D;
}

void AMMBGameModeBase::GetMonsterConfigure(FName RowName, UFMonsterConfigure& RtnConfig)
{
	UE_LOG(LogTemp, Log, TEXT("Monster Config RowName : %s"), *RowName.ToString());

	if (MonsterConfigTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MonsterConfigTable Not Found"));
		return;
	}
	FMonsterConfigTableRow* Row = MonsterConfigTable->FindRow<FMonsterConfigTableRow>(RowName, FString(""));
	if (Row == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Monster Config Can Not Found"));
		return;
	}
	FString DataTableAddress = Row->DropTable;
	//DataTableAddress = "/Game/Resources/DataTables/DropTable/" + DataTableAddress;
	UDataTable* DropTable = LoadObject<UDataTable>(nullptr, *DataTableAddress);
	if (DropTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Monster DropTable Can Not Found"));
	}

	RtnConfig.SetProperties(
		StaticLoadClass(UObject::StaticClass(), nullptr, *Row->MonsterClass),
		DropTable,
		Row->MonsterHP,
		Row->MonsterHP,
		Row->MonsterDamage,
		Row->MaxWalkSpeed,
		Row->FlyAcc,
		Row->VirticalAcc
	);

	//RtnConfig._MonsterClass = StaticLoadClass(UObject::StaticClass(), nullptr, *Row->MonsterClass);
	//RtnConfig._AttackDamage = Row->MonsterDamage;
	//RtnConfig._FlyAcc = Row->FlyAcc;
	//RtnConfig._HP = Row->MonsterHP;
	//RtnConfig._MaxHP = Row->MonsterHP;
	//RtnConfig._MaxWalkSpeed = Row->MaxWalkSpeed;
	//RtnConfig._VirticalAcc = Row->VirticalAcc;
}

//FSlateBrush* AMMBGameModeBase::GetSlateBrush(int32 e)
//{
//	return SlateBrushArr.IsValidIndex(e) ? &(SlateBrushArr[e]->Brush) : nullptr;
//}
