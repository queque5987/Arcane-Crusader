// Fill out your copyright notice in the Description page of Project Settings.


#include "CEthereal.h"
#include "IItemManager.h"

ACEthereal::ACEthereal() : Super()
{
	SetActorEnableCollision(true);

	//
	// 
	// ::FObjectFinder<UStaticMesh> SMFinder(TEXT("/Game/Isometric_World/Sky_Temple/Meshes/Sculptures/SM_Scultpture_Angel_01.SM_Scultpture_Angel_01"));
	//if (SMFinder.Succeeded())
	//{
	//	StaticMeshComponent->SetStaticMesh(SMFinder.Object);
	//}
	//StaticMeshComponent->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));
}

void ACEthereal::BeginPlay()
{
	Super::BeginPlay();
	//Collider->OnComponentBeginOverlap.AddDynamic(this, &ACEthereal::OnOverlapBegin);
	//Collider->OnComponentEndOverlap.AddDynamic(this, &ACEthereal::OnEndOverlap);

	FString CurrentLevel = GetWorld()->GetName();
	Initialize();
}

//void ACEthereal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("On Overlap Begin... Ethereal Chat On to: %s"), *OtherActor->GetName()));
//	if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(OtherActor))
//	{
//		if (ACPlayerController* PCC = Cast<ACPlayerController>(PC->GetController()))
//		{
//			PCC->SetNPCConversationVisibility(true, this);
//		}
//	}
//}
//
//void ACEthereal::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("On End Overlap... Ethereal Chat Off to: %s"), *OtherActor->GetName()));
//	if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(OtherActor))
//	{
//		if (ACPlayerController* PCC = Cast<ACPlayerController>(PC->GetController()))
//		{
//			PCC->SetNPCConversationVisibility(false, this);
//		}
//	}
//}

void ACEthereal::Initialize()
{
	ItemList.Empty();

	IIItemManager* ItemManager = Cast<IIItemManager>(GetWorld()->GetAuthGameMode());
	if (ItemManager == nullptr) return;

	for (FName PossessItemRowName : PossessItems)
	{
		UCInventoryItemData* ID = ItemManager->GetItem(PossessItemRowName);
		if (ID == nullptr) continue;
		ItemList.Add(ID);
	}

	//for (int i = 0; i < 3; i++)
	//{
	//	//UCInventoryItemData* T = NewObject<UCInventoryItemData>(this, UCInventoryItemData::StaticClass(), FName(FString::FromInt(ItemList->GetListItems().Num())));
	//	UCInventoryItemData* T = NewObject<UCInventoryItemData>(this, UCInventoryItemData::StaticClass(), FName(FString::FromInt(i)));
	//	T->SetIndex(i);
	//	T->SetIconTexture("Tex_gemstone_11_b");
	//	T->SetItemClass(ACStaff::StaticClass());
	//	T->SetItemCount(1);
	//	T->SetstrName(FString::FString(TEXT("Staff_")) + FString::FromInt(i));
	//	T->SetOwner(this);
	//	T->SetIsShopItem(true);
	//	T->SetItemDetail(FText::FromString("Test"));
	//	ItemList.Add(T);
	//}
}

//TArray<FNPCDialoguesRow*> ACEthereal::GetDialogue()
//{
//	TArray<FNPCDialoguesRow*> Dialogues;
//	for (int i : DialogueIndex) Dialogues.Add(DialogueTable->FindRow<FNPCDialoguesRow>(FName(FString::FormatAsNumber(i)), FString("")));
//	return Dialogues;
//}
