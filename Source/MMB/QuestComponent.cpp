// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestComponent.h"
#include "CMonsterSpawner_Manual.h"
#include "Kismet/GameplayStatics.h"
#include "CEntrance_Quest.h"
#include "CEnemy_Nightmare.h"
#include "CEnemy_TerrorBringer.h"
#include "CEnemy_Barghest.h"
#include "CEnemy_Dragon.h"
#include "CEthereal.h"
#include "Engine/StaticMeshActor.h"
#include "IItemManager.h"
#include "CustomDataTables.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

UQuestComponent::UQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UQuestComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UQuestComponent::Quest0()
{
	AActor* tempActor = FindActorByTag(ACEntrance_Quest::StaticClass(), FName("Tutorial_0"));

	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (PC == nullptr) return;
	ACEntrance_Quest* TutorialGate = Cast<ACEntrance_Quest>(tempActor);
	if (TutorialGate == nullptr) return;
	TutorialGate->FocusToGate(PC);

	IIItemManager* ItemManager = Cast<IIItemManager>(GetWorld()->GetAuthGameMode());
	if (ItemManager == nullptr) return;
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(PC->GetController());
	if (UIController == nullptr) return;
	FQuestsRow* QR = ItemManager->GetQuestbyIndex(5);
	FQuestsRow* QR_ToRemove = ItemManager->GetQuestbyIndex(4);
	if (QR != nullptr)
	{
		UIController->RemoveQuest(QR_ToRemove);
		UIController->AddQuest(QR);
	}
}

void UQuestComponent::Quest1()
{
	AActor* tempActor = FindActorByTag(ACEntrance_Quest::StaticClass(), FName("Tutorial_1"));

	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (PC == nullptr) return;
	ACEntrance_Quest* TutorialGate = Cast<ACEntrance_Quest>(tempActor);
	if (TutorialGate == nullptr) return;
	TutorialGate->FocusToGate(PC);

	IIItemManager* ItemManager = Cast<IIItemManager>(GetWorld()->GetAuthGameMode());
	if (ItemManager == nullptr) return;
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(PC->GetController());
	if (UIController == nullptr) return;
	FQuestsRow* QR = ItemManager->GetQuestbyIndex(6);
	FQuestsRow* QR_ToRemove = ItemManager->GetQuestbyIndex(5);
	if (QR != nullptr)
	{
		UIController->RemoveQuest(QR_ToRemove);
		UIController->AddQuest(QR);
	}
}

void UQuestComponent::Quest2()
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (PC == nullptr) return;
	IIItemManager* ItemManager = Cast<IIItemManager>(GetWorld()->GetAuthGameMode());
	if (ItemManager == nullptr) return;
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(PC->GetController());
	if (UIController == nullptr) return;
	FQuestsRow* QR = ItemManager->GetQuestbyIndex(7);
	FQuestsRow* QR_ToRemove = ItemManager->GetQuestbyIndex(6);
	if (QR != nullptr)
	{
		UIController->RemoveQuest(QR_ToRemove);
		UIController->AddQuest(QR);
	}
}

void UQuestComponent::Quest3()
{
	AActor* tempActor = FindActorByTag(ACEntrance_Quest::StaticClass(), FName("Tutorial_2"));

	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (PC == nullptr) return;
	ACEntrance_Quest* TutorialGate = Cast<ACEntrance_Quest>(tempActor);
	if (TutorialGate == nullptr) return;
	TutorialGate->FocusToGate(PC);

	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(PC->GetController());
	if (UIController == nullptr) return;
	IIItemManager* ItemManager = Cast<IIItemManager>(GetWorld()->GetAuthGameMode());
	if (ItemManager == nullptr) return;
	FQuestsRow* QR = ItemManager->GetQuestbyIndex(8);
	FQuestsRow* QR_ToRemove = ItemManager->GetQuestbyIndex(7);
	if (QR != nullptr)
	{
		UIController->RemoveQuest(QR_ToRemove);
		UIController->AddQuest(QR);
	}
}

