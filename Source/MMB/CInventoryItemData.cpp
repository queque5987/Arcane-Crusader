// Fill out your copyright notice in the Description page of Project Settings.


#include "CInventoryItemData.h"

UCInventoryItemData::UCInventoryItemData(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//ItemStats = ItemStat();
	//ItemStat temp = ItemStat();
	//ItemStats = &temp;
	ItemStats = (ItemStat*)malloc(sizeof(struct ItemStat));
}

float UCInventoryItemData::GetAttackDamage()
{
	return ItemStats->_AttackDamage;
}

void UCInventoryItemData::SetItemStats(float AttackDamage, float Defence, float AttackSpeed, float HealPoint)
{
	ItemStats->_AttackDamage = AttackDamage;
	ItemStats->_Defence = Defence;
	ItemStats->_AttackSpeed = AttackSpeed;
	ItemStats->_HealPoint = HealPoint;


	//ItemStat temp = ItemStat(
	//	AttackDamage,
	//	Defence,
	//	AttackSpeed
	//);
	//ItemStats = &temp;
}

//void UCInventoryItemData::SetItemStats(float AttackDamage, float Defence, float AttackSpeed)
//{
//	ItemStats._AttackDamage = AttackDamage;
//	ItemStats._Defence = Defence;
//	ItemStats._AttackSpeed = AttackSpeed;
//	//ItemStats->_AttackDamage = AttackDamage;
//	//ItemStats->_Defence = Defence;
//	//ItemStats->_AttackSpeed = AttackSpeed;
//}
