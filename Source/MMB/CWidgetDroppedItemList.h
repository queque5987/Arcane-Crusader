// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/ListView.h"
#include "CWidgetDroppedItemList.generated.h"

/**
 * 
 */
UCLASS()
class MMB_API UCWidgetDroppedItemList : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> ItemList;
};
