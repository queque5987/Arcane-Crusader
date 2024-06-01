// Fill out your copyright notice in the Description page of Project Settings.


#include "CStageGameMode.h"
#include "CGameInstance.h"

ACStageGameMode::ACStageGameMode() : Super()
{
	ConstructorHelpers::FObjectFinder<UDataTable> QuestTableFinder(TEXT("/Game/Resources/DataTables/DT_BattleField_QuestsTable.DT_BattleField_QuestsTable"));
	if (QuestTableFinder.Succeeded())	QuestTable = QuestTableFinder.Object;
}

void ACStageGameMode::BeginPlay()
{
	Super::BeginPlay();

}

FQuestsRow* ACStageGameMode::GetQuestbyIndex(int32 QuestIdx)
{
	return QuestTable->FindRow<FQuestsRow>(FName(FString::FormatAsNumber(QuestIdx)), FString(""));
}
