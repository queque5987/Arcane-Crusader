// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PCH.h"
#include "CNPCConversation.h"
#include "CInventoryItemData.generated.h"

UCLASS()
class MMB_API UCInventoryItemData : public UObject
{
	GENERATED_BODY()
	UCInventoryItemData(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FName DT_RowName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	UClass* ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 ItemCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FString strName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FString IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 ItemPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FString AttackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 Rarity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool IsShopItem = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FText ItemDetail;

	class ACStaticNPC* Owner;
public:
	int32 GetIndex() { return Index; }
	void SetIndex(int32 e) { Index = e; }
	FName GetDT_RowName() { return DT_RowName; }
	void SetDT_RowName(FName e) { DT_RowName = e; }
	UClass* GetItemClass() { return ItemClass; }
	void SetItemClass(UClass* e) { ItemClass = e; }
	int32 GetItemCount() { return ItemCount; }
	void SetItemCount(int32 e) { ItemCount = e; }
	FString GetstrName() { return strName; }
	void SetstrName(FString e) { strName = e; }
	FString GetIconTexture() { return IconTexture; }
	void SetIconTexture(FString e) { IconTexture = e; }
	ACStaticNPC* GetOwner() { return Owner; }
	void SetOwner(ACStaticNPC* e) { Owner = e; }
	int32 GetPrice() { return ItemPrice; }
	void SetPrice(int32 e) { ItemPrice = e; }
	float GetAttackDamage() { return AttackDamage; }
	void SetAttackDamage(float e) { AttackDamage = e; }
	int GetItemType() { return ItemType; }
	void SetItemType(int e) { ItemType = e; }
	int32 GetRarity() { return Rarity; }
	void SetRarity(int32 e) { Rarity = e; }
	bool GetIsShopItem() { return IsShopItem; }
	void SetIsShopItem(bool e) { IsShopItem = e; }
	FText GetItemDetail() { return ItemDetail; }
	void SetItemDetail(FText e) { ItemDetail = e; }
};
