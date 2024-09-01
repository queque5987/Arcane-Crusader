#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FMonsterConfigure.generated.h"

UCLASS()
class MMB_API UFMonsterConfigure : public UObject
{
	GENERATED_BODY()
public:
	UFMonsterConfigure();

private:
	UClass* _MonsterClass;
	class UDataTable* _DropTable;
	float _HP;
	float _MaxHP;
	float _MaxWalkSpeed;
	float _AttackDamage;
	float _FlyAcc;
	float _VirticalAcc;

public:
	void SetProperties(
		UClass* MonsterClass = nullptr,
		class UDataTable* DropTable = nullptr,
		float HP = 100.f, float MaxHP = 100.f,
		float AttackDamage = 20.f, float MaxWalkSpeed = 350.f,
		float FlyAcc = 0.5f, float VirticalAcc = 120.f
	);

	UClass* GetMonsterClass() { return _MonsterClass; };
	class UDataTable* GetDropTable() { return _DropTable; };
	float GetHP() { return _HP; };
	float GetMaxHP() {return _MaxHP;};
	float GetMaxWalkSpeed() { return _MaxWalkSpeed; };
	float GetAttackDamage() { return _AttackDamage; };
	float GetFlyAcc() { return _FlyAcc; };
	float GetVirticalAcc() { return _VirticalAcc; };
};
