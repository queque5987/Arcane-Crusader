#include "CCollisionCallFuncActor.h"
#include "Components/BoxComponent.h"
#include "CPlayerCharacter.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "CMonsterSpawner_Manual.h"
#include "CEnemy_Dragon.h"
#include "IEnemyStateManager.h"
#include "IPlayerUIController.h"
#include "GameFramework/PlayerController.h"
#include "CustomDataTables.h"
#include "IEnemyBBState.h"
#include "Engine/StaticMeshActor.h"

ACCollisionCallFuncActor::ACCollisionCallFuncActor()
{
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColliderComponent"));
	SetRootComponent(Collider);
	Collider->SetCollisionObjectType(EnemyAttackChannel);
	Called = false;
}

void ACCollisionCallFuncActor::BeginPlay()
{
	Super::BeginPlay();
	
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACCollisionCallFuncActor::OnOverlap);
}

void ACCollisionCallFuncActor::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Called) return;
	
	if (!OtherActor->IsA(ACPlayerCharacter::StaticClass())) return;

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(OtherActor);
	if (Player == nullptr) return;

	switch (CallFuncIndex)
	{
	case(0):
		CallFunc0();
		break;
	case(1):
		CallFunc1(Player);
		break;
	case(2):
		CallFunc2(Player);
		break;
	case(3):
		CallFunc3(Player);
		break;
	case(4):
		CallFunc4(Player);
		break;
	default:
		break;
	}
}

void ACCollisionCallFuncActor::CallFunc0()
{
	//Player->LaunchCharacter(Player->GetActorUpVector() * 500.f, true, true);

	AActor* tempActor = FindActorByTag(AActor::StaticClass(), FName("TutorialDestructibleBridge"));
	if (tempActor == nullptr) return;

	AGeometryCollectionActor* DestructibleBridge = Cast<AGeometryCollectionActor>(tempActor);
	if (DestructibleBridge == nullptr) return;

	UGeometryCollectionComponent* GCC = DestructibleBridge->GetGeometryCollectionComponent();
	if (GCC == nullptr) return;

	GCC->SetSimulatePhysics(true);
	Called = true;
}

void ACCollisionCallFuncActor::CallFunc1(ACPlayerCharacter* Player)
{
	// Spawn Mountain Dragon & Fall
	AActor* tempActor = FindActorByTag(ACMonsterSpawner_Manual::StaticClass(), FName("TutorialSpawner_1"));
	if (tempActor == nullptr) return;
	ACMonsterSpawner_Manual* Spawner = Cast<ACMonsterSpawner_Manual>(tempActor);
	if (Spawner == nullptr) return;
	ACEnemyCharacter* EC = Spawner->SpawnMonster(ACEnemy_Dragon::StaticClass(), 9000.f);
	if (EC == nullptr) return;

	MonsterConfigure Config = MonsterConfigure();

	UDataTable* DT = LoadObject<UDataTable>(nullptr, TEXT("/Game/Resources/DataTables/DropTable/DropTable_Spike.DropTable_Spike"));
	if (DT != nullptr) Config._DropTable = DT;
	Config._HP = 1000.f;
	Config._MaxHP = 1000.f;
	Config._AttackDamage *= 1.3f;
	EC->SetMonsterConfig(Config);

	IIEnemyStateManager* IEC = Cast<IIEnemyStateManager>(EC);
	if (IEC == nullptr) return;
	IEC->FreeFall_Init();

	IIEnemyBBState* BBState = Cast<IIEnemyBBState>(EC->GetController());
	BBState->SetbBusy(true);

	// Despose Tutorial Garbages
	TArray<AActor*> TutorialActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Tutorial_Desposable"), TutorialActors);
	for (AActor* Desposable : TutorialActors)
	{
		if (Desposable == nullptr) continue;
		UE_LOG(LogTemp, Log, TEXT("ACCollisionCallFuncActor : Destory Actor : %s"), *Desposable->GetName());
		Desposable->Destroy();
	}

	// Add Dragon Hunt Quest
	IIItemManager* ItemManager = Cast<IIItemManager>(GetWorld()->GetAuthGameMode());
	if (ItemManager == nullptr) return;
	FQuestsRow* QR = ItemManager->GetQuestbyIndex(10);
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(Player->GetController());
	if (QR == nullptr) return;
	if (UIController == nullptr) return;
	UIController->AddQuest(QR);

	Called = true;
}

void ACCollisionCallFuncActor::CallFunc2(ACPlayerCharacter* Player)
{
	IIItemManager* ItemManager = Cast<IIItemManager>(GetWorld()->GetAuthGameMode());
	if (ItemManager == nullptr) return;
	FQuestsRow* QR = ItemManager->GetQuestbyIndex(9);
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(Player->GetController());
	if (QR == nullptr) return;
	if (UIController == nullptr) return;
	UIController->AddQuest(QR);

	Called = true;
}

void ACCollisionCallFuncActor::CallFunc3(ACPlayerCharacter* Player)
{
	TArray<AActor*> TutorialActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Tutorial_Boss_In"), TutorialActors);
	for (AActor* Desposable : TutorialActors)
	{
		if (Desposable == nullptr) return;
		AStaticMeshActor* SMA = Cast<AStaticMeshActor>(Desposable);
		if (SMA == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Tutorial_Boss_In : %s Is Not StaticMeshActor"), *Desposable->GetName());
			return;
		}
		SMA->GetStaticMeshComponent()->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	}

	Called = true;
}

void ACCollisionCallFuncActor::CallFunc4(ACPlayerCharacter* Player)
{
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(Player->GetController());
	if (UIController == nullptr) return;
	
	UIController->ManualQuestClear(FString(TEXT("튜토리얼 8")), 0);

	TArray<AActor*> TutorialActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Tutorial_Desposable"), TutorialActors);
	for (AActor* Desposable : TutorialActors)
	{
		if (Desposable == nullptr) continue;
		UE_LOG(LogTemp, Log, TEXT("ACCollisionCallFuncActor : Destory Actor : %s"), *Desposable->GetName());
		Desposable->Destroy();
	}

	TutorialActors.Empty();
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Tutorial_Desposable2"), TutorialActors);
	for (AActor* Desposable : TutorialActors)
	{
		if (Desposable == nullptr) continue;
		UE_LOG(LogTemp, Log, TEXT("ACCollisionCallFuncActor : Destory Actor : %s"), *Desposable->GetName());
		Desposable->Destroy();
	}

	

	Called = true;
}

void ACCollisionCallFuncActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AActor* ACCollisionCallFuncActor::FindActorByTag(TSubclassOf<AActor> FindClass, FName Tag)
{
	TArray<AActor*> arrOut;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), Tag, arrOut);
	if (arrOut.Num() < 0)
	{
		UE_LOG(LogTemp, Log, TEXT("ACCollisionCallFuncActor : No Gate Found"));
		return nullptr;
	}
	for (AActor* A : arrOut)
	{
		if (A->IsA(FindClass)) return A;
	}
	return nullptr;
}

