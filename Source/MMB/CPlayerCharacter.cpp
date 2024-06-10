// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerCharacter.h"
#include "IWidgetInteract.h"
#include "PCH.h"
#include "Engine/LevelStreaming.h"
#include "IFlyMonster.h"

const FName ACPlayerCharacter::WeaponSocket(TEXT("WeaponSocket"));
const FName ACPlayerCharacter::MeleeSocket(TEXT("MeleeSocket"));

ACPlayerCharacter::ACPlayerCharacter()
{
	WeaponEquipped = nullptr;
	//IsAttacking = false;
	bRMBCastDone = false;
	bUIControlling = false;
	CastingClock = -1.f;
	State = 0;//1073741832;
	PlayerGold = 100;
	HP = 100;
	MaxHP = 100;
	Stamina = 0;
	MaxStamina = 100;
	ShiftStamina = 4.f;
	StaminaRegain = 12.f;
	LastDealingEnemy = nullptr;

	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCFinder(TEXT("/Game/Player/Input/IMC_Default"));
	ConstructorHelpers::FObjectFinder<UInputAction> MoveFinder(TEXT("/Game/Player/Input/IA_Move"));
	ConstructorHelpers::FObjectFinder<UInputAction> LookFinder(TEXT("/Game/Player/Input/IA_Look"));
	ConstructorHelpers::FObjectFinder<UInputAction> JumpFinder(TEXT("/Game/Player/Input/IA_Jump"));
	ConstructorHelpers::FObjectFinder<UInputAction> LMBFinder(TEXT("/Game/Player/Input/IA_LMB"));
	ConstructorHelpers::FObjectFinder<UInputAction> RMBFinder(TEXT("/Game/Player/Input/IA_RMB"));
	ConstructorHelpers::FObjectFinder<UInputAction> OpenInventoryFinder(TEXT("/Game/Player/Input/IA_Inventory"));
	ConstructorHelpers::FObjectFinder<UInputAction> ShiftFinder(TEXT("/Game/Player/Input/IA_Shift"));
	ConstructorHelpers::FObjectFinder<UInputAction> InteractFinder(TEXT("/Game/Player/Input/IA_Interact"));
	ConstructorHelpers::FObjectFinder<UInputAction> AnyKeyFinder(TEXT("/Game/Player/Input/IA_Any"));
	ConstructorHelpers::FObjectFinder<UInputAction> ScrollFinder(TEXT("/Game/Player/Input/IA_Scroll"));
	ConstructorHelpers::FObjectFinder<UInputAction> ESCFinder(TEXT("/Game/Player/Input/IA_ESC"));

	if (IMCFinder	.Succeeded()) DefaultMappingContext = IMCFinder.Object;
	if (MoveFinder	.Succeeded()) MoveAction = MoveFinder.Object;
	if (LookFinder	.Succeeded()) LookAction = LookFinder.Object;
	if (JumpFinder	.Succeeded()) JumpAction = JumpFinder.Object;
	if (LMBFinder	.Succeeded()) LMBAction = LMBFinder.Object;
	if (RMBFinder	.Succeeded()) RMBAction = RMBFinder.Object;
	if (OpenInventoryFinder.Succeeded()) OpenInventory = OpenInventoryFinder.Object;
	if (ShiftFinder.Succeeded()) ShiftAction = ShiftFinder.Object;
	if (InteractFinder.Succeeded()) InteractAction = InteractFinder.Object;
	if (AnyKeyFinder.Succeeded()) AnyKeyAction = AnyKeyFinder.Object;
	if (ScrollFinder.Succeeded()) ScrollAction = ScrollFinder.Object;
	if (ESCFinder.Succeeded()) ESCAction = ESCFinder.Object;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	//SpringArmComponent->SetUsingAbsoluteRotation(false);
	/*SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->AddRelativeRotation(FRotator(-25.f, 0.f, 0.f));*/
	SpringArmComponent->TargetArmLength = 550.f;
	//SpringArmComponent->SetRelativeLocation(FVector(0.f, 75.f, 100.f));
	SpringArmComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	//SpringArmComponent->SetRelativeTransform(FTransform(FRotator(0.f, -15.f, 0.f), FVector(0.f, 0.f, 0.f)));
	SpringArmComponent->bUsePawnControlRotation = true;
	//SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->SetupAttachment(GetCapsuleComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	//ConstructorHelpers::FObjectFinder<USkeletalMesh> SMWizard(TEXT("/Game/BattleWizardPolyart/Meshes/WizardSM.WizardSM"));
	//if (SMWizard.Succeeded()) GetMesh()->SetSkeletalMesh(SMWizard.Object);
	//GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -87.f), FRotator(0.f, -90.f, 0.f));
	//ConstructorHelpers::FObjectFinder<UAnimBlueprint> SMWizrdAnimBPFinder(TEXT("/Game/Player/Animation/BP_AnimInstance.BP_AnimInstance"));
	//GetMesh()->SetAnimClass(SMWizrdAnimBPFinder.Object->GeneratedClass);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> SMKnightMage(TEXT("/Game/Player/Guard/castle_guard_01"));
	if (SMKnightMage.Succeeded()) GetMesh()->SetSkeletalMesh(SMKnightMage.Object);

	//ConstructorHelpers::FClassFinder<UAnimBlueprint> SMKnightMageAnimBPFinder(TEXT("/Game/Player/Guard/Animation/BP_AnimInstance_Guard"));
	//ConstructorHelpers::FObjectFinder<UAnimBlueprint> SMKnightMageAnimBPFinder(TEXT("AnimBlueprint'/Game/Player/Guard/Animation/BP_AnimInstance_Guard'"));
	//if (SMKnightMageAnimBPFinder.Succeeded()) GetMesh()->SetAnimClass(SMKnightMageAnimBPFinder.Object->GeneratedClass);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -87.f), FRotator(0.f, -90.f, 0.f));

	//SetActorRelativeScale3D(FVector(1.3f, 1.3f, 1.3f));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->bEnablePhysicsInteraction = 0;
	GetCharacterMovement()->MaxStepHeight = 80.f;
	GetCharacterMovement()->JumpZVelocity = 550.f;
	GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed;

	ParticleSystemAimCircle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("CircleAim"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleFinder(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/Fire/combat/P_AuraCircle_Fire_00"));
	if (ParticleFinder.Succeeded()) ParticleSystemAimCircle->SetTemplate(ParticleFinder.Object);
	ParticleSystemAimCircle->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.7f));
	ParticleSystemAimCircle->SetVisibility(false);
	//ParticleSystemAimCircle->Deactivate();

	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//LMBPressedPointer = &ACPlayerCharacter::testLMB;
	GetCapsuleComponent()->SetCollisionResponseToChannel(EnemyAttackChannel, ECollisionResponse::ECR_Overlap);
	GetCapsuleComponent()->SetCollisionResponseToChannel(PlayerAttackChannel, ECollisionResponse::ECR_Block);

	QuestComponent = CreateDefaultSubobject<UQuestComponent>(TEXT("QuestComponent"));
}

void ACPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	/// Script / Engine.AnimBlueprint'/Game/Player/Guard/Animation/BPAnimInstanceGuard.BPAnimInstanceGuard'
	//FString AnimBPAdderss = "Class'/Game/Player/Guard/Animation/BP_AnimInstance_Guard.BP_AnimInstance_Guard_C'";
	//UBlueprintGeneratedClass* tempAnimBP = LoadObject<UBlueprintGeneratedClass>(nullptr, *AnimBPAdderss);
	FString AnimBPAdderss = "Class'/Game/Player/Guard/Animation/BPAnimInstanceGuard.BPAnimInstanceGuard_C'";
	UClass* tempAnimBP = LoadObject<UClass>(nullptr, *AnimBPAdderss);
	if (!tempAnimBP) return;
	GetMesh()->SetAnimInstanceClass(tempAnimBP);
}

void ACPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (ACPlayerController* PC = Cast<ACPlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (StartPos != FVector::ZeroVector)
	{
		SetActorLocation(StartPos);
	}

	GetWorld()->GetTimerManager().SetTimer(StageStartHandle, FTimerDelegate::CreateLambda([&] {
		bool Flag = true;
		for (ULevelStreaming* LS : GetWorld()->GetStreamingLevels())
		{
			if (LS != nullptr && !LS->IsLevelLoaded())
			{
				Flag = false;
				break;
			}
		}
		if (Flag)
		{
			UE_LOG(LogTemp, Log, TEXT("Loaded"));
			GetWorld()->GetTimerManager().ClearTimer(StageStartHandle);
		}
		else UE_LOG(LogTemp, Log, TEXT("Loading"));
		}), 0.1f, true
	);
}

void ACPlayerCharacter::SetCanGetup()
{
	SetState(PLAYER_RAGDOLL, true);
	SetState(PLAYER_CANGETUP, true);
	//GetWorld()->GetTimerManager().SetTimer(HitDownRecoverHandle, this, &ACPlayerCharacter::LazyGetUp, 1.5f);
}

void ACPlayerCharacter::Getup()
{
	if (GetState(PLAYER_RAGDOLL) && GetState(PLAYER_CANGETUP))
	{
		OnHitDown();
		GetWorld()->GetTimerManager().ClearTimer(HitDownRecoverHandle);
	}
}

void ACPlayerCharacter::LazyGetUp()
{
	if (GetState(PLAYER_RAGDOLL) && GetState(PLAYER_CANGETUP))
	{
		OnHitDown();
		SetState(PLAYER_GETTINGUP, true);
		HitDownRecover.ExecuteIfBound();
		GetWorld()->GetTimerManager().ClearTimer(HitDownRecoverHandle);
	}
}

void ACPlayerCharacter::StopAnimMontage(UAnimMontage* AnimMontage)
{
	Super::StopAnimMontage(AnimMontage);

	SetState(PLAYER_ATTACKING,			false);
	SetState(PLAYER_COMBO_STACK_1,		false);
	SetState(PLAYER_COMBO_STACK_2,		false);
	SetState(PLAYER_COMBO_STACK_3,		false);
	SetState(PLAYER_ROLLING,			false);
	SetState(PLAYER_ROLL_INVINCIBLE,	false);
	SetState(PLAYER_CANGETUP,			false);
	SetState(PLAYER_GETTINGUP,			false);
	SetState(PLAYER_STAMINA_RUNOUT,		false);
}

