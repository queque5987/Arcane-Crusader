// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/TileView.h"
#include "CInventoryItemData.h"
#include "Engine/StaticMesh.h"
#include "PCH.h"
#include "CustomDataTables.h"
//#include "Quest.h"
#include "CStaticNPC.generated.h"

UCLASS()
class MMB_API ACStaticNPC : public AActor
{
	GENERATED_BODY()
	
public:	
	ACStaticNPC();

	UPROPERTY(EditAnywhere)
	class UCameraComponent* NPCCameraComponent;
	UPROPERTY(EditAnywhere)
	float CameraMoveSpeed = 0.3f;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere)
	class USphereComponent* Collider;


	UPROPERTY(EditAnywhere)
	class UDataTable* DialogueTable;
	UPROPERTY(EditAnywhere)
	TArray<int> DialogueIndex;
	UPROPERTY(EditAnywhere)
	bool bPrintDialogueRandom;

	int CurrentDialogue = 0;

	UPROPERTY(EditAnywhere)
	class UDataTable* QuestTable;
	UPROPERTY(EditAnywhere)
	TArray<int> QuestIndex;

	virtual void Initialize() {}

protected:
	//TObjectPtr<UTileView> ItemList;

	TArray<class UCInventoryItemData*> ItemList;
	FTransform NPCCameraFixedTransform;

	virtual void BeginPlay() override;
	bool NPCCameraOn;
public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//TObjectPtr<UTileView> GetItemList() { return ItemList; }
	TArray<class UCInventoryItemData*> GetItemList() { return ItemList; }
	void SetItemList(TArray<class UCInventoryItemData*> e) { ItemList = e; }
	void RemoveItemFromItemList(UINT32 index);
	class UCInventoryItemData* GetItemFromItemList(UINT32 index) { return ItemList[index]; }
	int GetItemListLength() { return ItemList.Num(); }

	void SetNPCConversationItemList(TObjectPtr<UTileView>& NPCTileList);

	virtual TArray<FNPCDialoguesRow*> GetDialogue();
	virtual TArray<FQuestsRow*> GetQuest();
	AActor* SetCameraOn(bool e, FTransform CurrentCameraTransform);
};
