// Fill out your copyright notice in the Description page of Project Settings.


#include "CSaveFileUI.h"
#include "CSaveGame.h"
#include "CGameInstance.h"
#include "IItemManager.h"
#include "MainUIGameMode.h"
#include "CInventoryItemData.h"

void UCSaveFileUI::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	SaveFile = Cast<UCSaveGame>(ListItemObject);
	if (SaveFile == nullptr) return;

	SaveSlotName->SetText(FText::FromString(SaveFile->SaveSlotName));
	PlayerGold->SetText(FText::FromString(FString::FromInt(SaveFile->SavedGold)));

	IIItemManager* ItemManager = Cast<IIItemManager>(GetWorld()->GetAuthGameMode());
	if (ItemManager == nullptr) return;

	UCInventoryItemData* ID = ItemManager->GetItem(SaveFile->SavedWeapon);
	if (ID != nullptr) Weapon->AddItem(ID);
	ID = ItemManager->GetItem(SaveFile->SavedArtifact);
	if (ID != nullptr) Artifact->AddItem(ID);
	ID = ItemManager->GetItem(SaveFile->SavedArmor);
	if (ID != nullptr) Armor->AddItem(ID);
}

void UCSaveFileUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SelectButton->OnReleased.AddDynamic(this, &UCSaveFileUI::OnButtonClicked);
}

void UCSaveFileUI::OnButtonClicked()
{
	if (SaveFile == nullptr) return;
	//AMainUIGameMode* GM = Cast<AMainUIGameMode>(GetWorld()->GetAuthGameMode());
	//if (GM == nullptr) return;
	UGameInstance* UGI = GetGameInstance();
	UCGameInstance* GI = Cast<UCGameInstance>(UGI);
	if (GI == nullptr) return;
	GI->SelectedSaveSlot = SaveFile->SaveIndex;

	//TSoftObjectPtr<UWorld> LoadedLevel(FSoftObjectPath(SaveFile->SavedLevel));
	FName LoadedLevel = SaveFile->SavedLevel;
	if (SaveFile->SavedLevel.IsNone())
	{
		//LoadedLevel = FSoftObjectPath("/Game/Resources/Levels/Startlevel.Startlevel");
		LoadedLevel = "Startlevel";
	}

	OnLoadingScreenSet.Broadcast(LoadedLevel);

	UGameplayStatics::OpenLevel(this, LoadedLevel);

	if (ACPlayerController* e = Cast<ACPlayerController>(GetOwningPlayer()))
	{
		e->MainUI->SetVisibility(ESlateVisibility::Hidden);
	}
}
