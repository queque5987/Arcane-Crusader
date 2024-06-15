#pragma once

#include "MMBGameModeBase.h"
#include "CPlayerController.h"
#include "CPlayerCharacter.h"
#include "CPlayerAnimInstance.h"
#include "CWeapon.h"
#include "CBattleStaff.h"
#include "CStaff.h"
#include "CEnemyAIController.h"
#include "CEnemyCharacter.h"
#include "CEnemyAnimInstance.h"
#include "CEnemy_AnimInstance_Nightmare.h"
#include "CEntrance.h"
#include "CEntrance0.h"
#include "CEntrance_Quest.h"
#include "CEntrance_Cinematic.h"
#include "CQuestData.h"
#include "CQuest.h"
#include "CMeteor.h"
#include "CProjectile.h"
#include "CInventoryItemData.h"
#include "CustomDataTables.h"
#include "CStaticNPC.h"
#include "CDroppedItem.h"
#include "CWidgetDroppedItem.h"
#include "CWidgetDroppedItemList.h"

#define PLAYER_UI_INTERACTING		UINT(1) << 0
#define PLAYER_RAGDOLL				UINT(1) << 1
#define PLAYER_CANGETUP				UINT(1) << 2
#define PLAYER_ROLL_INVINCIBLE		UINT(1) << 3

#define PLAYER_INPUT_W				UINT(1) << 4
#define PLAYER_INPUT_S				UINT(1) << 5
#define PLAYER_INPUT_A				UINT(1) << 6
#define PLAYER_INPUT_D				UINT(1) << 7

#define PLAYER_ATTACKING			UINT(1) << 8
#define PLAYER_ATTACK_CANCLE_UNLOCK UINT(1) << 9
#define PLAYER_STAMINA_RUNOUT		UINT(1) << 10
#define PLAYER_ROLLING				UINT(1) << 11

#define PLAYER_INPUT_TYPE_CLICK		UINT(1) << 12
#define PLAYER_INPUT_TYPE_SHIFT		UINT(1) << 13
#define PLAYER_INPUT_TYPE_LOOK		UINT(1) << 14
#define PLAYER_INPUT_TYPE_JUMP		UINT(1) << 15

#define PLAYER_INPUT_TYPE_MOVE		UINT(1) << 16
#define PLAYER_COMBO_STACK_1		UINT(1) << 17
#define PLAYER_COMBO_STACK_2		UINT(1) << 18
#define PLAYER_COMBO_STACK_3		UINT(1) << 19

#define PLAYER_GETTINGUP			UINT(1) << 20
#define PLAYER_STAMINA_REGAIN		UINT(1) << 21
#define PLAYER_DIED					UINT(1) << 22
#define PLAYER_DRINKING_POTION		UINT(1) << 23

#define PLAYER_CLIMBING_ROPE		UINT(1) << 24
#define PLAYER_JUMPING_POINTS		UINT(1) << 25
//#define UINT(1) << 26
//#define UINT(1) << 27

#define PLAYER_INVENTORY_HOVERRING	UINT(1) << 28
//#define UINT(1) << 29
//#define UINT(1) << 30
//#define UINT(1) << 31

#define EnemyAttackChannel		ECollisionChannel::ECC_EngineTraceChannel1
#define PlayerAttackChannel		ECollisionChannel::ECC_EngineTraceChannel2


#define E_MELEEATTACKCOMBO_3_EXPLODE					1
#define E_MELEEATTACKCOMBO_3_FINALATTACK_EXPLODE		2
#define E_MELEEATTACKCOMBO_3_FINALATTACK_BONUS_EXPLODE	3
#define E_MELEEATTACKCOMBO_2_EXPLODE					4
#define E_MELEEATTACK_HITEFFECT							5
#define E_MELEEATTACKCOMBO_1_PROJECTILE					6
#define E_MELLEATTACKCOMBO_1_PROJECTILE_EXPLODE			7
#define E_MELLEATTACKCOMBO_1_PROJECTILE_LAUNCH			8
#define E_MELLEATTACKCOMBO_1_PROJECTILE_SPAWN			9
#define E_MELLEATTACKCOMBO_2_PROJECTILE					10
#define E_MELLEWEAPON_ATTACKING_EFFECT					11
#define E_MELLEWEAPON_ATTACK_TRAIL						12
#define E_MELLEWEAPON_ATTACK_HIT						13
#define E_MELLEATTACKCOMBO_2_PROJECTILE_HIT				14
#define MAX_E_WEAPONEFFECT								15

