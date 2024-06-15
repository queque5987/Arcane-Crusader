// Fill out your copyright notice in the Description page of Project Settings.


#include "CDynamicNPC.h"
#include "CNPCAnimInstance.h"
#include "Components/SkeletalMeshComponent.h"

ACDynamicNPC::ACDynamicNPC() : Super()
{
	SKComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SKComponent");
	SKComponent->SetupAttachment(Collider);
}

void ACDynamicNPC::BeginPlay()
{
	Super::BeginPlay();
	//SKComponent->PlayAnimation(Idle, true);
	if (NPCAnimBluperint != nullptr)
	{
		SKComponent->SetAnimClass(NPCAnimBluperint->GeneratedClass);
		NPCAnimInstance = Cast<UCNPCAnimInstance>(SKComponent->GetAnimInstance());
	}

	Initialize();
}

void ACDynamicNPC::SetNPCAnimation(int32 State)
{
	if (NPCAnimInstance == nullptr) return;
	GetWorld()->GetTimerManager().ClearTimer(PoseTimer);

	NPCAnimInstance->SetNPCPose(State);
	if (State > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(PoseTimer, FTimerDelegate::CreateLambda([&] {
			SetNPCAnimation(0);
			}), 0.3f, false);
	}
}

void ACDynamicNPC::Initialize()
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
}
