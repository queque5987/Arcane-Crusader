// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "IWeapon.h"
#include "CMonsterSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "IPlayerState.h"
#include "IPlayerQuest.h"
#include "QuestComponent.h" 
#include "Components/PointLightComponent.h"
#include "CPlayerCharacter.generated.h"

DECLARE_DELEGATE(FLMBAttack);
DECLARE_DELEGATE(FRMBCastStart);
DECLARE_DELEGATE(FRMBCastOnGoing);
DECLARE_DELEGATE(FMeleeAttackCombo);
DECLARE_DELEGATE(FMeleeAttackCombo1);
DECLARE_DELEGATE(FMeleeAttackCombo2);
DECLARE_DELEGATE(FMeleeAttackCombo3);
DECLARE_DELEGATE(FFinishAttack);
DECLARE_DELEGATE(FCombo1Attack);
DECLARE_DELEGATE(FCombo2Attack);
DECLARE_DELEGATE(FSheath);
DECLARE_DELEGATE(FDraw);
DECLARE_DELEGATE(FStandToRoll);
DECLARE_DELEGATE(FHitDown);
DECLARE_DELEGATE(FHitDownRecover);
DECLARE_DELEGATE(FDizzy);

DECLARE_DELEGATE(FJumpPointReady);
DECLARE_DELEGATE_OneParam(FJumpPointJump, float);
DECLARE_DELEGATE(FJumpPointLand);

DECLARE_DELEGATE_OneParam(FClimbingRope, bool);
DECLARE_DELEGATE(FDie);
DECLARE_DELEGATE(FHitReact);
DECLARE_DELEGATE(FPickUp);
DECLARE_DELEGATE(FDrink);

DECLARE_DELEGATE(FInventoryOpened);
DECLARE_DELEGATE(FFireRifle);
DECLARE_DELEGATE(FAimOff);
DECLARE_DELEGATE(FBulletChange);

DECLARE_DELEGATE(FInitiatePunchCombo);
DECLARE_DELEGATE_OneParam(FBruteRush0, bool);
DECLARE_DELEGATE(FFinishPunch);

DECLARE_DELEGATE_OneParam(FBrute_LMB_Combo, int32);

DECLARE_DELEGATE_OneParam(FBattleStaffUlt, bool);
DECLARE_DELEGATE(FRifleStaffUlt);
DECLARE_DELEGATE(FInwardSlash);
DECLARE_DELEGATE(FUnarmedJump);
DECLARE_DELEGATE(FUnarmedOnAir);
DECLARE_DELEGATE(FUltFinishPunch);
DECLARE_DELEGATE(FBackflip);
DECLARE_DELEGATE(FUltLand);

DECLARE_DELEGATE_TwoParams(FOverrideBoneTransform, int32, FRotator);

//DECLARE_DELEGATE(FPlayerDodged);

UCLASS()
class MMB_API ACPlayerCharacter : public ACharacter, public IIPlayerState, public IIPlayerQuest
{
	GENERATED_BODY()

public:
	ACPlayerCharacter();

	virtual void PostInitializeComponents() override;

	UPROPERTY(EditAnywhere)
	class UPointLightComponent* PointLight;

	UPROPERTY()
	class UInputAction* MoveAction;
	UPROPERTY()
	class UInputAction* LookAction;
	UPROPERTY()
	class UInputAction* JumpAction;
	UPROPERTY()
	class UInputAction* LMBAction;
	UPROPERTY()
	class UInputAction* RMBAction;
	UPROPERTY()
	class UInputAction* OpenInventory;
	UPROPERTY()
	class UInputAction* InteractAction;
	UPROPERTY()
	class UInputAction* ShiftAction;
	UPROPERTY()
	class UInputAction* AnyKeyAction;
	UPROPERTY()
	class UInputAction* ScrollAction;
	UPROPERTY()
	class UInputAction* ESCAction;
	UPROPERTY()
	class UInputAction* Quick1Action;
	UPROPERTY()
	class UInputAction* Quick2Action;
	UPROPERTY()
	class UInputAction* Quick3Action;
	UPROPERTY()
	class UInputAction* TabAction;
	UPROPERTY()
	class UInputAction* QAction;

	UPROPERTY()
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY()
	class UCameraComponent* CameraComponent;
	UPROPERTY()
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(BlueprintReadOnly)
	AActor* WeaponEquipped;

	UFUNCTION(BlueprintCallable)
	int32 GetEquippedWeaponType();

	virtual void StopAnimMontage(class UAnimMontage* AnimMontage = nullptr);

