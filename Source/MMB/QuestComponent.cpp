// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestComponent.h"
#include "CMonsterSpawner_Manual.h"
#include "Kismet/GameplayStatics.h"
#include "CEntrance_Quest.h"
#include "CEnemy_TerrorBringer.h"

UQuestComponent::UQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UQuestComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UQuestComponent::Quest0()
{
	UE_LOG(LogTemp, Log, TEXT("Quest Reward : Quest 0"));

	AActor* tempActor = FindActorByLabel(ACEntrance_Quest::StaticClass(), "TutorialZoneOutGate");

	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (PC == nullptr) return;
	ACEntrance_Quest* TutorialGate = Cast<ACEntrance_Quest>(tempActor);
	if (TutorialGate == nullptr) return;
	TutorialGate->FocusToGate(PC);
}

void UQuestComponent::Init_Quest0()
{
	AActor* tempActor = FindActorByLabel(ACEntrance_Quest::StaticClass(), "TutorialZoneInGate");

	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (PC == nullptr) return;
	ACEntrance_Quest* TutorialGate = Cast<ACEntrance_Quest>(tempActor);
	if (TutorialGate == nullptr) return;
	TutorialGate->SetOpenGate(true);
}

void UQuestComponent::Init_Quest1()
{
	AActor* tempActor = FindActorByLabel(ACMonsterSpawner_Manual::StaticClass(), "RockMountain_MonsterSpawner");

	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (PC == nullptr) return;
	ACMonsterSpawner_Manual* Spawner = Cast<ACMonsterSpawner_Manual>(tempActor);
	if (Spawner == nullptr) return;
	Spawner->SpawnMonster(ACEnemy_TerrorBringer::StaticClass());

	//TArray<AActor*> arrOut;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACMonsterSpawner_Manual::StaticClass(), arrOut);
	//if (arrOut.Num() < 0)
	//{
	//	UE_LOG(LogTemp, Log, TEXT("ERROR In QuestComponent : No Gate Found"));
	//	return;
	//}
	//ACMonsterSpawner_Manual* MonsterSpawner;
	//for (auto& A : arrOut)
	//{
	//	MonsterSpawner = Cast<ACMonsterSpawner_Manual>(A);
	//	if (MonsterSpawner == nullptr) continue;
	//}

	//RockMountain_MonsterSpawner
}

//void UQuestComponent::Init_Quest2()
//{
//}

AActor* UQuestComponent::FindActorByLabel(TSubclassOf<AActor> FindClass, FString Label)
{
	TArray<AActor*> arrOut;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), FindClass, arrOut);
	if (arrOut.Num() < 0)
	{
		UE_LOG(LogTemp, Log, TEXT("ERROR In QuestComponent : No Gate Found"));
		return nullptr;
	}
	for (AActor* A : arrOut)
	{
		if (A->GetActorLabel() == Label) return A;
		//if (A->IsA(FindClass)) return A;
	}
	return nullptr;
}

void UQuestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UQuestComponent::OnQuestCleared(int RewardIndex)
{
	switch (RewardIndex)
	{
	case(0):
		Quest0();
		return;
	default:
		return;
	}
}

void UQuestComponent::OnQuestInitialize(int InitIndex)
{
	switch (InitIndex)
	{
	case(0):
		Init_Quest0();
		return;
	case(1):
		Init_Quest1();
		return;
	//case(2):
	//	Init_Quest2();
	//	return;
	default:
		return;
	}
}