void UQuestComponent::Quest4()
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (PC == nullptr) return;
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(PC->GetController());
	if (UIController == nullptr) return;
	IIItemManager* ItemManager = Cast<IIItemManager>(GetWorld()->GetAuthGameMode());
	if (ItemManager == nullptr) return;
	//FQuestsRow* QR = ItemManager->GetQuestbyIndex(9);
	FQuestsRow* QR_ToRemove = ItemManager->GetQuestbyIndex(8);
	if (QR_ToRemove != nullptr)
	{
		UIController->RemoveQuest(QR_ToRemove);
		//UIController->AddQuest(QR);
	}
}

void UQuestComponent::Quest5()
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (PC == nullptr) return;
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(PC->GetController());
	if (UIController == nullptr) return;
	IIItemManager* ItemManager = Cast<IIItemManager>(GetWorld()->GetAuthGameMode());
	if (ItemManager == nullptr) return;
	//FQuestsRow* QR = ItemManager->GetQuestbyIndex(10);
	FQuestsRow* QR_ToRemove = ItemManager->GetQuestbyIndex(9);
	if (QR_ToRemove != nullptr)
	{
		UIController->RemoveQuest(QR_ToRemove);
		//UIController->AddQuest(QR);
	}
}

void UQuestComponent::Quest6()
{
	ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	if (PC == nullptr) return;
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(PC->GetController());
	if (UIController == nullptr) return;
	IIItemManager* ItemManager = Cast<IIItemManager>(GetWorld()->GetAuthGameMode());
	if (ItemManager == nullptr) return;
	FQuestsRow* QR = ItemManager->GetQuestbyIndex(11);
	FQuestsRow* QR_ToRemove = ItemManager->GetQuestbyIndex(10);
	if (QR_ToRemove != nullptr)
	{
		UIController->RemoveQuest(QR_ToRemove);
		UIController->AddQuest(QR);
	}

	TArray<AActor*> arrOut;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Tutorial_Boss"), arrOut);
	if (arrOut.Num() < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR In QuestComponent : No Actor Found"));
		return;
	}
	for (AActor* A : arrOut)
	{
		if (A == nullptr) continue;
		A->Destroy();
	}
}

void UQuestComponent::Init_Quest0()
{


	//AActor* tempActor = FindActorByTag(ACEntrance_Quest::StaticClass(), FName("TutorialZoneInGate"));

	//ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	//if (PC == nullptr) return;
	//ACEntrance_Quest* TutorialGate = Cast<ACEntrance_Quest>(tempActor);
	//if (TutorialGate == nullptr) return;
	//TutorialGate->SetOpenGate(true);


	//AActor* tempSpawner = FindActorByTag(ACMonsterSpawner_Manual::StaticClass(), FName("MonsterSpawner"));

	//ACMonsterSpawner_Manual* Spawner = Cast<ACMonsterSpawner_Manual>(tempSpawner);
	//if (Spawner == nullptr) return;
	//ACEnemyCharacter* EC = Spawner->SpawnMonster(ACEnemy_Nightmare::StaticClass());
	//ACEnemy_Nightmare* cEC = Cast<ACEnemy_Nightmare>(EC);
	//if (cEC == nullptr) return;
	//MonsterConfigure Config = MonsterConfigure();

	//UDataTable* DT = LoadObject<UDataTable>(nullptr, TEXT("/Game/Resources/DataTables/DropTable_Tusk.DropTable_Tusk"));
	//if (DT != nullptr) Config._DropTable = DT;
	//Config._HP = 1000.f;
	//Config._MaxHP = 5000.f;
	//cEC->SetMonsterConfig(Config);
}