	// Anim Delegates
	FLMBAttack LMBAttack;
	FRMBCastStart RMBCastStart;
	FRMBCastOnGoing RMBCastOnGoing;
	FMeleeAttackCombo MeleeAttackCombo;
	FMeleeAttackCombo1 MeleeAttackCombo1;
	FMeleeAttackCombo2 MeleeAttackCombo2;
	FMeleeAttackCombo3 MeleeAttackCombo3;
	FFinishAttack FinishAttack;
	FCombo1Attack Combo1Attack;
	FCombo2Attack Combo2Attack;
	FSheath Sheath;
	FDraw Draw;
	FStandToRoll StandToRoll;
	FHitDown HitDown;
	FHitDownRecover HitDownRecover;
	FDizzy Dizzy;
	FClimbingRope ClimbingRope;
	FJumpPointReady JumpPointReady;
	FJumpPointJump JumpPointJump;
	FJumpPointLand JumpPointLand;
	FHitReact HitReact;
	FDie Die;
	FPickUp PickUp;
	FDrink Drink;
	FInventoryOpened InventoryOpenedEvent;
	FFireRifle FireRifle;
	FAimOff AimOff;
	FBulletChange BulletChange;

// Brute Rush
	FInitiatePunchCombo InitiatePunchCombo;
	FBruteRush0 BruteRush0;
	FFinishPunch FinishPunch;
//Brute Rush End
	FBrute_LMB_Combo Brute_LMB_Combo;

	FBattleStaffUlt BattleStaffUlt;
	FRifleStaffUlt RifleStaffUlt;
	FInwardSlash InwardSlash;
	FUnarmedJump UnarmedJump;
	FUnarmedOnAir UnarmedOnAir;
	FUltFinishPunch UltFinishPunch;
	FBackflip Backflip;
	FUltLand UltLand;

//Bone Transform Override
	FOverrideBoneTransform OverrideBoneTransform;
	class UParticleSystemComponent* ParticleSystemAimCircle;

	FVector DebugAimLocation;
	//typedef void (ACPlayerCharacter::* CallBackFunction)(ACPlayerCharacter&);
	//CallBackFunction LMBPressedPointer;
	//void (*LMBPressedPointer)(ACPlayerCharacter);

	//void testLMB(ACPlayerCharacter& PC);
	virtual void GetLineTraceResult(FHitResult& HitResult, float AttackRange) override;
	virtual bool GetDealingEnemyTransform(FTransform& OutTransform) override;

	UPROPERTY(BlueprintReadOnly)
	bool IsWeaponEquiped = false;
// Stage Material Access
	class IIStageMaterialManager* StageMaterialManager;
	//class USphereComponent* BWSphereComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* DodgeDom;

	bool PlayerInputCheck(int InputType = 0);

protected:
	virtual void BeginPlay() override;
	FVector StartPos;
	float SpineCapsuleDist;
	UQuestComponent* QuestComponent;

	UPROPERTY()
	float StaminaRegain;

	UPROPERTY(EditAnyWhere)
	float HP;
	float MaxHP;
	float Stamina;
	float MaxStamina;
	float ShiftStamina;
	UPROPERTY(EditAnyWhere)
	float UltGauge;
	UINT32 PlayerGold;
	float ClimbSpeed = 10.f;
	int32 BruteRushComboCounter = 0;
	class ACEnemyCharacter* LastDealingEnemy;

	FTimerHandle LastDealingEnemyTimerHandle;
	FTimerHandle HitReactTimerHandle;
	FTimerHandle HitDownRecoverHandle;
	FTimerHandle StaminaRegainHandle;
	FTimerHandle StageStartHandle;
	FTimerHandle PotionTimerHandle;
	FTimerHandle DodgeTimerHandle;

	void SetCanGetup();
	void Getup();
	void LazyGetUp();

	UUserWidget* HoverringUI;

	void SetAnimPauseFree() {
		GetMesh()->bPauseAnims = false;
	}
	UPROPERTY(EditAnyWhere)
	float DefaultMovementSpeed = 400.f;
	UPROPERTY(EditAnyWhere)
	float AccMovementSpeedAcc = 0.015f;
	UPROPERTY(EditAnyWhere)
	float MaxMoveMentSpeed = 800.f;

	bool bSecondDimentionalLocator;
	bool bUIControlling;
	float CastingClock;
	bool ContinueCombo;

	UINT32 State;
	UINT32 KeyState;

	bool bRMBCastDone;

	static const FName WeaponSocket;
	static const FName MeleeSocket;
	static const FName RifleSocket;
	static const FName tempRifleSocket;
	static const FName BackSocket;

	FName CurrentWeaponMode;

	//bool PlayerInputCheck(bool bBtn = true);
	UPROPERTY(VisibleAnywhere)
	FVector RevivalPos;
	void Revive(class ACPlayerController* PC);

	void OnWeaponChanged();
private:
	void UpdateHUDStates();
	bool CheckIsActing();
	void SetStaminaRegain();
	void OnDie();

