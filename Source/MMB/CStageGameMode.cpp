// Fill out your copyright notice in the Description page of Project Settings.


#include "CStageGameMode.h"
#include "CGameInstance.h"
#include "Components/DirectionalLightComponent.h"
#include "Engine/DirectionalLight.h"

ACStageGameMode::ACStageGameMode() : Super()
{
	ConstructorHelpers::FObjectFinder<UDataTable> QuestTableFinder(TEXT("/Game/Resources/DataTables/DT_BattleField_QuestsTable"));
	if (QuestTableFinder.Succeeded())	QuestTable = QuestTableFinder.Object;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	TArray<AActor*> tempArr;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("DirectionalLight"), tempArr);
	if (tempArr.Num() <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("ERROR In ACStageGameMode : No Directional Light Found"));
	}
	for (AActor* A : tempArr)
	{
		if (ADirectionalLight* DL = Cast<ADirectionalLight>(A))
		{
			DirectionalLight = DL;
		}
	}
}

void ACStageGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ACStageGameMode::Tick(float DeltaSeconds)
{
	if (DirectionalLight == nullptr) return;

// On Hour Per Sec
	float TickTime = DeltaSeconds * MaxClock / FullDaySecond;
	LevelClock += TickTime;
	if (LevelClock > MaxClock) LevelClock -= MaxClock;

	float Angle = 360.f / FullDaySecond * DeltaSeconds;
	FQuat Rot = FQuat(FVector(0.f, 1.f, 0.f), FMath::DegreesToRadians(Angle));
	DirectionalLight->AddActorLocalRotation(Rot);
}

FQuestsRow* ACStageGameMode::GetQuestbyIndex(int32 QuestIdx)
{
	return QuestTable->FindRow<FQuestsRow>(FName(FString::FormatAsNumber(QuestIdx)), FString(""));
}

void ACStageGameMode::InitLevelClock(float fClock)
{
	if (DirectionalLight == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("ACStageGameMode : DirectionalLight Not Found"));
		return;
	}

	float Angle = (FMath::Abs(LevelClock - fClock) / MaxClock) * 360.f;

	LevelClock = fClock;

	FQuat Rot = FQuat(FVector(0.f, 1.f, 0.f), FMath::DegreesToRadians(Angle));
	DirectionalLight->AddActorLocalRotation(Rot);
}
