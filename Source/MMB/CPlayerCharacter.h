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
DECLARE_DELEGATE(FClimbingRope);
UCLASS()
class MMB_API ACPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayerCharacter();

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
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY()
	class UCameraComponent* CameraComponent;
	UPROPERTY()
	class UInputMappingContext* DefaultMappingContext;
	//UPROPERTY(BlueprintReadOnly)
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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	float StaminaRegain;

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
	void SetCanGetup();
	void Getup();
	void LazyGetUp();

	void SetAnimPauseFree() {
		GetMesh()->bPauseAnims = false;
	}

	//bool IsAttacking;
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

private:
	void UpdateHUDStates();
	bool CheckIsActing();
	void SetStaminaRegain();
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

	void Equip(class ACWeapon& ActorToEquip);
	void Equip(class AActor& ActorToEquip);
	//void Equip(TSubClassOf<AActor>& ActorToEquip);


	UFUNCTION()
	void OnMontageEnd(UAnimMontage* Montage, bool bInterrupted);

	/*void SetIsAttacking(bool b) { IsAttacking = b; }
	bool GetIsAttacking() { return IsAttacking; }*/
	bool GetState(UINT StateType);
	void SetState(UINT StateType, bool b);
	UINT32 GetPlayerGold() { return PlayerGold; }
	void SetPlayerGold(UINT32 e);
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

	void TransferToLevel(FName e);

	void AxisAdjustOnScreenRotation(float DeltaTime = 1/60);

	void OnHitDown(bool OnLazyGetUp = false);
	void StaminaSpend(float RequiredStamina);
	void MonsterKilledCount(TSubclassOf<class ACEnemyCharacter> MonsterClass);
};