	void OnDodgedAttack();
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;

// Movement
	virtual void OnOverlapEnemy(class ACharacter* EnemyChar) override;
	virtual void OnOverlapEndEnemy(class ACharacter* EnemyChar) override;
	void Move(const FInputActionValue& Value);
private:
	TArray<class ACharacter*> OverlapingCharacters;
	bool CheckIsAtCharacter(FVector Direction);
// Movement End

public:
	void StopMove(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void LMB();
	void LMBTriggered();
	void LMBCompleted();
	void RMBTriggered();
	void RMBCompleted();
	void InventoryOpened();
	void ShiftTriggered();
	void E_Triggered();
	void Anykey_Triggered();
	UFUNCTION()
	void Scroll(const FInputActionValue& Value);
	void ESC();
	void Quick1();
	void Quick2();
	void Quick3();
	void Tab();
	void QCompleted();
	void ItemUsageAction(int32 ItemType);
	virtual void Heal(float HealPoint) override;

	virtual void Equip(class ACWeapon& ActorToEquip) override;
	virtual void Equip(class AActor& ActorToEquip) override;
	virtual void UnEquip() override;
	virtual void SwitchBruteMode(bool BruteMode) override;
	//void Equip(TSubClassOf<AActor>& ActorToEquip);

	virtual float GetMaxHP() override { return MaxHP; }
	virtual void SetMaxHP(float NewMaxHP) override;
	virtual float GetMaxStamina() override { return MaxStamina; }
	virtual void SetMaxStamina(float NewMaxStamina) override;

	UFUNCTION()
	void OnMontageEnd(UAnimMontage* Montage, bool bInterrupted);

	/*void SetIsAttacking(bool b) { IsAttacking = b; }
	bool GetIsAttacking() { return IsAttacking; }*/
	virtual bool GetState(UINT StateType) override;
	virtual void SetState(UINT StateType, bool b) override;
	virtual bool GetKeyState(UINT StateType) override;
	virtual void SetKeyState(UINT StateType, bool b) override;
	virtual void SetHoverringUI(UUserWidget* UI) override;

	virtual UINT32 GetPlayerGold() override { return PlayerGold; }
	virtual void SetPlayerGold(UINT32 e) override;
	virtual void GainPlayerGold(UINT32 e) override;
	bool GetContinueCombo() { return ContinueCombo; }
	void SetContinueCombo(bool e) { ContinueCombo = e; }

	void SetbSecondDimentionalLocator(bool e) { bSecondDimentionalLocator = e; }
	bool GetbSecondDimentionalLocator() { return bSecondDimentionalLocator; }
	void SetDebugAimLocation(FVector e) { DebugAimLocation = e; }
	FVector GetDebugAimLocation() { return DebugAimLocation; }

	void ShowDamageUI(float Damage, FVector Location, bool IsAttacked = false);
	bool HitDamage(float e, class ACEnemyCharacter* Attacker, FVector HitLocation = FVector::ZeroVector, int Power = 0);
	void SetLastDealingEnemy(class ACEnemyCharacter* EC);
	UFUNCTION()
	void ResetLastDealingEnemy() { LastDealingEnemy = nullptr; }

	FVector GetMoveInputDesiredVector();
	FRotator GetMoveInputDesiredRotator();

	//void TransferToLevel(FName e);

	void AxisAdjustOnScreenRotation(float DeltaTime = 1/60);
	virtual void Grasped(class ACharacter& GraspedEnemyCharacter, FName GraspBoneName) override;
	virtual void UnGrasp() override;

	virtual void OnHitDown() override;
	virtual void StaminaSpend(float RequiredStamina) override;
	void MonsterKilledCount(class ACEnemyCharacter* MonsterKilled);
	void OnGraspRope(FTransform GraspLocation);
	void OnLooseRope();

	virtual void SetRevivalPoint(FVector Pos) override;
	virtual FVector GetRevivalPoint() override { return RevivalPos; };

	virtual void QuestClear(int e) override;
	virtual void QuestInitialize(int e) override;

	virtual void SetStartPos(FVector e) override;

	virtual float GetBonusAttackDamage() override;

	virtual void DealtDamage(float AttackDamage, float DamageScale, class ACharacter* TargetCharacter) override;

	virtual void FallToRevivalPoint(class AActor* AttachedCamera, float Damage = 0.f) override;

	virtual FTransform GetSocketTransform(FName SocketName) override;
// Weapon Effect
	virtual void WeaponEffectActivate() override;
	virtual void WeaponEffectDeactivate() override;
	virtual void SetWeaponEffectCharge(float e, bool IsLeft = false) override;
// Brute Mode
	virtual void BruteRushContinue() override;
	virtual bool IsBruteMode() override;
// Battle Staff Func
	virtual void ThrowStaffEffect() override;
	virtual void TurnBruteMode() override;
	virtual void Ult_ThrowStaffEffectDirect() override;
	virtual void Ult_Jump() override;
	virtual void Ult_PunchInit() override;
	virtual void Ult_Airbone() override;
	virtual void Ult_Land() override;
	virtual void Ult_HitGround() override;
	virtual void Ult_Backflip() override;
// Rifle Staff Func
	virtual void SwitchWeaponHoldingHand(bool ToLeft) override;
	virtual void SpawnAndGraspBeacon() override;
	virtual void ThrowBeacon() override;

	AActor* GetWeaponEquipped() { return WeaponEquipped; }

	float GetCameraArmLength();

};
