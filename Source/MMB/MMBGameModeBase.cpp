// Copyright Epic Games, Inc. All Rights Reserved.


#include "MMBGameModeBase.h"
#include "CEthereal.h"
#include "CEntrance0.h"
#include "CWeapon.h"
#include "CStaff.h"
#include "CBattleStaff.h"

AMMBGameModeBase::AMMBGameModeBase()
{
	DefaultPawnClass = ACPlayerCharacter::StaticClass();
	PlayerControllerClass = ACPlayerController::StaticClass();

	/*ConstructorHelpers::FObjectFinder<UWorld> testlevelFinder(TEXT("/Game/TestLevel1.TestLevel1"));
	if (testlevelFinder.Succeeded())
	{
		LevelToLoad = testlevelFinder.Object;
	}*/
	PreLoadedTextures.SetNum(MAX_PRELOADED_TEXTURES_NUM);
	DropItemMaterialsRarity.SetNum(MAX_ITEM_RARITY_NUM);

	ConstructorHelpers::FObjectFinder<UTexture2D>StaffIconFinder(TEXT("/Game/Resources/staff.staff"));
	ConstructorHelpers::FObjectFinder<UTexture2D>BattleStaffIconFinder(TEXT("/Game/Resources/Textrue_BattleStaff.Textrue_BattleStaff"));
	ConstructorHelpers::FObjectFinder<UTexture2D>DroppedItemIconFinder(TEXT("/Game/Resources/Texture_DroppedItem.Texture_DroppedItem"));

	if (StaffIconFinder.Succeeded())		PreLoadedTextures[TEXTURE_STAFF]		= (StaffIconFinder.Object);
	if (BattleStaffIconFinder.Succeeded())	PreLoadedTextures[TEXTURE_BATTLESTAFF]	= (BattleStaffIconFinder.Object);
	if (DroppedItemIconFinder.Succeeded())	PreLoadedTextures[TEXTURE_DROPPEDITEM]	= (DroppedItemIconFinder.Object);

	ConstructorHelpers::FObjectFinder<UMaterialInstance> NormalMat(TEXT("/Game/Resources/Material/MI_Normal.MI_Normal"));
	ConstructorHelpers::FObjectFinder<UMaterialInstance> RareMat(TEXT("/Game/Resources/Material/MI_Rare.MI_Rare"));
	ConstructorHelpers::FObjectFinder<UMaterialInstance> EpicMat(TEXT("/Game/Resources/Material/MI_Epic.MI_Epic"));
	ConstructorHelpers::FObjectFinder<UMaterialInstance> LegendaryMat(TEXT("/Game/Resources/Material/MI_Legendary.MI_Legendary"));
	
	if (NormalMat.Succeeded())		DropItemMaterialsRarity[ITEM_NORMAL] = NormalMat.Object;
	if (RareMat.Succeeded())		DropItemMaterialsRarity[ITEM_RARE] = RareMat.Object;
	if (EpicMat.Succeeded())		DropItemMaterialsRarity[ITEM_EPIC] = EpicMat.Object;
	if (LegendaryMat.Succeeded())	DropItemMaterialsRarity[ITEM_LEGENDARY] = LegendaryMat.Object;

	FSoftObjectPath path = FSoftObjectPath("/Game/TestLevel1.TestLevel1");
	TSoftObjectPtr<UWorld> testlevel(path);
	LevelToLoad = testlevel;
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

	/*for (auto& NPC : NPCs)
	{
		ACStaticNPC* NPCt = Cast<ACStaticNPC>(NPC);
		if (IsValid(NPCt))
		{
			NPCt->Initialize();
		}
	}*/

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
