// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "CNPCConversationDataTable.generated.h"

USTRUCT(BlueprintType)
struct FNPCConversationRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FText NPCName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FText NPCConversation;

};

UCLASS()
class MMB_API ACNPCConversationDataTable : public AActor
{
	GENERATED_BODY()
};