void ACPlayerCharacter::GetLineTraceResult(FHitResult& HitResult, float AttackRange)
{
	FVector StartLocation = CameraComponent->GetComponentLocation() + GetBaseAimRotation().Vector() * 550.f; //Spring Arm Length;
	FVector EndLocation = StartLocation + GetBaseAimRotation().Vector() * AttackRange;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Pawn))
	{
		UE_LOG(LogTemp, Log, TEXT("Line Trace ActorName : %s"), *HitResult.GetActor()->GetName());	
	}
}

void ACPlayerCharacter::OnMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	if (CastingClock >= 1.2f)
	{
		RMBCastOnGoing.Execute();
		bSecondDimentionalLocator = false;
		CastingClock = -1.f;
		FVector SpawnLocation = DebugAimLocation + FVector(0.f, 0.f, 1000.f);
		//GetWorld()->SpawnActor<ACMeteor>(ACMeteor::StaticClass(), SpawnLocation, FRotator::ZeroRotator);
	}
}

bool ACPlayerCharacter::PlayerInputCheck(int InputType)
{
	bool UICheck = !GetState(PLAYER_UI_INTERACTING);
	bool Standing = (!GetState(PLAYER_RAGDOLL) && !GetState(PLAYER_CANGETUP));
	bool GroundedButCanGetUp = GetState(PLAYER_CANGETUP) && GetState(PLAYER_RAGDOLL);
	bool notGettingUp = !GetState(PLAYER_GETTINGUP);
	bool notStaminaRunout = !GetState(PLAYER_STAMINA_RUNOUT);
	bool notClimbing = !GetState(PLAYER_CLIMBING_ROPE) && !GetState(PLAYER_JUMPING_POINTS); // or jumping
	bool notDead = !GetState(PLAYER_DIED);

	switch (InputType)
	{
	case(PLAYER_INPUT_TYPE_SHIFT):
		if (notDead) Getup();
		else Anykey_Triggered();
		return notDead && UICheck && (Standing || GroundedButCanGetUp) && notStaminaRunout && notClimbing;
		break;
	case(PLAYER_INPUT_TYPE_LOOK):
		return UICheck;
		break;
	case(PLAYER_INPUT_TYPE_CLICK):
		//if (notDead) LazyGetUp();
		//else Anykey_Triggered();
		//return notDead && UICheck && Standing && notGettingUp && notStaminaRunout && notClimbing;
		//break;
	case(PLAYER_INPUT_TYPE_JUMP):
		//if (notDead) LazyGetUp();
		//else Anykey_Triggered();
		//return notDead && UICheck && Standing && notGettingUp && notStaminaRunout && notClimbing;
		//break;
	case(PLAYER_INPUT_TYPE_MOVE):
		if (notDead) LazyGetUp();
		else Anykey_Triggered();
		return notDead && UICheck && Standing && notGettingUp && notStaminaRunout && notClimbing;
		break;
	default:
		return false;
	}
}

void ACPlayerCharacter::Revive(ACPlayerController* PC)
{
	GetWorld()->GetTimerManager().SetTimer(HitReactTimerHandle, FTimerDelegate::CreateLambda([&]() {
		SetState(PLAYER_GETTINGUP, false);
		}), 6.4f, false);
	SetActorLocation(RevivalPos);
	SetAnimPauseFree();
	SetState(PLAYER_DIED, false);
	SetState(PLAYER_GETTINGUP, true);
	PC->CharacterDied(false);
	HP = MaxHP;
}

