// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameInstance.h"
#include "FMonsterConfigure.h"

void UCGameInstance::Init()
{
	Super::Init();
	SelectedSaveSlot = -1;
	//SpawnMonsterConfig = NewObject<UFMonsterConfigure>(GetWorld(), UFMonsterConfigure::StaticClass(), TEXT("MonsterConfig"));
}

void UCGameInstance::Shutdown()
{
	Super::Shutdown();
}

void UCGameInstance::SetSpawnMonsterConfig(UClass* MonsterClass, UDataTable* DropTable, float HP, float MaxHP, float AttackDamage, float MaxWalkSpeed, float FlyAcc, float VirticalAcc)
{
	//if (SpawnMonsterConfig == nullptr)
	//{
	//	SpawnMonsterConfig = NewObject<UFMonsterConfigure>(GetWorld(), UFMonsterConfigure::StaticClass(), TEXT("MonsterConfig"));
	//}
	//SpawnMonsterConfig->SetProperties(
	//	MonsterClass, DropTable, HP, MaxHP, AttackDamage, MaxWalkSpeed, FlyAcc, VirticalAcc
	//);

	_MonsterClass = MonsterClass;
	_DropTable = DropTable;
	_HP = HP;
	_MaxHP = MaxHP;
	_MaxWalkSpeed = MaxWalkSpeed;
	_AttackDamage = AttackDamage;
	_FlyAcc = FlyAcc;
	_VirticalAcc = VirticalAcc;
}

void UCGameInstance::CopySpawnMonsterConfig(UFMonsterConfigure* Config)
{
	//if (SpawnMonsterConfig == nullptr)
	//{
	//	SpawnMonsterConfig = NewObject<UFMonsterConfigure>(GetWorld(), UFMonsterConfigure::StaticClass(), TEXT("MonsterConfig"));
	//}
	//SpawnMonsterConfig->SetProperties(
	//	Config->GetMonsterClass(),
	//	Config->GetDropTable(),
	//	Config->GetHP(),
	//	Config->GetMaxHP(),
	//	Config->GetMaxWalkSpeed(),
	//	Config->GetAttackDamage(),
	//	Config->GetFlyAcc(),
	//	Config->GetVirticalAcc()
	//);

	_MonsterClass = Config->GetMonsterClass();
	_DropTable = Config->GetDropTable();
	_HP = Config->GetHP();
	_MaxHP = Config->GetMaxHP();
	_MaxWalkSpeed = Config->GetMaxWalkSpeed();
	_AttackDamage = Config->GetAttackDamage();
	_FlyAcc = Config->GetFlyAcc();
	_VirticalAcc = Config->GetVirticalAcc();
}

UFMonsterConfigure* UCGameInstance::GetSpawnMonsterConfig()
{
	UFMonsterConfigure* SpawnMonsterConfig = NewObject<UFMonsterConfigure>(GetWorld(), UFMonsterConfigure::StaticClass(), TEXT("MonsterConfig"));
	SpawnMonsterConfig->SetProperties(
		_MonsterClass,
		_DropTable,
		_HP,
		_MaxHP,
		_MaxWalkSpeed,
		_AttackDamage,
		_FlyAcc,
		_VirticalAcc
	);
	return SpawnMonsterConfig;
}
