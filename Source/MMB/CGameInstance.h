// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
//#include "CEnemyCharacter.h"
#include "CGameInstance.generated.h"

UCLASS()
class MMB_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings")
	int32 SelectedSaveSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings")
	TArray<uint8> TempSaveFileAddress;

	//Deprecated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings")
	UClass* SpawnMonsterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings")
	int32 BattleQuestRowIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings")
	float StartLevelClock;

	virtual void Init() override;
	virtual void Shutdown() override;

	//Deprecated
	void SetSpawnMonsterConfig(
		UClass* MonsterClass = nullptr,
		class UDataTable* DropTable = nullptr,
		float HP = 100.f, float MaxHP = 100.f,
		float AttackDamage = 20.f, float MaxWalkSpeed = 350.f,
		float FlyAcc = 0.5f, float VirticalAcc = 120.f
	);
	//Deprecated
	void CopySpawnMonsterConfig(
		class UFMonsterConfigure* Config
	);
	//Deprecated
	class UFMonsterConfigure* GetSpawnMonsterConfig();
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings")
	UClass* _MonsterClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings")
	class UDataTable* _DropTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings")
	float _HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings")
	float _MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings")
	float _MaxWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings")
	float _AttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings")
	float _FlyAcc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings")
	float _VirticalAcc;
};