void ACPlayerCharacter::UpdateHUDStates()
{
	if (ACPlayerController* PCC = Cast<ACPlayerController>(GetController()))
	{
		if (PCC->HUDOverlay->GetVisibility() == ESlateVisibility::Visible)
		{
			PCC->HUDOverlay->HPBar->SetPercent(HP / MaxHP);
			PCC->HUDOverlay->StaminaBar->SetPercent(Stamina / MaxStamina);
			//FProgressBarStyle Style = PCC->HUDOverlay->StaminaBar->GetWidgetStyle();
			//FSlateBrush Brush = Style.FillImage;
			////Brush.
			//PCC->HUDOverlay->StaminaBar->SetWidgetStyle(FProgressBarStyle());

			if (LastDealingEnemy != nullptr)
			{
				PCC->HUDOverlay->EnemyHPBar->SetPercent(LastDealingEnemy->GetHP()/ LastDealingEnemy->GetMaxHP());
				PCC->HUDOverlay->EnemyHPBar->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				PCC->HUDOverlay->EnemyHPBar->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

bool ACPlayerCharacter::CheckIsActing()
{
	return GetState(PLAYER_ATTACKING); //|| GetState(PLAYER_ROLLING);
}

void ACPlayerCharacter::SetStaminaRegain()
{
	SetState(PLAYER_STAMINA_REGAIN, true);
}

void ACPlayerCharacter::OnDie()
{
	//if (Die.ExecuteIfBound()) SetState(PLAYER_DIED, true);
	StopAnimMontage();
	SetState(PLAYER_DIED, true);
	ACPlayerController* PC = Cast<ACPlayerController>(GetController());
	if (!IsValid(PC)) return;
	PC->CharacterDied(true);
	//GetWorld()->GetTimerManager().ClearTimer(HitReactTimerHandle);
	//GetWorld()->GetTimerManager().SetTimer(HitReactTimerHandle,
	//	FTimerDelegate::CreateLambda([&]() {
	//		GetMesh()->bPauseAnims = true;
	//	}), 3.5f, false
	//);
}

void ACPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetState(PLAYER_DIED) && HP <= 0.f)
	{
		OnDie();
	}

	if (CastingClock >= 0)
	{
		CastingClock += DeltaTime;
	}

// CHANGE CHARACTER DIRECTION MATCH THE CAMERA PERSPECTIVE WHILE ATTACKING
	if (GetState(PLAYER_ATTACKING)) AxisAdjustOnScreenRotation(DeltaTime);

// STAMINA REGAIN
	if (!CheckIsActing() && !GetWorld()->GetTimerManager().TimerExists(StaminaRegainHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(StaminaRegainHandle, this, &ACPlayerCharacter::SetStaminaRegain, 1.6f);
	}
	else if (CheckIsActing())
	{
		GetWorld()->GetTimerManager().ClearTimer(StaminaRegainHandle);
		SetState(PLAYER_STAMINA_REGAIN, false);
	}
	if (
		Stamina < MaxStamina && 
		GetState(PLAYER_STAMINA_REGAIN) && 
		!GetState(PLAYER_STAMINA_RUNOUT) &&
		!GetState(PLAYER_ROLLING)
		) Stamina += StaminaRegain * DeltaTime;
	if (Stamina > MaxStamina) Stamina = MaxStamina;

// STAMINA RUNOUT
	if (Stamina < 0.f) Stamina = 0.f;
	if (GetState(PLAYER_STAMINA_RUNOUT)) Stamina += StaminaRegain * DeltaTime * 1.3f;

// HUD UPDATE
	UpdateHUDStates();

// IN RAGDOLL CAMERA TO FOLLOW STATICMESH
	if (GetState(PLAYER_RAGDOLL))
	{
		FTransform RT = GetCapsuleComponent()->GetRelativeTransform();
		RT.SetLocation(GetMesh()->GetRelativeTransform().GetLocation() + FVector(0.f, 0.f, 80.f));
		GetCapsuleComponent()->SetRelativeTransform(RT);
	}

// IF ENEMY FLYING -> SET CAMERA HIGHER
	if (LastDealingEnemy != nullptr && LastDealingEnemy->GetClass()->ImplementsInterface(UIFlyMonster::StaticClass()))
	{
		IIFlyMonster* FlyableMonster = Cast<IIFlyMonster>(LastDealingEnemy);
		FVector tempPos = CameraComponent->GetRelativeLocation();
		if (FlyableMonster->GetIsFlying())
		{
			tempPos.Z += 180.f * DeltaTime;
			if (tempPos.Z > 200.f) tempPos.Z = 300.f;
			CameraComponent->SetRelativeLocation(tempPos);
		}
		else
		{
			tempPos.Z -= 180.f * DeltaTime;
			if (tempPos.Z < 0.f) tempPos.Z = 0.f;
			CameraComponent->SetRelativeLocation(tempPos);
		}
	}
}

void ACPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ACPlayerCharacter::StopMove);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(LMBAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::LMBTriggered);
		EnhancedInputComponent->BindAction(LMBAction, ETriggerEvent::Completed, this, &ACPlayerCharacter::LMBCompleted);
		EnhancedInputComponent->BindAction(RMBAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::RMBTriggered);
		EnhancedInputComponent->BindAction(RMBAction, ETriggerEvent::Completed, this, &ACPlayerCharacter::RMBCompleted);
		EnhancedInputComponent->BindAction(OpenInventory, ETriggerEvent::Completed, this, &ACPlayerCharacter::InventoryOpened);
		EnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::ShiftTriggered);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::E_Triggered);
		EnhancedInputComponent->BindAction(ScrollAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Scroll);
		EnhancedInputComponent->BindAction(ESCAction, ETriggerEvent::Completed, this, &ACPlayerCharacter::ESC);
	}
}

void ACPlayerCharacter::Jump()
{
	return;
	Super::Jump();
}

void ACPlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	SetState(PLAYER_INPUT_W, MovementVector.Y > 0 ? true: false);
	SetState(PLAYER_INPUT_S, MovementVector.Y < 0 ? true : false);
	SetState(PLAYER_INPUT_D, MovementVector.X > 0 ? true : false);
	SetState(PLAYER_INPUT_A, MovementVector.X < 0 ? true : false);

	if (GetState(PLAYER_ATTACKING) || GetState(PLAYER_ROLLING)) return;

	if (GetState(PLAYER_CLIMBING_ROPE))
	{
		ACPlayerController* PC = Cast<ACPlayerController>(GetController());
		if (PC == nullptr) return;
		GetMovementComponent()->StopMovementImmediately();

		bool IsArrived;
		if (GetState(PLAYER_INPUT_W))
		{
			GetMesh()->bPauseAnims = false;
			FVector CurrLocation = GetActorLocation();
			CurrLocation.Z += ClimbSpeed;
			PC->ClimbRopeInteract_Move(CurrLocation, IsArrived, true);
			//UE_LOG(LogTemp, Log, TEXT("PlayerCharacter : Current Location : %s"), *GetActorLocation().ToString());
			SetActorLocation(CurrLocation);
			if (IsArrived) OnLooseRope();
			return;
		}
		else if (GetState(PLAYER_INPUT_S))
		{
			GetMesh()->bPauseAnims = false;
			FVector CurrLocation = GetActorLocation();
			CurrLocation.Z -= ClimbSpeed;
			PC->ClimbRopeInteract_Move(CurrLocation, IsArrived, false);
			SetActorLocation(CurrLocation);
			if (IsArrived) OnLooseRope();
			//UE_LOG(LogTemp, Log, TEXT("PlayerCharacter : Setting Location : %s"), *NextTickLocation.ToString());
			return;
		}
	}

	if (Controller != nullptr && PlayerInputCheck(PLAYER_INPUT_TYPE_MOVE))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

		float TempSpeed = GetCharacterMovement()->MaxWalkSpeed * (1 + AccMovementSpeedAcc);
		if (MaxMoveMentSpeed >= TempSpeed) GetCharacterMovement()->MaxWalkSpeed = TempSpeed;
	}
}