void UQuestComponent::Init_Quest1()
{
	AActor* tempActor = FindActorByTag(ACMonsterSpawner_Manual::StaticClass(), FName("TutorialSpawner_0"));

	//ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	//if (PC == nullptr) return;
	ACMonsterSpawner_Manual* Spawner = Cast<ACMonsterSpawner_Manual>(tempActor);
	if (Spawner == nullptr) return;
	UDataTable* DT;
	for (int i = 0; i < 3; i++)
	{
		ACEnemyCharacter* EC = Spawner->SpawnMonster(ACEnemy_Barghest::StaticClass());
		MonsterConfigure Config = MonsterConfigure();

		DT = LoadObject<UDataTable>(nullptr, i == 0 ? TEXT("/Game/Resources/DataTables/DropTable/DropTable_Barghest_Tutorial_RS") : TEXT("/Game/Resources/DataTables/DropTable/DropTable_Barghest"));
		
		if (DT != nullptr) Config._DropTable = DT;
		Config._MaxHP = 100.f;
		Config._HP = 100.f;
		EC->SetMonsterConfig(Config);
	}
}

void UQuestComponent::Init_Quest2()
{
	AActor* tempActor = FindActorByTag(ACMonsterSpawner_Manual::StaticClass(), FName("TutorialSpawner_0"));

	ACMonsterSpawner_Manual* Spawner = Cast<ACMonsterSpawner_Manual>(tempActor);
	if (Spawner == nullptr) return;
	UDataTable* DT;
	for (int i = 0; i < 3; i++)
	{
		ACEnemyCharacter* EC = Spawner->SpawnMonster(ACEnemy_Barghest::StaticClass());
		MonsterConfigure Config = MonsterConfigure();

		DT = LoadObject<UDataTable>(nullptr, i == 0 ? TEXT("/Game/Resources/DataTables/DropTable/DropTable_Barghest_Tutorial_RS") : TEXT("/Game/Resources/DataTables/DropTable/DropTable_Barghest"));

		if (DT != nullptr) Config._DropTable = DT;
		Config._MaxHP = 100.f;
		Config._HP = 100.f;
		EC->SetMonsterConfig(Config);
	}
}

void UQuestComponent::Init_Quest3()
{
	AActor* tempActor = FindActorByTag(ACMonsterSpawner_Manual::StaticClass(), FName("MonsterSpawner"));

	//ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	//if (PC == nullptr) return;
	ACMonsterSpawner_Manual* Spawner = Cast<ACMonsterSpawner_Manual>(tempActor);
	if (Spawner == nullptr) return;
	ACEnemyCharacter* EC = Spawner->SpawnMonster(ACEnemy_Nightmare::StaticClass());
	ACEnemy_Nightmare* cEC = Cast<ACEnemy_Nightmare>(EC);
	if (cEC == nullptr) return;
	MonsterConfigure Config = MonsterConfigure();
	
	UDataTable* DT = LoadObject<UDataTable>(nullptr, TEXT("/Game/Resources/DataTables/DropTable/DropTable_Tusk.DropTable_Tusk"));
	if (DT != nullptr) Config._DropTable = DT;
	Config._HP = 30000.f;
	Config._MaxHP = 30000.f;
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

	UDataTable* DT = LoadObject<UDataTable>(nullptr, TEXT("/Game/Resources/DataTables/DropTable/DropTable_Spike.DropTable_Spike"));
	if (DT != nullptr) Config._DropTable = DT;
	Config._HP = 5000.f;
	Config._MaxHP = 5000.f;
	cEC->SetMonsterConfig(Config);
}

void UQuestComponent::Init_Quest5()
{
	AActor* tempActor = FindActorByTag(ACMonsterSpawner_Manual::StaticClass(), FName("MonsterSpawner"));

	//ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	//if (PC == nullptr) return;
	ACMonsterSpawner_Manual* Spawner = Cast<ACMonsterSpawner_Manual>(tempActor);
	if (Spawner == nullptr) return;
	ACEnemyCharacter* EC = Spawner->SpawnMonster(ACEnemy_Nightmare::StaticClass());
	ACEnemy_Nightmare* cEC = Cast<ACEnemy_Nightmare>(EC);
	if (cEC == nullptr) return;
	MonsterConfigure Config = MonsterConfigure();

	UDataTable* DT = LoadObject<UDataTable>(nullptr, TEXT("/Game/Resources/DataTables/DropTable/DropTable_Tusk.DropTable_Tusk"));
	if (DT != nullptr) Config._DropTable = DT;
	Config._HP = 4000.f;
	Config._MaxHP = 4000.f;
	Config._AttackDamage *= 1.3f;
	cEC->SetMonsterConfig(Config);
}

