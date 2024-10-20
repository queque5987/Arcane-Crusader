#pragma once

#include "MMBGameModeBase.h"
#include "CPlayerController.h"
#include "CPlayerCharacter.h"
#include "CPlayerAnimInstance.h"
#include "CWeapon.h"
#include "CBattleStaff.h"
#include "CRifleStaff.h"
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

//Player State
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

#define PLAYER_DODGED				UINT(1) << 12
#define PLAYER_BS_ESCAPE_COMBO_TAB	UINT(1) << 13
//#define PLAYER_BS_JUMP_UP			UINT(1) << 14
//#define PLAYER_INPUT_TYPE_JUMP		UINT(1) << 15

//#define PLAYER_INPUT_TYPE_MOVE		UINT(1) << 16
#define PLAYER_COMBO_STACK_1		UINT(1) << 17
#define PLAYER_COMBO_STACK_2		UINT(1) << 18
#define PLAYER_COMBO_STACK_3		UINT(1) << 19

#define PLAYER_GETTINGUP			UINT(1) << 20
#define PLAYER_STAMINA_REGAIN		UINT(1) << 21
#define PLAYER_DIED					UINT(1) << 22
#define PLAYER_DRINKING_POTION		UINT(1) << 23

#define PLAYER_CLIMBING_ROPE		UINT(1) << 24
#define PLAYER_JUMPING_POINTS		UINT(1) << 25
#define PLAYER_AIMING				UINT(1) << 26
#define PLAYER_DIZZY				UINT(1) << 27

#define PLAYER_INVENTORY_HOVERRING	UINT(1) << 28
#define	PLAYER_BRUTEMODE_ORAORA		UINT(1) << 29
#define PLAYER_BRUTEMODE_COMBO_IN	UINT(1) << 30
#define PLAYER_ULT_INVINCIBLE		UINT(1) << 31

//Player Pressing Key
#define PLAYER_INPUT_LMB			UINT(1) << 0
#define PLAYER_INPUT_RMB			UINT(1) << 1

//Player Input Type Overall Check
#define PLAYER_INPUT_TYPE_CLICK		UINT(1) << 2
#define PLAYER_INPUT_TYPE_SHIFT		UINT(1) << 3

#define PLAYER_INPUT_TYPE_LOOK		UINT(1) << 4
#define PLAYER_INPUT_TYPE_JUMP		UINT(1) << 5
#define PLAYER_INPUT_TYPE_MOVE		UINT(1) << 6

//Player Bone Index
#define PLAYER_MESH_BONE_SPINE1		0
#define PLAYER_MESH_BONE_SPINE2		1


#define EnemyAttackChannel		ECollisionChannel::ECC_EngineTraceChannel1
#define PlayerAttackChannel		ECollisionChannel::ECC_EngineTraceChannel2

//BattleStaff Effect
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
#define E_ULT_HITGROUND									15
#define E_ULT_HITGROUND_BIG								16
#define E_ULT_JUMP										17
#define E_ULT_JUMP_AIR									18
#define E_BRUTEMODE_INIT								19
#define E_BRUTEMODE_INIT_LIGHTNING						20
#define E_BRUTEMODE_INIT_LIGHTNING_BIG					21
#define E_BRUTEMODE_FIST_LIGHTNING						22
#define E_BRUTEMODE_FIST_HIT_EFFECT						23

//RifleStaff Effect
#define E_RIFLE_TYPE_A_PROJECTILE						1
#define E_RIFLE_SPAWN_EFFECT							2
#define E_RIFLE_EXPLODE_EFFECT							3
#define E_RIFLE_LAUNCH_EFFECT							4
#define E_RIFLE_ULT_EXPLODE_EFFECT						5

#define MAX_E_WEAPONEFFECT								24
//BattleStaff Sound Effect
#define SE_MELEEATTACKCOMBO_3_EXPLODE					0
#define SE_MELEEATTACKCOMBO_2_EXPLODE					1
#define SE_MELEEATTACKCOMBO_2_LAUNCH					2
#define SE_MELEEATTACKCOMBO_1_LAUNCH					3
#define SE_ULT_HITGROUND_A								4
#define SE_ULT_HITGROUND_B								4
//RifleStaff Sound Effect
#define SE_RIFLE_TYPE_A_CHARGE	0
#define SE_RIFLE_TYPE_A_SHOT	1
#define SE_RIFLE_TYPE_A_Hit		2
#define SE_RIFLE_TYPE_B_SHOT	3
#define MAX_SE_WEAPON									5

#define E_ENEMYATTACK_FLAMETHROWER	0
#define E_ENEMYATTACK_FIREBALL		1
#define E_ENEMYATTACK_FIREBALL_EXPLODE	2
#define E_ENEMYATTACK_ATTACK_CHARGE	3
#define MAX_E_ENEMEYATTACK			4

#define ENEMY_ATTACKING			UINT(1) << 0
#define ENEMY_HOSTILE			UINT(1) << 1
#define ENEMY_DYING				UINT(1) << 2
#define ENEMY_RAGDOLL			UINT(1) << 3

#define ENEMY_ATTACK_RHAND		0
#define ENEMY_ATTACK_RHAND_E	1
#define ENEMY_ATTACK_HEAD		2
#define ENEMY_ATTACK_HEAD_E		3
#define ENEMY_ATTACK_MOUTH		4
#define ENEMY_ATTACK_MOUTH_E	5
#define ENEMY_ATTACK_LHAND		6
#define ENEMY_ATTACK_LHAND_E	7
#define ENEMY_ATTACK_WINGS		8
#define ENEMY_ATTACK_WINGS_E	9
#define ENEMY_ATTACK_WINGS_R	10
#define ENEMY_ATTACK_WINGS_R_E	11
#define ENEMY_ATTACK_TURN_L		12

#define ENEMY_ATTACK_TURN_R		14

#define ENEMY_ATTACK_BONE_NUM	16

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

#define RGB_NORMAL		FVector(1.f, 0.962442f, 0.99769f)
#define RGB_RARE		FVector(0.176293f, 0.559561f, 1.f)
#define RGB_EPIC		FVector(0.47264f, 0.f, 0.734375f)
#define RGB_LEGENDARY	FVector(1.f, 0.610103f, 0.268382f)

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

#define QUEST_ACHEIEVED_ACTION_DEFAULT		0
#define QUEST_ACHEIEVED_ACTION_EQUIP		1
#define QUEST_ACHEIEVED_ACTION_USE			2
#define QUEST_ACHEIEVED_ACTION_INTERACT		3

#define ITEM_TYPE_WEAPON	0
#define ITEM_TYPE_ARTIFACT	1
#define ITEM_TYPE_ARMOR		2
#define ITEM_TYPE_GOLD		3
#define ITEM_TYPE_GUITAR	4
#define ITEM_TYPE_POTION	5

#define RIFLESTAFF_BULLET_RIFLE			0
#define RIFLESTAFF_BULLET_SHOTGUN		1
#define RIFLESTAFF_BULLET_MACHINEGUN	2

struct AttackResult
{
	float StaminaUsed;
	bool Succeeded;
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
		UClass* MonsterClass = nullptr,
		class UDataTable* DropTable = nullptr,
		float HP = 100.f, float MaxHP = 100.f,
		float AttackDamage = 20.f, float MaxWalkSpeed = 350.f,
		float FlyAcc = 0.5f, float VirticalAcc = 120.f
	)
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

	UClass* _MonsterClass;
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