void ACPlayerCharacter::StopMove(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped / Reseting move input states"));

	SetState(PLAYER_INPUT_W, false);
	SetState(PLAYER_INPUT_A, false);
	SetState(PLAYER_INPUT_S, false);
	SetState(PLAYER_INPUT_D, false);

	if (GetState(PLAYER_CLIMBING_ROPE))
	{
		GetMesh()->bPauseAnims = true;
	}

	GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed;
}

void ACPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (PlayerInputCheck(PLAYER_INPUT_TYPE_LOOK) && Controller != nullptr)
	{
		if (!bSecondDimentionalLocator)
		{
			AddControllerYawInput(-LookAxisVector.X);
			AddControllerPitchInput(LookAxisVector.Y);
		}
		else
		{
			FVector NewAimVector = GetBaseAimRotation().RotateVector(FVector::ForwardVector);
			NewAimVector -= FVector(0.f, 0.f, NewAimVector.Z);
			FRotator SecondDimensionalAim = NewAimVector.Rotation();
			FVector NewLocation = SecondDimensionalAim.RotateVector(FVector(-LookAxisVector.Y*12, -LookAxisVector.X*12, 0.f));
			DebugAimLocation += NewLocation;
		}
	}
}

void ACPlayerCharacter::LMB()
{
	if (PlayerInputCheck(PLAYER_INPUT_TYPE_CLICK))
	{
		if (WeaponEquipped != nullptr)
		{
			//(this->*LMBPressedPointer)(*this);
			if (IIWeapon * IWeaponEquipped = Cast<IIWeapon>(WeaponEquipped)) IWeaponEquipped->LMB_Attack();
		}
	}
}

void ACPlayerCharacter::LMBTriggered()
{
	if (PlayerInputCheck(PLAYER_INPUT_TYPE_CLICK))
	{
		if (WeaponEquipped != nullptr)
		{
			//(this->*LMBPressedPointer)(*this);
			AttackResult AR = AttackResult();
			if (IIWeapon* IWeaponEquipped = Cast<IIWeapon>(WeaponEquipped)) IWeaponEquipped->LMB_Triggered(AR);
			StaminaSpend(AR.StaminaUsed);
		}
	}
}

void ACPlayerCharacter::LMBCompleted()
{
	if (PlayerInputCheck(PLAYER_INPUT_TYPE_CLICK))
	{
		if (WeaponEquipped != nullptr)
		{
			//(this->*LMBPressedPointer)(*this);
			AttackResult AR = AttackResult();
			if (IIWeapon* IWeaponEquipped = Cast<IIWeapon>(WeaponEquipped)) IWeaponEquipped->LMB_Completed(AR);
			StaminaSpend(AR.StaminaUsed);
		}
	}
}

void ACPlayerCharacter::RMBTriggered()
{
	if (PlayerInputCheck(PLAYER_INPUT_TYPE_CLICK))
	{
		if (WeaponEquipped != nullptr)
		{
			AttackResult AR = AttackResult();
			if (IIWeapon* IWeaponEquipped = Cast<IIWeapon>(WeaponEquipped)) IWeaponEquipped->RMB_Triggered(AR);
			StaminaSpend(AR.StaminaUsed);
			//Stamina -= AR.StaminaUsed;
		}
	}
}

void ACPlayerCharacter::RMBCompleted()
{
	if (PlayerInputCheck(PLAYER_INPUT_TYPE_CLICK))
	{
		if (WeaponEquipped != nullptr)
		{
			AttackResult AR = AttackResult();
			if (IIWeapon* IWeaponEquipped = Cast<IIWeapon>(WeaponEquipped)) IWeaponEquipped->RMB_Completed(AR);
			StaminaSpend(AR.StaminaUsed);
			//Stamina -= AR.StaminaUsed;
		}
	}
	if (GetState(PLAYER_UI_INTERACTING))
	{
		if (HoverringUI == nullptr) return;
		IIWidgetInteract* IWidget = Cast<IIWidgetInteract>(HoverringUI);
		if (IWidget == nullptr) return;
		IWidget->OnRightClicked();
	}
}

