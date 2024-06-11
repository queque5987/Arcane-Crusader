// Fill out your copyright notice in the Description page of Project Settings.


#include "CStaticNPC.h"
#include "Components/TileView.h"

// Sets default values
ACStaticNPC::ACStaticNPC()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	SetRootComponent(StaticMeshComponent);
	Collider = CreateDefaultSubobject<USphereComponent>(FName("Collider"));
	Collider->SetupAttachment(StaticMeshComponent);
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Collider->InitSphereRadius(200.f);
	SetActorEnableCollision(true);

	NPCCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("NPCCameraComponent"));
	NPCCameraComponent->SetupAttachment(Collider);
	NPCCameraFixedTransform = NPCCameraComponent->GetComponentTransform();
}

void ACStaticNPC::BeginPlay()
{
	Super::BeginPlay();

	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACStaticNPC::OnOverlapBegin);
	Collider->OnComponentEndOverlap.AddDynamic(this, &ACStaticNPC::OnEndOverlap);
}

void ACStaticNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (NPCCameraOn)
	{
		FTransform CameraTransform = NPCCameraComponent->GetComponentTransform();

		CameraTransform.SetLocation(
			FMath::Lerp(CameraTransform.GetLocation(), NPCCameraFixedTransform.GetLocation(), CameraMoveSpeed)
		);
		CameraTransform.SetRotation(
			FMath::Lerp(CameraTransform.GetRotation(), NPCCameraFixedTransform.GetRotation(), CameraMoveSpeed)
		);

		NPCCameraComponent->SetWorldTransform(CameraTransform);
		if (
			FMath::IsNearlyEqual(CameraTransform.GetLocation().X, NPCCameraFixedTransform.GetLocation().X, 3.f) &&
			FMath::IsNearlyEqual(CameraTransform.GetLocation().Y, NPCCameraFixedTransform.GetLocation().Y, 3.f) &&
			FMath::IsNearlyEqual(CameraTransform.GetLocation().Z, NPCCameraFixedTransform.GetLocation().Z, 3.f)
			)
		{
			NPCCameraOn = false;
		}
	}

}

void ACStaticNPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(OtherActor))
	{
		if (ACPlayerController* PCC = Cast<ACPlayerController>(PC->GetController()))
		{
			//PCC->SetNPCConversationVisibility(true, this);
			PCC->NPCInteract_ShowAndInputReady(this);
		}
	}
}

void ACStaticNPC::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(OtherActor))
	{
		if (ACPlayerController* PCC = Cast<ACPlayerController>(PC->GetController()))
		{
			//PCC->SetNPCConversationVisibility(false, this);
			PCC->NPCInteract_UnShow();
		}
	}
}

void ACStaticNPC::RemoveItemFromItemList(UINT32 index)
{
	ItemList.RemoveAt(index);
}

void ACStaticNPC::SetNPCConversationItemList(TObjectPtr<UTileView>& NPCTileList)
{
	NPCTileList->ClearListItems();
	if (ItemList.IsEmpty()) return;
	for (int i = 0; i < ItemList.Num(); i++)
	{
		if (ItemList[i] != nullptr)
		{
			//UE_LOG(LogTemp, Log, TEXT("%s"), *ItemList[i]->GetName());
			NPCTileList->AddItem(ItemList[i]);
		}
	}
}

TArray<FNPCDialoguesRow*> ACStaticNPC::GetDialogue()
{
	TArray<FNPCDialoguesRow*> Dialogues;
	for (int i : DialogueIndex) Dialogues.Add(DialogueTable->FindRow<FNPCDialoguesRow>(FName(FString::FormatAsNumber(i)), FString("")));
	return Dialogues;
}

TArray<FQuestsRow*> ACStaticNPC::GetQuest()
{
	TArray<FQuestsRow*> Q;
	for (int i : QuestIndex)
	{
		Q.Add(QuestTable->FindRow<FQuestsRow>(FName(FString::FormatAsNumber(i)), FString("")));
	}
	return Q;
}

AActor* ACStaticNPC::SetCameraOn(bool e, FTransform CurrentCameraTransform)
{
	NPCCameraOn = e;
	if (e)
	{
		NPCCameraFixedTransform = NPCCameraComponent->GetComponentTransform();
		NPCCameraComponent->SetWorldTransform(CurrentCameraTransform);
	}
	else NPCCameraComponent->SetWorldTransform(NPCCameraFixedTransform);
	return e? NPCCameraComponent->GetOwner() : nullptr;
}