void UQuestComponent::Init_Quest6()
{
	AActor* tempActor = FindActorByTag(ACMonsterSpawner_Manual::StaticClass(), FName("MonsterSpawner"));

	//ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(GetOwner());
	//if (PC == nullptr) return;
	ACMonsterSpawner_Manual* Spawner = Cast<ACMonsterSpawner_Manual>(tempActor);
	if (Spawner == nullptr) return;
	ACEnemyCharacter* EC = Spawner->SpawnMonster(ACEnemy_TerrorBringer::StaticClass());
	ACEnemy_TerrorBringer* cEC = Cast<ACEnemy_TerrorBringer>(EC);
	if (cEC == nullptr) return;
	MonsterConfigure Config = MonsterConfigure();

	UDataTable* DT = LoadObject<UDataTable>(nullptr, TEXT("/Game/Resources/DataTables/DropTable/DropTable_Spike.DropTable_Spike"));
	if (DT != nullptr) Config._DropTable = DT;
	Config._HP = 6500.f;
	Config._MaxHP = 6500.f;
	Config._AttackDamage *= 1.3f;
	cEC->SetMonsterConfig(Config);
}

void UQuestComponent::Init_Quest7()
{
	UE_LOG(LogTemp, Log, TEXT("Init 7 Called"));
	//AActor* tempActor = FindActorByTag(AActor::StaticClass(), FName("TutorialDestructibleBridge"));
	//if (tempActor == nullptr) return;

	//AGeometryCollectionActor* DestructibleBridge = Cast<AGeometryCollectionActor>(tempActor);
	//if (DestructibleBridge == nullptr) return;

	//UGeometryCollectionComponent* GCC = DestructibleBridge->GetGeometryCollectionComponent();
	//if (GCC == nullptr) return;

	//GCC->SetSimulatePhysics(true);
	
}

void UQuestComponent::Init_Quest8()
{
}

void UQuestComponent::Init_Quest9()
{
	AActor* tempActor = FindActorByTag(ACMonsterSpawner_Manual::StaticClass(), FName("MonsterSpawner"));
	if (tempActor == nullptr) return;
	ACMonsterSpawner_Manual* Spawner = Cast<ACMonsterSpawner_Manual>(tempActor);
	if (Spawner == nullptr) return;
	ACEnemyCharacter* EC = Spawner->SpawnMonster(ACEnemy_Dragon::StaticClass());
	if (EC == nullptr) return;

	MonsterConfigure Config = MonsterConfigure();

	UDataTable* DT = LoadObject<UDataTable>(nullptr, TEXT("/Game/Resources/DataTables/DropTable/DropTable_Spike.DropTable_Spike"));
	if (DT != nullptr) Config._DropTable = DT;
	Config._HP = 4000.f;
	Config._MaxHP = 4000.f;
	Config._AttackDamage *= 2.5f;
	EC->SetMonsterConfig(Config);
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
	case(2):
		Quest2();
		return;
	case(3):
		Quest3();
		return;
	case(4):
		Quest4();
		return;
	case(5):
		Quest5();
		return;
	case(6):
		Quest6();
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
	case(2):
		Init_Quest2();
		return;
	case(3):
		Init_Quest3();
		return;
	case(4):
		Init_Quest4();
		return;
	case(5):
		Init_Quest5();
		return;
	case(6):
		Init_Quest6();
		return;
	case(7):
		Init_Quest7();
		return;
	case(8):
		Init_Quest8();
		return;
	case(9):
		Init_Quest9();
		return;
	default:
		return;
	}
}