void ACPlayerCharacter::InventoryOpened()
{
	if (ACPlayerController* PC = Cast<ACPlayerController>(GetController()))
	{
		if (PC->SetInventoryVisibility())
		{
			SetState(PLAYER_UI_INTERACTING, true);
			//bUIControlling = true;
		}
		else
		{
			if (ESlateVisibility::Visible == PC->NPCConversation->GetVisibility()) return;
			SetState(PLAYER_UI_INTERACTING, false);
			//bUIControlling = false;
		}
	}
}

void ACPlayerCharacter::ShiftTriggered()
{
	if (!PlayerInputCheck(PLAYER_INPUT_TYPE_SHIFT) || GetState(PLAYER_ROLLING))
	{
		return;
	}
	
	if (Stamina <= ShiftStamina * 0.4f) return;

	if (
		(GetState(PLAYER_ATTACKING) && GetState(PLAYER_ATTACK_CANCLE_UNLOCK)) ||
		!GetState(PLAYER_ATTACKING)
		)
	{
		SetActorRotation(GetMoveInputDesiredRotator());
		StopAnimMontage();
		if (StandToRoll.ExecuteIfBound())
		{
			SetState(PLAYER_ROLLING, true);
			Stamina -= ShiftStamina;
		}
	}
}
void ACPlayerCharacter::E_Triggered()
{
	ACPlayerController* PC = Cast<ACPlayerController>(GetController());
	if (!IsValid(PC)) return;
	PC->OnInteract();
}

void ACPlayerCharacter::Anykey_Triggered()
{
	//Revive
	if (GetState(PLAYER_DIED))
	{
		ACPlayerController* PC = Cast<ACPlayerController>(GetController());
		if (!IsValid(PC)) return;
		if (PC->HUDOverlay != nullptr && PC->HUDOverlay->GetContinueRevive())
		{
			Revive(PC);
		}
	}
}

void ACPlayerCharacter::Scroll(const FInputActionValue& Value)
{
	if (GetState(PLAYER_UI_INTERACTING)) return;

	float ScrollAxis = Value.Get<float>();
	float TempTargetLength = SpringArmComponent->TargetArmLength - 10.f * ScrollAxis;

	if (ScrollAxis > 0.f && 80 > TempTargetLength) return;
	if (ScrollAxis < 0.f && 1200 < TempTargetLength) return;
	
	SpringArmComponent->TargetArmLength = TempTargetLength;
}


void ACPlayerCharacter::Equip(ACWeapon& ActorToEquip)
{
	//ActorToEquip.AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), MeleeSocket);
	//CurrentWeaponMode = WeaponSocket;
	//UE_LOG(LogTemp, Log, TEXT("Equiped %s"), *ActorToEquip.GetName());
	//WeaponEquipped = &ActorToEquip;
	//ActorToEquip.SetOwner(this);
}

void ACPlayerCharacter::ESC()
{
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetController());
	UIController->SwitchESCMenu();
}

void ACPlayerCharacter::Equip(AActor& ActorToEquip)
{
	IIWeapon* WTE = Cast<IIWeapon>(&ActorToEquip);
	ActorToEquip.AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), MeleeSocket);
	CurrentWeaponMode = WeaponSocket;
	UE_LOG(LogTemp, Log, TEXT("Equiped %s"), *ActorToEquip.GetName());
	WeaponEquipped = &ActorToEquip;
	IsWeaponEquiped = true;
	ActorToEquip.SetOwner(this);
}

void ACPlayerCharacter::UnEquip()
{
	WeaponEquipped->Destroy();
	IsWeaponEquiped = false;
}

bool ACPlayerCharacter::GetState(UINT StateType)
{
	if (State & StateType) return true;
	else return false;
}

void ACPlayerCharacter::SetState(UINT StateType, bool b)
{	
	if (GetState(StateType) ^ b)
	{
		if (b) State += StateType;
		else State -= StateType;
	}
}

void ACPlayerCharacter::SetHoverringUI(UUserWidget* UI)
{
	HoverringUI = UI;
	if (UI != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Set Hoverring UI : %s"), *UI->GetName());
	}
	else UE_LOG(LogTemp, Log, TEXT("Set Hoverring UI : nullptr"));
}

void ACPlayerCharacter::SetPlayerGold(UINT32 e)
{
	PlayerGold = e;
	if (ACPlayerController* PC = Cast<ACPlayerController>(GetController()))
	{
		PC->ItemInventory->PlayerGold->SetText(FText::FromString(FString::FromInt(e)));
	}
}

void ACPlayerCharacter::GainPlayerGold(UINT32 e)
{
	SetPlayerGold(PlayerGold + e);
}

void ACPlayerCharacter::ShowDamageUI(float Damage, FVector Location, bool IsAttacked)
{
	ACPlayerController* PC = Cast<ACPlayerController>(GetController());
	if (PC == nullptr) return;

	PC->ShowDamageUI(Damage, Location, IsAttacked ? FColor::Red : FColor::White, IsAttacked);

	if (!IsAttacked)
	{
		GetMesh()->bPauseAnims = true;
		GetWorld()->GetTimerManager().SetTimer(HitReactTimerHandle, this, &ACPlayerCharacter::SetAnimPauseFree, 0.15f);
	}
}