#define SE_MELEEATTACKCOMBO_3_EXPLODE					0
#define SE_MELEEATTACKCOMBO_2_EXPLODE					1
#define SE_MELEEATTACKCOMBO_2_LAUNCH					2
#define SE_MELEEATTACKCOMBO_1_LAUNCH					3
#define MAX_SE_WEAPON									4

#define E_ENEMYATTACK_FLAMETHROWER	0
#define MAX_E_ENEMEYATTACK			1

#define ENEMY_ATTACK_RHAND		0
#define ENEMY_ATTACK_HEAD		1
#define ENEMY_ATTACK_MOUTH		2
#define ENEMY_ATTACK_LHAND		3
#define ENEMY_ATTACK_WINGS		4
#define ENEMY_ATTACK_WINGS_R	5

#define TEXTURE_STAFF				0
#define TEXTURE_BATTLESTAFF			1
#define TEXTURE_DROPPEDITEM			2
#define MAX_PRELOADED_TEXTURES_NUM	3

#define SB_DESERT	0
#define MAX_SB_NUM	1

#define ITEM_NORMAL			0
#define ITEM_RARE			1
#define ITEM_EPIC			2
#define ITEM_LEGENDARY		3
#define MAX_ITEM_RARITY_NUM	4

#define PLAYER_HIT_REACT_STAND		0
#define PLAYER_HIT_REACT_FLINCH		1
#define PLAYER_HIT_REACT_HITDOWN	2

#define INTERACT_BUTTON_MODE_NPCDIALOGUE	0
#define INTERACT_BUTTON_MODE_CLIMBROPE		1
#define INTERACT_BUTTON_MODE_JUMPPOINTS		2
#define INTERACT_BUTTON_MODE_PICKUPITEM		3

#define QUEST_NO_MATCH			UINT(0)
#define QUEST_ALREADY_HAVE		UINT(1)
#define QUEST_CLEARED			UINT(2)
#define QUEST_ALEARDY_CLEARED	UINT(3)
#define QUEST_UNQUALIFIED		UINT(4)

#define ITEM_TYPE_WEAPON	0
#define ITEM_TYPE_ARTIFACT	1
#define ITEM_TYPE_ARMOR		2
#define ITEM_TYPE_GOLD		3
#define ITEM_TYPE_GUITAR	4
#define ITEM_TYPE_POTION	5

struct AttackResult
{
	float StaminaUsed;
};

struct DELAY_START_PROJECTILE_CONFIGURE
{
	float AccCoefficient;
	float LaunchClock;
	float MaxSpeedCoefficient;
};

struct MonsterConfigure
{
	MonsterConfigure(
		class UDataTable* DropTable = nullptr,
		float HP = 100.f, float MaxHP = 100.f,
		float AttackDamage = 20.f, float MaxWalkSpeed = 350.f,
		float FlyAcc = 0.5f, float VirticalAcc = 120.f
	)
	{
		_DropTable = DropTable;
		_HP = HP;
		_MaxHP = MaxHP;
		_MaxWalkSpeed = MaxWalkSpeed;
		_AttackDamage = AttackDamage;
		_FlyAcc = FlyAcc;
		_VirticalAcc = VirticalAcc;
	}

	class UDataTable* _DropTable;
	float _HP;
	float _MaxHP;
	float _MaxWalkSpeed;
	float _AttackDamage;
	float _FlyAcc;
	float _VirticalAcc;
};

struct ItemStat
{
	ItemStat(
		float AttackDamage = 0.f,
		float Defence = 0.f,
		float AttackSpeed = 0.f,
		float HealPoint = 0.f
	)
	{
		_AttackDamage = AttackDamage;
		_Defence = Defence;
		_AttackSpeed = AttackSpeed;
		_HealPoint = HealPoint;
	}

	float _AttackDamage;
	float _Defence;
	float _AttackSpeed;
	float _HealPoint;
};