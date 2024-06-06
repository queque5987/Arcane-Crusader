// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestComponent.h"
#include "CMonsterSpawner_Manual.h"
#include "Kismet/GameplayStatics.h"
#include "CEntrance_Quest.h"
#include "CEnemy_Nightmare.h"
#include "CEnemy_TerrorBringer.h"
#include "CEthereal.h"
#include "Engine/StaticMeshActor.h"

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
	//AActor* tempActor = FindActorByLabel(ACEntrance_Quest::StaticClass(), "TutorialZoneOutGate");
	AActor* tempActor = FindActorByTag(ACEntrance_Quest::StaticClass(), FName("TutorialZoneOutGate"));

	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (PC == nullptr) return;
	ACEntrance_Quest* TutorialGate = Cast<ACEntrance_Quest>(tempActor);
	if (TutorialGate == nullptr) return;
	TutorialGate->FocusToGate(PC);

	AActor* tempEthereal = FindActorByTag(ACEthereal::StaticClass(), FName("NPC_Ethereal"));
	AActor* tempPos = FindActorByTag(AStaticMeshActor::StaticClass(), FName("NPC_Ethereal_Empty"));
	
	ACEthereal* Ethereal = Cast<ACEthereal>(tempEthereal);
	if (tempPos == nullptr) return;
	FTransform tempTransform = tempPos->GetTransform();
	Ethereal->SetActorTransform(tempTransform);
	tempPos->Destroy();
}

void UQuestComponent::Quest1()
{
	AActor* tempActor = FindActorByTag(ACEntrance_Quest::StaticClass(), FName("RockMountainOutGate"));

	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (PC == nullptr) return;
	ACEntrance_Quest* RockMountainOutGate = Cast<ACEntrance_Quest>(tempActor);
	if (RockMountainOutGate == nullptr) return;
	RockMountainOutGate->FocusToGate(PC);
}

void UQuestComponent::Quest3()
{
}

void UQuestComponent::Init_Quest0()
{
	AActor* tempActor = FindActorByTag(ACEntrance_Quest::StaticClass(), FName("TutorialZoneInGate"));

	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (PC == nullptr) return;
	ACEntrance_Quest* TutorialGate = Cast<ACEntrance_Quest>(tempActor);
	if (TutorialGate == nullptr) return;
	TutorialGate->SetOpenGate(true);


	AActor* tempSpawner = FindActorByTag(ACMonsterSpawner_Manual::StaticClass(), FName("MonsterSpawner"));

	ACMonsterSpawner_Manual* Spawner = Cast<ACMonsterSpawner_Manual>(tempSpawner);
	if (Spawner == nullptr) return;
	ACEnemyCharacter* EC = Spawner->SpawnMonster(ACEnemy_Nightmare::StaticClass());
	ACEnemy_Nightmare* cEC = Cast<ACEnemy_Nightmare>(EC);
	if (cEC == nullptr) return;
	MonsterConfigure Config = MonsterConfigure();

	UDataTable* DT = LoadObject<UDataTable>(nullptr, TEXT("/Game/Resources/DropTable0"));
	if (DT != nullptr) Config._DropTable = DT;
	Config._HP = 80.f;
	Config._MaxHP = 200.f;
	cEC->SetMonsterConfig(Config);
}

void UQuestComponent::Init_Quest1()
{
	AActor* tempActor = FindActorByTag(ACMonsterSpawner_Manual::StaticClass(), FName("RockMountain_MonsterSpawner"));

	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (PC == nullptr) return;
	ACMonsterSpawner_Manual* Spawner = Cast<ACMonsterSpawner_Manual>(tempActor);
	if (Spawner == nullptr) return;
	ACEnemyCharacter* EC = Spawner->SpawnMonster(ACEnemy_Nightmare::StaticClass());
	ACEnemy_Nightmare* cEC = Cast<ACEnemy_Nightmare>(EC);
	if (cEC == nullptr) return;
	MonsterConfigure Config = MonsterConfigure();

	UDataTable* DT = LoadObject<UDataTable>(nullptr, TEXT("/Game/Resources/DropTable0"));
	if (DT != nullptr) Config._DropTable = DT;
	Config._HP = 1.f;
	cEC->SetMonsterConfig(Config);
}

void UQuestComponent::Init_Quest2()
{
	AActor* tempActor = FindActorByTag(ACMonsterSpawner_Manual::StaticClass(), FName("RockMountain_MonsterSpawner"));

	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (PC == nullptr) return;
	ACMonsterSpawner_Manual* Spawner = Cast<ACMonsterSpawner_Manual>(tempActor);
	if (Spawner == nullptr) return;
	Spawner->SpawnMonster(ACEnemy_TerrorBringer::StaticClass());
}

void UQuestComponent::Init_Quest3()
{
	AActor* tempActor = FindActorByTag(ACMonsterSpawner_Manual::StaticClass(), FName("MonsterSpawner"));

	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (PC == nullptr) return;
	ACMonsterSpawner_Manual* Spawner = Cast<ACMonsterSpawner_Manual>(tempActor);
	if (Spawner == nullptr) return;
	ACEnemyCharacter* EC = Spawner->SpawnMonster(ACEnemy_Nightmare::StaticClass());
	ACEnemy_Nightmare* cEC = Cast<ACEnemy_Nightmare>(EC);
	if (cEC == nullptr) return;
	MonsterConfigure Config = MonsterConfigure();

	UDataTable* DT = LoadObject<UDataTable>(nullptr, TEXT("/Game/Resources/DropTable0"));
	if (DT != nullptr) Config._DropTable = DT;
	Config._HP = 200.f;
	Config._MaxHP = 200.f;
	cEC->SetMonsterConfig(Config);
}

void UQuestComponent::Init_Quest4()
{
	AActor* tempActor = FindActorByTag(ACMonsterSpawner_Manual::StaticClass(), FName("MonsterSpawner"));

	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (PC == nullptr) return;
	ACMonsterSpawner_Manual* Spawner = Cast<ACMonsterSpawner_Manual>(tempActor);
	if (Spawner == nullptr) return;
	ACEnemyCharacter* EC = Spawner->SpawnMonster(ACEnemy_TerrorBringer::StaticClass());
	ACEnemy_TerrorBringer * cEC = Cast<ACEnemy_TerrorBringer>(EC);
	if (cEC == nullptr) return;
	MonsterConfigure Config = MonsterConfigure();

	UDataTable* DT = LoadObject<UDataTable>(nullptr, TEXT("/Game/Resources/DropTable0"));
	if (DT != nullptr) Config._DropTable = DT;
	Config._HP = 200.f;
	Config._MaxHP = 200.f;
	cEC->SetMonsterConfig(Config);
}

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
		//if (A->GetActorLabel() == Label) return A;
		if (A->IsA(FindClass)) return A;
	}
	return nullptr;
}

AActor* UQuestComponent::FindActorByTag(TSubclassOf<AActor> FindClass, FName Tag)
{
	TArray<AActor*> arrOut;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), Tag, arrOut);
	if (arrOut.Num() < 0)
	{
		UE_LOG(LogTemp, Log, TEXT("ERROR In QuestComponent : No Gate Found"));
		return nullptr;
	}
	for (AActor* A : arrOut)
	{
		//if (A->GetActorLabel() == Label) return A;
		if (A->IsA(FindClass)) return A;
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
	case(1):
		Quest1();
		return;
	case(3):
		Quest3();
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
	case(2):
		Init_Quest2();
		return;
	case(3):
		Init_Quest3();
		return;
	case(4):
		Init_Quest4();
		return;
	default:
		return;
	}
}

