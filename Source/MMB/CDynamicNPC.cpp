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

	//switch (State)
	//{
	//case(0):
	//	NPCAnimInstance->SetNPCPose(0);
	//	//SKComponent->PlayAnimation(Idle, true);
	//	break;
	//case(1):
	//	NPCAnimInstance->SetNPCPose(1);
	//	//SKComponent->PlayAnimation(Talking, true);
	//	GetWorld()->GetTimerManager().SetTimer(PoseTimer, FTimerDelegate::CreateLambda([&] {
	//		SetNPCAnimation(0);
	//		}), Talking->GetPlayLength(), false);
	//	break;
	//case(2):
	//	NPCAnimInstance->SetNPCPose(2);
	//	SKComponent->PlayAnimation(Thankful, false);
	//	GetWorld()->GetTimerManager().SetTimer(PoseTimer, FTimerDelegate::CreateLambda([&] {
	//		SetNPCAnimation(0);
	//		}), Thankful->GetPlayLength(), false);
	//	break;
	//case(3):
	//	NPCAnimInstance->SetNPCPose(3);
	//	SKComponent->PlayAnimation(Disappointed, false);
	//	GetWorld()->GetTimerManager().SetTimer(PoseTimer, FTimerDelegate::CreateLambda([&] {
	//		SetNPCAnimation(0);
	//		}), Disappointed->GetPlayLength(), false);
	//	break;
	//case(4):
	//	NPCAnimInstance->SetNPCPose(4);
	//	SKComponent->PlayAnimation(Bow, false);
	//	GetWorld()->GetTimerManager().SetTimer(PoseTimer, FTimerDelegate::CreateLambda([&] {
	//		SetNPCAnimation(0);
	//		}), Bow->GetPlayLength(), false);
	//	break;
	//default:
	//	break;
	//}
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
