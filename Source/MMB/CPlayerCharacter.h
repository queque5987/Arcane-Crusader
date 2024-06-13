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
//#include "CPlayerController.h"
//#include "CPlayerAnimInstance.h"
//#include "Quest.h"
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
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY()
	class UCameraComponent* CameraComponent;
	UPROPERTY()
	class UInputMappingContext* DefaultMappingContext;
	AActor* WeaponEquipped;

	virtual void StopAnimMontage(class UAnimMontage* AnimMontage = nullptr);

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
	class UParticleSystemComponent* ParticleSystemAimCircle;

	FVector DebugAimLocation;
	//typedef void (ACPlayerCharacter::* CallBackFunction)(ACPlayerCharacter&);
	//CallBackFunction LMBPressedPointer;
	//void (*LMBPressedPointer)(ACPlayerCharacter);

	//void testLMB(ACPlayerCharacter& PC);
	void GetLineTraceResult(FHitResult& HitResult, float AttackRange);

	UPROPERTY(BlueprintReadOnly)
	bool IsWeaponEquiped = false;
protected:
	virtual void BeginPlay() override;
	FVector StartPos;

	UQuestComponent* QuestComponent;

	UPROPERTY()
	float StaminaRegain;

	UPROPERTY(EditAnyWhere)
	float HP;
	float MaxHP;
	float Stamina;
	float MaxStamina;
	float ShiftStamina;
	UINT32 PlayerGold;
	float ClimbSpeed = 10.f;
	class ACEnemyCharacter* LastDealingEnemy;
	FTimerHandle LastDealingEnemyTimerHandle;
	FTimerHandle HitReactTimerHandle;
	FTimerHandle HitDownRecoverHandle;
	FTimerHandle StaminaRegainHandle;
	FTimerHandle StageStartHandle;
	void SetCanGetup();
	void Getup();
	void LazyGetUp();

	UUserWidget* HoverringUI;

	void SetAnimPauseFree() {
		GetMesh()->bPauseAnims = false;
	}
	UPROPERTY(EditAnyWhere)
	float DefaultMovementSpeed = 500.f;
	UPROPERTY(EditAnyWhere)
	float AccMovementSpeedAcc = 0.05f;
	UPROPERTY(EditAnyWhere)
	float MaxMoveMentSpeed = 800.f;

	bool bSecondDimentionalLocator;
	bool bUIControlling;
	float CastingClock;
	bool ContinueCombo;

	UINT32 State;

	bool bRMBCastDone;

	static const FName WeaponSocket;
	static const FName MeleeSocket;

	FName CurrentWeaponMode;

	//bool PlayerInputCheck(bool bBtn = true);
	bool PlayerInputCheck(int InputType = 0);
	UPROPERTY(VisibleAnywhere)
	FVector RevivalPos;
	void Revive(class ACPlayerController* PC);
private:
	void UpdateHUDStates();
	bool CheckIsActing();
	void SetStaminaRegain();
	void OnDie();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;
	void Move(const FInputActionValue& Value);
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


	virtual void Equip(class ACWeapon& ActorToEquip) override;
	virtual void Equip(class AActor& ActorToEquip) override;
	virtual void UnEquip() override;
	//void Equip(TSubClassOf<AActor>& ActorToEquip);


	UFUNCTION()
	void OnMontageEnd(UAnimMontage* Montage, bool bInterrupted);

	/*void SetIsAttacking(bool b) { IsAttacking = b; }
	bool GetIsAttacking() { return IsAttacking; }*/
	virtual bool GetState(UINT StateType) override;
	virtual void SetState(UINT StateType, bool b) override;
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

	void OnHitDown();
	void StaminaSpend(float RequiredStamina);
	void MonsterKilledCount(class ACEnemyCharacter* MonsterKilled);
	void OnGraspRope(FTransform GraspLocation);
	void OnLooseRope();

	virtual void SetRevivalPoint(FVector Pos) override;
	virtual FVector GetRevivalPoint() override { return RevivalPos; };

	virtual void QuestClear(int e) override;
	virtual void QuestInitialize(int e) override;

	virtual void SetStartPos(FVector e) override;

	virtual float GetBonusAttackDamage() override;
	virtual void FallToRevivalPoint(class AActor* AttachedCamera, float Damage = 0.f) override;
};
