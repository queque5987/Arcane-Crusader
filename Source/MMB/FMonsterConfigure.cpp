#include "FMonsterConfigure.h"

UFMonsterConfigure::UFMonsterConfigure()
{
}

void UFMonsterConfigure::SetProperties(UClass* MonsterClass, UDataTable* DropTable, float HP, float MaxHP, float AttackDamage, float MaxWalkSpeed, float FlyAcc, float VirticalAcc)
{
	_MonsterClass = MonsterClass;
	_DropTable = DropTable;
	_HP = HP;
	_MaxHP = MaxHP;
	_MaxWalkSpeed = MaxWalkSpeed;
	_AttackDamage = AttackDamage;
	_FlyAcc = FlyAcc;
	_VirticalAcc = VirticalAcc;
}