bool ACPlayerCharacter::HitDamage(float e, ACEnemyCharacter* Attacker, FVector HitLocation, int Power)
{
	if (GetState(PLAYER_ROLL_INVINCIBLE))
	{
		UE_LOG(LogTemp, Log, TEXT("Player Roll Dodged"));
		return false;
	}
	else if (GetState(PLAYER_RAGDOLL) || GetState(PLAYER_GETTINGUP))
	{
		UE_LOG(LogTemp, Log, TEXT("Player in Ragdoll"));
		return false;
	}
	HP -= e;
	SetState(PLAYER_UI_INTERACTING, false);
	SetLastDealingEnemy(Attacker);
	
	ShowDamageUI(e, HitLocation, true);

	if (HP <= 0.f) return true;
	switch (Power)
	{
	case(PLAYER_HIT_REACT_STAND):
		break;
	case(PLAYER_HIT_REACT_FLINCH):
		StopAnimMontage();
		SetState(PLAYER_ATTACKING, true);
		HitReact.ExecuteIfBound();
		break;
	case(PLAYER_HIT_REACT_HITDOWN):
		StopAnimMontage();
		
		SetState(PLAYER_RAGDOLL, false);
		SetState(PLAYER_CANGETUP, true);
		HitDown.ExecuteIfBound();
		//OnHitDown();
		break;
	}
	return true;
}

void ACPlayerCharacter::SetLastDealingEnemy(ACEnemyCharacter* EC)
{
	FTimerManager& WorldTimer = GetWorld()->GetTimerManager();
	WorldTimer.ClearTimer(LastDealingEnemyTimerHandle);
	WorldTimer.SetTimer(LastDealingEnemyTimerHandle, this, &ACPlayerCharacter::ResetLastDealingEnemy, 15.f);

	LastDealingEnemy = EC;
}

FVector ACPlayerCharacter::GetMoveInputDesiredVector()
{
	double directionalYaw = 0.f;

	bool W = GetState(PLAYER_INPUT_W);
	bool S = GetState(PLAYER_INPUT_S);
	bool A = GetState(PLAYER_INPUT_A);
	bool D = GetState(PLAYER_INPUT_D);
	
	if (W && A)			directionalYaw = -45.f;
	else if (W && D)	directionalYaw = 45.f;
	else if (S && A)	directionalYaw = -135.f;
	else if (S && D)	directionalYaw = 135.f;
	else if (S)			directionalYaw = 180.f;
	else if (A)			directionalYaw = -90.f;
	else if (D)			directionalYaw = 90.f;
	//else if (W)			directionalYaw = 0.f;
	else				directionalYaw = 0.f;
	
	return FRotator(0.f, GetBaseAimRotation().Yaw + directionalYaw, 0.f).RotateVector(FVector::ForwardVector);
}

FRotator ACPlayerCharacter::GetMoveInputDesiredRotator()
{
	double directionalYaw = 0.f;

	bool W = GetState(PLAYER_INPUT_W);
	bool S = GetState(PLAYER_INPUT_S);
	bool A = GetState(PLAYER_INPUT_A);
	bool D = GetState(PLAYER_INPUT_D);

	if (W && A)			directionalYaw = -45.f;
	else if (W && D)	directionalYaw = 45.f;
	else if (S && A)	directionalYaw = -135.f;
	else if (S && D)	directionalYaw = 135.f;
	else if (S)			directionalYaw = 180.f;
	else if (A)			directionalYaw = -90.f;
	else if (D)			directionalYaw = 90.f;
	else if (W)			directionalYaw = 0.f;
	else FRotator(0.f, GetActorRotation().Yaw, 0.f);
	
	return FRotator(0.f, GetBaseAimRotation().Yaw + directionalYaw, 0.f);
	//return FRotator(0.f, GetControlRotation().Yaw + directionalYaw, 0.f);
}

//Deprecated
//void ACPlayerCharacter::TransferToLevel(FName e)
//{
//	if (AMMBGameModeBase* GM = Cast<AMMBGameModeBase>(GetWorld()->GetAuthGameMode()))
//	{
//		UE_LOG(LogTemp, Log, TEXT("Gamemode loaded"));
//		//UGameplayStatics::OpenLevelBySoftObjectPtr(this, GM->LevelToLoad);
//	}
//}

void ACPlayerCharacter::AxisAdjustOnScreenRotation(float DeltaTime)
{
	FRotator Delta = (GetMoveInputDesiredRotator() - GetActorRotation()).GetNormalized();
	FRotator NR = GetActorRotation();
	float CurrentYaw = NR.Yaw;
	float weight = 12.f * DeltaTime;

	NR.Yaw = NR.Yaw + (Delta.Yaw >= 0 ? weight : -weight);
	if ((CurrentYaw <= Delta.Yaw) != (NR.Yaw <= Delta.Yaw)) NR.Yaw = NR.Yaw - weight + Delta.Yaw;
	SetActorRotation(NR);

	//float weight = weight <= FMath::Abs(NR.Yaw - Delta.Yaw) ? 0.6f : NR.Yaw;
	//UE_LOG(LogTemp, Log, TEXT("Rotating To %s"), *Delta.ToString());
	
}

