// Fill out your copyright notice in the Description page of Project Settings.


#include "CInventoryItem.h"
#include "CPlayerCharacter.h"
#include "CWeapon.h"
#include "IWeapon.h"
#include "GenericPlatform/GenericPlatformTime.h"

void UCInventoryItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	ItemData = ListItemObject;
	ItemName->SetText(FText::FromString(TEXT("ItemName")));

	if (UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData))
	{
		if (AMMBGameModeBase* GM = Cast<AMMBGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			UTexture2D* T = GM->GetPreLoadedTexture(ID->GetIconTexture());
			ItemImage->SetBrushFromTexture(T);
		}

		ItemName->SetText(FText::FromString(ID->GetstrName()));
	}
}

void UCInventoryItem::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ItemButton->OnClicked.AddDynamic(this, &UCInventoryItem::OnButtonClicked);
	ClickedSec = 0.f;
}

void UCInventoryItem::OnButtonClicked()
{
	if (FPlatformTime::Seconds() - ClickedSec <= 0.35f)
	{
		ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(this->GetOwningPlayer()->GetCharacter());
		//UE_LOG(LogTemp, Log, TEXT("Double Clicked %s"), *PC->GetName());
		UCInventoryItemData* ID = Cast<UCInventoryItemData>(ItemData);

		if (IsValid(ID))
		{
			//if (ID->GetItemClass()->GetSuperClass() == ACWeapon::StaticClass())
			//{
			AActor* spawnedActor = GetWorld()->SpawnActor<AActor>(ID->GetItemClass(), PC->GetActorLocation(), FRotator::ZeroRotator);
			
			//ACWeapon* isWeapon = Cast<ACWeapon>(spawnedActor);

			//if (IsValid(isWeapon))
			if (IIWeapon* isWeapon = Cast<IIWeapon>(spawnedActor))
			{
				isWeapon->SetIsEquiped(true);

				isWeapon->SetWeaponName(FName(ID->GetstrName()));
				isWeapon->SetAttackDamage(ID->GetAttackDamage());

				//SetActorRelativeRotation(FRotator::ZeroRotator);
				PC->Equip(*spawnedActor);
				ACPlayerController* PCC = Cast<ACPlayerController>(PC->GetController());
				if (IsValid(PCC))
				{
					PCC->ItemInventory->ItemList->RemoveItem(ItemData);
				}
			}
			//}
			//else if (ID->GetItemClass() == nullptr)
			//{

			//}
		}
	}
	ClickedSec = FPlatformTime::Seconds();
	//int64 Milliseconds = static_cast<int64>(Seconds * 1000);
	//UE_LOG(LogTemp, Log, TEXT("Item Button Clicked Event : %f"), ClickedSec);

}
