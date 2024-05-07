// Fill out your copyright notice in the Description page of Project Settings.


#include "CTeleportableMap.h"
#include "GameFramework/Character.h"

void UCTeleportableMap::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	MapData = Cast<UCTeleportableMapData>(ListItemObject);
	if (MapData != nullptr) MapName->SetText(FText::FromName(MapData->GetDestLevelName()));
}

void UCTeleportableMap::NativeOnInitialized()
{
	BtnMapPreview->OnClicked.AddDynamic(this, &UCTeleportableMap::OnButtonClicked);
}

void UCTeleportableMap::OnButtonClicked()
{
	if (MapData == nullptr) return;
	UE_LOG(LogTemp, Log, TEXT("Current Level : %s"), *GetWorld()->GetName());

	if (GetWorld()->GetName() == MapData->GetDestLevel()->GetMapName())
	{
		//Just Location
		UE_LOG(LogTemp, Log, TEXT("Teleporting to %s At %s"),
			*MapData->GetDestLevel()->GetMapName(),
			*MapData->GetDestLocation().ToString()
		);

		AController* ACC = GetOwningPlayer();
		if (ACC == nullptr) return;
		ACharacter* AC = ACC->GetCharacter();
		if (AC != nullptr) AC->SetActorLocation(MapData->GetDestLocation());
	}
	else
	{
		//Load Level
		//Move to Pos
	}

	
}