void ACPlayerCharacter::OnHitDown()
{
	if (!GetState(PLAYER_RAGDOLL)) //DOWN(RAGDOLL)
	{
		UE_LOG(LogTemp, Log, TEXT("collision prifile name : %s"), *GetMesh()->GetCollisionProfileName().ToString());

		SetState(PLAYER_RAGDOLL, true);
		SetState(PLAYER_CANGETUP, false);

		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
		SetActorEnableCollision(true);

		GetMesh()->WakeAllRigidBodies();
		GetMesh()->SetAllBodiesSimulatePhysics(true);
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->bBlendPhysics = true;

		UCharacterMovementComponent* CharacterComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
		if (CharacterComp)
		{
			CharacterComp->StopMovementImmediately();
			CharacterComp->SetComponentTickEnabled(false);
		}

		GetWorld()->GetTimerManager().SetTimer(HitDownRecoverHandle, this, &ACPlayerCharacter::SetCanGetup, 1.5f);

	}
	else //GET UP
	{
		SetState(PLAYER_RAGDOLL, false);
		SetState(PLAYER_CANGETUP, false);
		//FHitResult SweepResult;
		//FCollisionShape CS;
		//CS.SetCapsule(34.f, 88.f);
		//if (GetWorld()->SweepSingleByChannel(SweepResult, GetActorLocation(), GetActorLocation(), FQuat::Identity, DefaultCollisionChannel, CS))
		//{
		//	if (Cast<ACharacter>(SweepResult.GetActor()))
		//	{
		//		UE_LOG(LogTemp, Log, TEXT("Sweep Result : %s"), *SweepResult.GetActor()->GetName());
		//	}
		//}
		UCapsuleComponent* CapsuleComp = GetCapsuleComponent();

		GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));
		SetActorEnableCollision(true);

		GetMesh()->SetAllBodiesSimulatePhysics(false);
		GetMesh()->SetSimulatePhysics(false);
		GetMesh()->PutAllRigidBodiesToSleep();
		GetMesh()->bBlendPhysics = false;

		GetMesh()->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -87.f), FRotator(0.f, -90.f, 0.f));

		UCharacterMovementComponent* CharacterComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
		if (CharacterComp)
		{
			CharacterComp->SetComponentTickEnabled(true);
		}
	}
	return;
}

void ACPlayerCharacter::StaminaSpend(float RequiredStamina)
{
	if (RequiredStamina <= 0.f) return;
	if (Stamina <= 0.f)
	{
		StopAnimMontage();
		if (Dizzy.ExecuteIfBound())
		{
			SetState(PLAYER_STAMINA_REGAIN, false);
			SetState(PLAYER_STAMINA_RUNOUT, true);
		}
	}
	else Stamina -= RequiredStamina;
}

void ACPlayerCharacter::MonsterKilledCount(ACEnemyCharacter* MonsterKilled)
{
	//UE_LOG(LogTemp, Log, TEXT("Killed Monster Class : %s"), MonsterKilled->GetFName());

	if (ACPlayerController* PC = Cast<ACPlayerController>(GetController()))
	{
		PC->CheckQuest(MonsterKilled);
		//PC->CheckQuest(this, MonsterClass);
	}
	
}

void ACPlayerCharacter::OnGraspRope(FTransform GraspTransform)
{
	StopAnimMontage();
	SetState(PLAYER_CLIMBING_ROPE, true);
	ClimbingRope.ExecuteIfBound(true);
	GetMesh()->bPauseAnims = true;
	GetCharacterMovement()->GravityScale = 0;
	GetMovementComponent()->StopMovementImmediately();
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Ignore);
	//SetActorLocation(GraspLocation);
	SetActorLocationAndRotation(GraspTransform.GetLocation(), GraspTransform.GetRotation());
	//SetActorTransform();
}

void ACPlayerCharacter::OnLooseRope()
{
	GetMesh()->bPauseAnims = false;
	SetState(PLAYER_CLIMBING_ROPE, false);
	ClimbingRope.ExecuteIfBound(false);
	GetCharacterMovement()->GravityScale = 1;
	GetMovementComponent()->StopMovementImmediately();
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
}

void ACPlayerCharacter::SetRevivalPoint(FVector Pos)
{
	RevivalPos = Pos;
}

void ACPlayerCharacter::QuestClear(int e)
{
	QuestComponent->OnQuestCleared(e);
}

void ACPlayerCharacter::QuestInitialize(int e)
{
	QuestComponent->OnQuestInitialize(e);
}

void ACPlayerCharacter::SetStartPos(FVector e)
{
	StartPos = e;
}

float ACPlayerCharacter::GetBonusAttackDamage()
{
	return 0.0f;
}

void ACPlayerCharacter::FallToRevivalPoint(AActor* AttachedCamera, float Damage)
{
	APlayerController* AController = Cast<APlayerController>(GetController());
	if (AttachedCamera != nullptr) AController->SetViewTargetWithBlend(AttachedCamera);
	GetWorld()->GetTimerManager().SetTimer(
		HitReactTimerHandle, FTimerDelegate::CreateLambda([&] {
			SetActorLocation(RevivalPos);
			APlayerController* AController = Cast<APlayerController>(GetController());
			if (AController != nullptr) AController->SetViewTargetWithBlend(CameraComponent->GetOwner(), 1.f);
			}), 3.f, false
	);
	if (Damage > 0.f) HitDamage(Damage, nullptr);
}
