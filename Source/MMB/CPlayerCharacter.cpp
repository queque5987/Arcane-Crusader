#include "CPlayerCharacter.h"
#include "IWidgetInteract.h"
#include "PCH.h"
#include "Engine/LevelStreaming.h"
#include "IFlyMonster.h"
#include "CStageGameMode.h"
#include "GameFramework//PlayerStart.h"
#include "IStageMaterialManager.h"
#include "Materials/Material.h"

const FName ACPlayerCharacter::WeaponSocket(TEXT("WeaponSocket"));
const FName ACPlayerCharacter::MeleeSocket(TEXT("MeleeSocket"));
const FName ACPlayerCharacter::RifleSocket(TEXT("RifleSocket"));
const FName ACPlayerCharacter::tempRifleSocket(TEXT("tempRifleSocket"));
const FName ACPlayerCharacter::BackSocket(TEXT("BackSocket"));

ACPlayerCharacter::ACPlayerCharacter()
{
	WeaponEquipped = nullptr;
	//IsAttacking = false;
	bRMBCastDone = false;
	bUIControlling = false;
	CastingClock = -1.f;
	State = 0;//1073741832;
	KeyState = 0;
	PlayerGold = 100;
	HP = 100;
	MaxHP = 100;
	Stamina = 0;
	MaxStamina = 500;
	UltGauge = 0.f;
	ShiftStamina = 4.f;
	StaminaRegain = 12.f;
	LastDealingEnemy = nullptr;
	SpineCapsuleDist = 0.f;

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
	ConstructorHelpers::FObjectFinder<UInputAction> Q1Finder(TEXT("/Game/Player/Input/IA_1"));
	ConstructorHelpers::FObjectFinder<UInputAction> Q2Finder(TEXT("/Game/Player/Input/IA_2"));
	ConstructorHelpers::FObjectFinder<UInputAction> Q3Finder(TEXT("/Game/Player/Input/IA_3"));
	ConstructorHelpers::FObjectFinder<UInputAction> TabFinder(TEXT("/Game/Player/Input/IA_Tab"));
	ConstructorHelpers::FObjectFinder<UInputAction> QFinder(TEXT("/Game/Player/Input/IA_Q"));

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
	if (Q1Finder.Succeeded()) Quick1Action = Q1Finder.Object;
	if (Q2Finder.Succeeded()) Quick2Action = Q2Finder.Object;
	if (Q3Finder.Succeeded()) Quick3Action = Q3Finder.Object;
	if (TabFinder.Succeeded()) TabAction = TabFinder.Object;
	if (QFinder.Succeeded()) QAction = QFinder.Object;


	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->TargetArmLength = 550.f;
	SpringArmComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(GetCapsuleComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	ConstructorHelpers::FObjectFinder<USkeletalMesh> SMKnightMage(TEXT("/Game/Player/Guard/castle_guard_01"));
	if (SMKnightMage.Succeeded()) GetMesh()->SetSkeletalMesh(SMKnightMage.Object);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -87.f), FRotator(0.f, -90.f, 0.f));

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

	GetCapsuleComponent()->SetCollisionResponseToChannel(EnemyAttackChannel, ECollisionResponse::ECR_Overlap);
	GetCapsuleComponent()->SetCollisionResponseToChannel(PlayerAttackChannel, ECollisionResponse::ECR_Block);

	QuestComponent = CreateDefaultSubobject<UQuestComponent>(TEXT("QuestComponent"));

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComponent"));
	PointLight->SetupAttachment(RootComponent);
	PointLight->SetRelativeLocation(FVector(600.f, 0.f, 150.f));
	PointLight->SetVisibility(false);

	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Overlap);

	DodgeDom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DodgeDomComponent"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> DodgeDomFinder(TEXT("/Game/Resources/Meshes/Player_DodgeDom/SM_PlayerDodgeDom"));
	if (DodgeDomFinder.Succeeded()) DodgeDom->SetStaticMesh(DodgeDomFinder.Object);
	DodgeDom->SetupAttachment(GetRootComponent());
	DodgeDom->SetVisibility(false);
	DodgeDom->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(1);
}

void ACPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
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

	//if (StartPos != FVector::ZeroVector)
	//{
	//	SetActorLocation(StartPos);
	//}
	//else
	//{
	//	AActor* PS = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass());
	//	if (PS != nullptr)
	//	{
	//		UE_LOG(LogTemp, Log, TEXT("Player Start Point : %s"), *PS->GetActorLocation().ToString());
	//		//DrawDebugSphere(GetWorld(), PS->GetActorLocation(), 300.f, 32.f, FColor::Blue, false, 10.f);
	//		StartPos = PS->GetActorLocation();
	//	}
	//}

	//GetWorld()->GetTimerManager().SetTimer(StageStartHandle, FTimerDelegate::CreateLambda([&] {
	//	bool Flag = true;
	//	for (ULevelStreaming* LS : GetWorld()->GetStreamingLevels())
	//	{
	//		if (LS != nullptr && !LS->IsLevelLoaded())
	//		{
	//			Flag = false;
	//			break;
	//		}
	//	}
	//	if (Flag)
	//	{
	//		UE_LOG(LogTemp, Log, TEXT("Loaded"));
	//		SetActorLocation(StartPos);
	//		GetWorld()->GetTimerManager().ClearTimer(StageStartHandle);
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Log, TEXT("Loading"));
	//	}
	//	}), 0.1f, true
	//);

	if (IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetController()))
	{
		UIController->SetMaxHP(GetMaxHP());
		UIController->SetMaxStamina(GetMaxStamina());
	}

	if (WeaponEquipped != nullptr) OnWeaponChanged();

// Stage Game Mode Materail Set
	StageMaterialManager = nullptr;
	if (IIStageMaterialManager* IMM = Cast<IIStageMaterialManager>(GetWorld()->GetAuthGameMode()))
	{
		StageMaterialManager = IMM;
	}
	//if (StageMaterialManager != nullptr) StageMaterialManager->UpdatePlayerCharacterPos(GetActorLocation());
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

int32 ACPlayerCharacter::GetEquippedWeaponType()
{
	if (WeaponEquipped == nullptr) return 0;
	else if (WeaponEquipped->IsA(ACBattleStaff::StaticClass())) return 1;
	else if (WeaponEquipped->IsA(ACRifleStaff::StaticClass())) return 2;
	return 0;
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

	FCollisionQueryParams CollQuery;
	CollQuery.AddIgnoredActor(this);
	if (WeaponEquipped != nullptr) CollQuery.AddIgnoredActor(WeaponEquipped);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Pawn, CollQuery))
	{
		UE_LOG(LogTemp, Log, TEXT("Line Trace ActorName : %s"), *HitResult.GetActor()->GetName());	
	}
}

bool ACPlayerCharacter::GetDealingEnemyTransform(FTransform& OutTransform)
{
	if (LastDealingEnemy == nullptr) return false;

	OutTransform = LastDealingEnemy->GetActorTransform();
	return true;
}

void ACPlayerCharacter::SetMaxHP(float NewMaxHP)
{
	if (IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetController()))
	{
		UIController->SetMaxHP(NewMaxHP);
	}
	MaxHP = NewMaxHP;
}

void ACPlayerCharacter::SetMaxStamina(float NewMaxStamina)
{
	if (IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetController()))
	{
		UIController->SetMaxStamina(NewMaxStamina);
	}
	MaxStamina = NewMaxStamina;
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
	bool notAiming = !GetState(PLAYER_AIMING);

	switch (InputType)
	{
	case(PLAYER_INPUT_TYPE_SHIFT):
		if (notDead) Getup();
		else Anykey_Triggered();
		return notAiming && notDead && UICheck && (Standing || GroundedButCanGetUp) && notStaminaRunout && notClimbing;
		break;
	case(PLAYER_INPUT_TYPE_LOOK):
		return UICheck;
		break;
	case(PLAYER_INPUT_TYPE_CLICK):
		if (GetState(PLAYER_DRINKING_POTION))
		{
			UE_LOG(LogTemp, Log, TEXT("PLAYER_DRINKING_POTION True"));
			return false;
		}
	case(PLAYER_INPUT_TYPE_JUMP):
	case(PLAYER_INPUT_TYPE_MOVE):
		if (notDead) LazyGetUp();
		else Anykey_Triggered();
		return notDead && UICheck && Standing && notGettingUp && notStaminaRunout && notClimbing;
		break;
	default:
		return false;
	}
}

void ACPlayerCharacter::OnOverlapEnemy(ACharacter* EnemyChar)
{
	OverlapingCharacters.AddUnique(EnemyChar);
}

void ACPlayerCharacter::OnOverlapEndEnemy(ACharacter* EnemyChar)
{
	OverlapingCharacters.Remove(EnemyChar);
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

void ACPlayerCharacter::OnWeaponChanged()
{
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetController());
	if (UIController == nullptr) return;
	UIController->SetAimVisibility(WeaponEquipped != nullptr ? WeaponEquipped->IsA(ACRifleStaff::StaticClass()) : false);
	UIController->SetBattleVIsibility(WeaponEquipped != nullptr ? WeaponEquipped->IsA(ACBattleStaff::StaticClass()) : false);
	if (ACBattleStaff* BS = Cast<ACBattleStaff>(WeaponEquipped))
	{
		UIController->SetBruteCooldownParam(BS->GetBruteCoolDownMax());
	}
	//if (ACBattleStaff* BS = Cast<ACBattleStaff>(WeaponEquipped))
	//{
	//	UIController->SetBruteCooldown(BS->GetBruteCoolDown() / BS->GetBruteCoolDownMax());
}

void ACPlayerCharacter::UpdateHUDStates()
{
	// TODO Use Interface Instead
	ACPlayerController* PCC = Cast<ACPlayerController>(GetController());
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetController());
	if (UIController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerUIController Not Found"));
		return;
	}
	if (PCC == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController Not Found"));
		return;
	}
	if (PCC->HUDOverlay->GetVisibility() != ESlateVisibility::Visible) return;

	// HP BAR

	PCC->SetHPPercent(HP / MaxHP);
	PCC->SetStaminaPercent(Stamina / MaxStamina);

	if (LastDealingEnemy != nullptr)
	{
		PCC->SetEnemyHP(LastDealingEnemy->GetHP() / LastDealingEnemy->GetMaxHP());
		PCC->SetEnemyHPVisibility(true);
	}
	else
	{
		PCC->SetEnemyHPVisibility(false);
	}

	// AIM SPOT
	if (WeaponEquipped == nullptr) return;

	// Move To OnWeaponChanged 
	//PCC->SetAimVisibility(WeaponEquipped->IsA(ACRifleStaff::StaticClass())); //GetState(PLAYER_AIMING)

	if (ACBattleStaff* BS = Cast<ACBattleStaff>(WeaponEquipped))
	{
		//UIController->SetBruteCooldown(BS->GetBruteCoolDown() / BS->GetBruteCoolDownMax());
		UIController->SetBruteGauge(BS->GetBruteGauge() / BS->GetBruteGaugeMax());
		UIController->SetBruteMode(BS->GetBruteMode());
	}
	if (ACRifleStaff* RS = Cast<ACRifleStaff>(WeaponEquipped))
	{
		PCC->SetAimSpriteBlur(GetState(PLAYER_AIMING) ? 0.f : 10.f);
		// Rifle Select UI Update
		FVector LeftBullets;
		RS->GetLeftBullet(LeftBullets);
		//UE_LOG(LogTemp, Log, TEXT("[%f, %f, %f]"), LeftBullets.Y, LeftBullets.X, LeftBullets.Z);
		int32 CurrBulletType = RS->GetBulletType();
		PCC->SetRifleSelectCylinder(LeftBullets, FVector(CurrBulletType, (CurrBulletType + 2) % 3, (CurrBulletType + 1) % 3));
		// Charge Visibility
		if (RS != nullptr && RS->GetBulletType() == 0)
		{
			float Charged = RS->GetLMBCharge();
			//UE_LOG(LogTemp, Log, TEXT("%f"), Charged);
			if (Charged < 0.05f) PCC->HUDOverlay->AimCharge->SetVisibility(ESlateVisibility::Hidden);
			else
			{
				PCC->HUDOverlay->AimCharge->SetVisibility(ESlateVisibility::HitTestInvisible);
				PCC->HUDOverlay->AimCharge->SetPercent(Charged / 2.f);
			}
		}
		else PCC->HUDOverlay->AimCharge->SetVisibility(ESlateVisibility::Hidden);
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

void ACPlayerCharacter::OnDodgedAttack()
{
	if (StageMaterialManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("StageMaterialManager Not Found"));
		return;
	}
	StageMaterialManager->PostProcessZoom(true, GetActorLocation());
	StageMaterialManager->ExecutePlayerDodgedEvent();
	GetWorld()->GetTimerManager().ClearTimer(DodgeTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(DodgeTimerHandle, FTimerDelegate::CreateLambda(
		[&] {
			if (StageMaterialManager != nullptr) StageMaterialManager->ExecutePlayerDodgedEndEvent();
			SetState(PLAYER_DODGED, false);
			DodgeDom->SetVisibility(false);
		}
	), 3.f, false);
	DodgeDom->SetRelativeScale3D(FVector(StageMaterialManager->GetPostProcessRadius() / 100.f));
	DodgeDom->SetVisibility(true);
	SetState(PLAYER_DODGED, true);
}

void ACPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (LastDealingEnemy != nullptr)
	//{
	//	UE_LOG(LogTemp, Log, TEXT("Is Enemy On Left : %f"), FVector::DotProduct(LastDealingEnemy->GetActorLocation() - GetActorLocation(), GetActorRightVector()));
	//}

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
		GetWorld()->GetTimerManager().SetTimer(StaminaRegainHandle, this, &ACPlayerCharacter::SetStaminaRegain, 2.6f);
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
		) Stamina += (StaminaRegain + (MaxStamina - Stamina) / MaxStamina * 50.f) * DeltaTime;
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
	//if (LastDealingEnemy != nullptr && LastDealingEnemy->GetClass()->ImplementsInterface(UIFlyMonster::StaticClass()))
	//{
	//	IIFlyMonster* FlyableMonster = Cast<IIFlyMonster>(LastDealingEnemy);
	//	FVector tempPos = CameraComponent->GetRelativeLocation();
	//	if (FlyableMonster->GetIsFlying())
	//	{
	//		tempPos.Z += 180.f * DeltaTime;
	//		if (tempPos.Z > 200.f) tempPos.Z = 300.f;
	//		CameraComponent->SetRelativeLocation(tempPos);
	//	}
	//	else
	//	{
	//		tempPos.Z -= 180.f * DeltaTime;
	//		if (tempPos.Z < 0.f) tempPos.Z = 0.f;
	//		CameraComponent->SetRelativeLocation(tempPos);
	//	}
	//}

// TURN ON LIGHT WHEN NIGHT
	if (ACStageGameMode* StageGameMode = Cast<ACStageGameMode>(GetWorld()->GetAuthGameMode()))
	{
		float CurrLevelClock = StageGameMode->GetCurrentLevelClock();
		if (CurrLevelClock / 60.f > 18.5f || CurrLevelClock / 60.f < 6.5f)
		{
			PointLight->SetVisibility(true);

			// Distance < 1200
			if (LastDealingEnemy != nullptr && FVector::Distance(GetActorLocation(), LastDealingEnemy->GetActorLocation()) <= 1200.f)
			{
				UE_LOG(LogTemp, Log, TEXT("Dealing With Close monster"));
				PointLight->SetRelativeLocation(
					FVector(
						FVector::Distance(GetActorLocation(), LastDealingEnemy->GetActorLocation()) / 2.f,
						0.f,
						500.f
					)
				);
			}
			else
			{
				FVector SpawnPointLightLocation = GetActorLocation() + GetActorForwardVector() * 600.f;
				FHitResult HitResult;
				FCollisionQueryParams Params;
				Params.AddIgnoredActor(this);
				bool bHit = GetWorld()->LineTraceSingleByProfile(
					HitResult,
					GetActorLocation(),
					SpawnPointLightLocation,
					GetMesh()->GetCollisionProfileName(),
					Params
				);
				if (bHit)
				{
					PointLight->SetRelativeLocation(
						FVector(
							FVector::Dist2D(GetActorLocation(), HitResult.Location),
							0.f,
							150.f
						)
					);
					//UE_LOG(LogTemp, Log, TEXT("Traced Actor : %s"), *HitResult.GetActor()->GetName());
				}
				else PointLight->SetRelativeLocation(FVector(600.f, 0.f, 150.f));
				//DrawDebugSphere(GetWorld(), bHit ? HitResult.Location : SpawnPointLightLocation, 120.f, 32.f, bHit ? FColor::Green : FColor::Red);
			}
		}
		else
		{
			PointLight->SetVisibility(false);
		}
	}

//ON RIFLE STAFF
	
	if (GetState(PLAYER_AIMING) && (WeaponEquipped != nullptr && WeaponEquipped->IsA(ACRifleStaff::StaticClass())))
	{
		if (CameraComponent->FieldOfView > 60.f)
		{
			CameraComponent->SetFieldOfView(CameraComponent->FieldOfView - 30.f * DeltaTime);
		}
		else
		{
			CameraComponent->SetFieldOfView(60.f);
		}
	}
	else
	{
		if (CameraComponent->FieldOfView < 90.f)
		{
			CameraComponent->SetFieldOfView(CameraComponent->FieldOfView + 4.f * DeltaTime);
		}
		else
		{
			CameraComponent->SetFieldOfView(90.f);
		}

	}

// Stage Material Access
	if (GetState(PLAYER_DODGED) && StageMaterialManager != nullptr)
	{
		DodgeDom->SetRelativeScale3D(FVector(StageMaterialManager->GetPostProcessRadius() / 100.f));
	}

// Mesh-Montage Adjusting
	//FVector SpineLoc_Origin = GetMesh()->GetBoneLocation("Spine", EBoneSpaces::WorldSpace) - MeshAdjustingVector;
	FVector SpineLoc = GetMesh()->GetBoneLocation("Spine", EBoneSpaces::WorldSpace);
	FVector CapsuleLoc = GetCapsuleComponent()->GetComponentLocation();
	SpineCapsuleDist = FVector::Dist2D(SpineLoc, CapsuleLoc);
	//DrawDebugSphere(GetWorld(), SpineLoc, 150.f, 32.f, FColor::Green);
	//DrawDebugSphere(GetWorld(), CapsuleLoc, 150.f, 32.f, FColor::Yellow);

	//UE_LOG(LogTemp, Log, TEXT("Bone Diff : %f"), S_C_Distance);
	//if (FVector::Dist2D(SpineLoc_Origin, CapsuleLoc) > 20.f)
	//{
	//	FVector SpineToCapsuleDirection = (CapsuleLoc - SpineLoc).GetSafeNormal2D();
	//	if (FVector::Dist2D(MeshAdjustingVector, MeshAdjustingVector + SpineToCapsuleDirection * S_C_Distance * DeltaTime * 2.f) <= S_C_Distance)
	//	{
	//		MeshAdjustingVector += SpineToCapsuleDirection * S_C_Distance * DeltaTime * 2.f;
	//	}
	//}
	//else
	//{
	//	MeshAdjustingVector = FVector::ZeroVector;
	//}
	//GetMesh()->SetRelativeLocation(MeshAdjustingVector + FVector(0.f, 0.f, -87.f));
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
		EnhancedInputComponent->BindAction(Quick1Action, ETriggerEvent::Completed, this, &ACPlayerCharacter::Quick1);
		EnhancedInputComponent->BindAction(Quick2Action, ETriggerEvent::Completed, this, &ACPlayerCharacter::Quick2);
		EnhancedInputComponent->BindAction(Quick3Action, ETriggerEvent::Completed, this, &ACPlayerCharacter::Quick3);
		EnhancedInputComponent->BindAction(TabAction, ETriggerEvent::Completed, this, &ACPlayerCharacter::Tab);
		EnhancedInputComponent->BindAction(QAction, ETriggerEvent::Completed, this, &ACPlayerCharacter::QCompleted);
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

	if (SpineCapsuleDist > 40.f) return;

	SetState(PLAYER_INPUT_W, MovementVector.Y > 0 ? true: false);
	SetState(PLAYER_INPUT_S, MovementVector.Y < 0 ? true : false);
	SetState(PLAYER_INPUT_D, MovementVector.X > 0 ? true : false);
	SetState(PLAYER_INPUT_A, MovementVector.X < 0 ? true : false);

	// NO ATTACK or ROLLING BUT AIMING IS FINE 
	if ((!GetState(PLAYER_AIMING) && GetState(PLAYER_ATTACKING)) || GetState(PLAYER_ROLLING)) return;

	// STAMINA RAN OUT OVERED
	if (GetState(PLAYER_DIZZY) && !GetState(PLAYER_STAMINA_RUNOUT))
	{
		SetState(PLAYER_DIZZY, false);
		StopAnimMontage();
	}

	//CLIMB ROPE
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

	//MOVE
	if (Controller != nullptr && PlayerInputCheck(PLAYER_INPUT_TYPE_MOVE))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		if (!CheckIsAtCharacter(ForwardDirection * MovementVector.Y + RightDirection * MovementVector.X))
		{
			return;
		}

		AddMovementInput(ForwardDirection, GetState(PLAYER_AIMING) ? 
			MovementVector.Y * 0.1f : MovementVector.Y * CameraComponent->FieldOfView / 90.f);
		AddMovementInput(RightDirection, GetState(PLAYER_AIMING) ? 
			MovementVector.X * 0.1f : MovementVector.X * CameraComponent->FieldOfView / 90.f);

		float TempSpeed = GetCharacterMovement()->MaxWalkSpeed * (1 + AccMovementSpeedAcc);
		if (MaxMoveMentSpeed >= TempSpeed) GetCharacterMovement()->MaxWalkSpeed = TempSpeed;

		//UE_LOG(LogTemp, Log, TEXT("%s"), *Rotation.ToString());
	}
}

bool ACPlayerCharacter::CheckIsAtCharacter(FVector Direction)
{
	FVector CurrLocation = GetActorLocation();

	//DrawDebugLine(GetWorld(), CurrLocation, CurrLocation + Direction * 500.f, FColor::Blue, false, -1.f, 0U, 80.f);

	for (ACharacter* C : OverlapingCharacters)
	{
		FVector EDirection = (CurrLocation - C->GetActorLocation()).GetSafeNormal2D();

		float Rad = FMath::Acos(FVector::DotProduct(Direction, EDirection) / (Direction.Size() * EDirection.Size()));

		UE_LOG(LogTemp, Log, TEXT("CheckIsAtCharacter : %s : %f"), *C->GetName(), Rad);
		if (Rad > 1.2f) return false;
	}

	return true;
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
	SetKeyState(PLAYER_INPUT_LMB, true);

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
	SetKeyState(PLAYER_INPUT_LMB, false);

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
	SetKeyState(PLAYER_INPUT_RMB, true);

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
	SetKeyState(PLAYER_INPUT_RMB, false);

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
	InventoryOpenedEvent.ExecuteIfBound();

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

	//if (StageMaterialManager != nullptr)
	//{
	//	OnDodgedAttack();
	//	//StageMaterialManager->PostProcessZoom(true, GetActorLocation());
	//}
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

void ACPlayerCharacter::Quick1()
{
	if (!PlayerInputCheck(PLAYER_INPUT_TYPE_CLICK) || GetState(PLAYER_ATTACKING)) return;
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetController());
	int32 ReactAnim = UIController->UseItem(1);
	ItemUsageAction(ReactAnim);
	UE_LOG(LogTemp, Log, TEXT("QuickSlot 1 : Item Type %d"), ReactAnim);
}

void ACPlayerCharacter::Quick2()
{
	if (!PlayerInputCheck(PLAYER_INPUT_TYPE_CLICK) || GetState(PLAYER_ATTACKING)) return;

	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetController());
	int32 ReactAnim = UIController->UseItem(2);
	ItemUsageAction(ReactAnim);
	UE_LOG(LogTemp, Log, TEXT("QuickSlot 2 : Item Type %d"), ReactAnim);
}

void ACPlayerCharacter::Quick3()
{
	if (!PlayerInputCheck(PLAYER_INPUT_TYPE_CLICK) || GetState(PLAYER_ATTACKING)) return;

	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetController());
	int32 ReactAnim = UIController->UseItem(3);
	ItemUsageAction(ReactAnim);
	UE_LOG(LogTemp, Log, TEXT("QuickSlot 3 : Item Type %d"), ReactAnim);
}

void ACPlayerCharacter::Tab()
{
	////Test
	//if (StageMaterialManager != nullptr)
	//{
	//	StageMaterialManager->PostProcessZoom(false, GetActorLocation());
	//	SetState(PLAYER_DODGED, false);
	//	//BWSphereComponent->SetVisibility(false);
	//	DodgeDom->SetVisibility(false);
	//}
	//// Test

	if (WeaponEquipped == nullptr) return;

	bool RS = WeaponEquipped->IsA(ACRifleStaff::StaticClass());
	// Rifle Staff No Switch Weapon When Attacking
	if (RS && (!GetState(PLAYER_AIMING) && GetState(PLAYER_ATTACKING))) return;
	//if (!RS && GetState(PLAYER_ATTACKING)) return;
	// Rifle Staff General Input Check
	if (RS && !PlayerInputCheck(PLAYER_INPUT_TYPE_CLICK)) return;

	AttackResult AR = AttackResult();
	IIWeapon* IWeaponEquipped = Cast<IIWeapon>(WeaponEquipped);
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetController());

	if (IWeaponEquipped == nullptr || UIController == nullptr) return;

	if (RS)
	{
		if (!UIController->GetWeaponChangeReady())
		{
			UE_LOG(LogTemp, Log, TEXT("Weapon Change Is Not Ready"));
			return;
		}
		IWeaponEquipped->Tab_Triggered(AR);

		if (!GetState(PLAYER_ROLLING)) BulletChange.Execute();
		UIController->SetAimSpriteColorOverlay(IWeaponEquipped->GetWeaponMode());
		UIController->DoRifleSelectBarrelRoll();
	}
	else if (WeaponEquipped->IsA(ACBattleStaff::StaticClass()))
	{
		//if (!UIController->GetWeaponChangeReady())
		//{
		//	UE_LOG(LogTemp, Log, TEXT("Weapon Change Is Not Ready"));
		//	return;
		//}
		IWeaponEquipped->Tab_Triggered(AR);
		//if (AR.Succeeded)
		//{
		//	SwitchBruteMode(IWeaponEquipped->GetWeaponMode() <= 0);
		//	UIController->SetAimSpriteColorOverlay(-1.f);
		//}
	}
}

void ACPlayerCharacter::QCompleted()
{
	if (!GetState(PLAYER_ATTACKING))
	{
		if (UltGauge < 100.f) return;
		if (WeaponEquipped != nullptr)
		{
			AttackResult AR = AttackResult();
			if (IIWeapon* IWeaponEquipped = Cast<IIWeapon>(WeaponEquipped)) IWeaponEquipped->Ult_Triggered(AR);
			StaminaSpend(AR.StaminaUsed);

			UltGauge = 0.f;

			if (IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetController()))
			{
				UIController->SetCenterProgress(UltGauge / 100.f);
			}

			SetState(PLAYER_ULT_INVINCIBLE, true);
		}
	}
}

void ACPlayerCharacter::ItemUsageAction(int32 ItemType)
{
	if (ItemType < 0) return;

	switch(ItemType)
	{
	case(ITEM_TYPE_POTION):
		if (Drink.ExecuteIfBound())
		{
			SetState(PLAYER_DRINKING_POTION, true);
			GetWorld()->GetTimerManager().SetTimer(PotionTimerHandle, FTimerDelegate::CreateLambda([&] {
				SetState(PLAYER_DRINKING_POTION, false);
				}), 2.f, false);
		}
		break;
	default:
		UE_LOG(LogTemp, Log, TEXT("No Action Found On Item Type : %d"), ItemType);
		break;
	}
}

void ACPlayerCharacter::Heal(float HealPoint)
{
	HP += HealPoint;
	if (HP > MaxHP) HP = MaxHP;
}

void ACPlayerCharacter::Equip(AActor& ActorToEquip)
{
	IIWeapon* WTE = Cast<IIWeapon>(&ActorToEquip);
	if (WTE == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ACPlayerCharacter - ActorToEquip Is Not Weapon"));
		return;
	}
	FName AttachSocket = MeleeSocket;
	
	// Rifle Staff Equipped
	if (ACRifleStaff* Rifle = Cast<ACRifleStaff>(&ActorToEquip))
	{
		AttachSocket = RifleSocket;
		//UE_LOG(LogTemp, Log, TEXT("ACPlayerCharacter Equip : Binding Lambda To Rifle->BulletCountUpdated"));
		Rifle->BulletCountUpdated.BindLambda([&](float NewPercent) {
			IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetController());
			//UE_LOG(LogTemp, Log, TEXT("ACPlayerCharacter : Set NewPercent : %f"), NewPercent);
			if (UIController == nullptr) return;
			UIController->SetAimProgressBarPercent(NewPercent);
			}
		);
	}
	// Default Battle Staff Equip
	ActorToEquip.AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), AttachSocket);
	CurrentWeaponMode = WeaponSocket;
	UE_LOG(LogTemp, Log, TEXT("Equiped %s"), *ActorToEquip.GetName());
	WeaponEquipped = &ActorToEquip;
	IsWeaponEquiped = true;
	ActorToEquip.SetOwner(this);

	WTE->OnEquipped();
	OnWeaponChanged();
}

void ACPlayerCharacter::UnEquip()
{
	WeaponEquipped->Destroy();
	IsWeaponEquiped = false;
}

void ACPlayerCharacter::SwitchBruteMode(bool BruteMode)
{
	if (!WeaponEquipped->IsA(ACBattleStaff::StaticClass())) return;
	IIWeapon* IWeaponEquipped = Cast<IIWeapon>(WeaponEquipped);
	if (IWeaponEquipped == nullptr) return;

	AttackResult AR = AttackResult();
	FName SocketName = BruteMode ? BackSocket : MeleeSocket;
	
	WeaponEquipped->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	WeaponEquipped->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), SocketName);

	if (BruteMode)
	{
		UGameplayStatics::SpawnEmitterAttached(IWeaponEquipped->GetWeaponEffect(E_BRUTEMODE_INIT), GetMesh(), NAME_None, FVector(0.f, 0.f, 0.f), FRotator::ZeroRotator);
		UGameplayStatics::SpawnEmitterAttached(IWeaponEquipped->GetWeaponEffect(E_BRUTEMODE_INIT_LIGHTNING), GetMesh(), NAME_None, FVector(0.f, 0.f, 0.f), FRotator::ZeroRotator);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), IWeaponEquipped->GetWeaponEffect(E_BRUTEMODE_INIT_LIGHTNING_BIG), GetActorLocation() + GetActorUpVector() * -90.f);
			//SpawnEmitterAttached(IWeaponEquipped->GetWeaponEffect(E_BRUTEMODE_INIT_LIGHTNING_BIG), GetMesh(), NAME_None, FVector(0.f, 0.f, 0.f), FRotator::ZeroRotator);
	}
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

	//Exceptions

	switch (StateType)
	{
	case(PLAYER_AIMING):
		bUseControllerRotationYaw = b;
		GetCharacterMovement()->bOrientRotationToMovement = !b;
		if (!b)
		{
			ACRifleStaff* RS = Cast<ACRifleStaff>(WeaponEquipped);
			if (RS != nullptr)
			{
				RS->SetLMBLock(false);
			}
			//AimOff.ExecuteIfBound();
		}
		break;
	default:
		break;
	}
}

bool ACPlayerCharacter::GetKeyState(UINT StateType)
{
	//UE_LOG(LogTemp, Log, TEXT("KeyState : %f"), KeyState);
	if (KeyState & StateType) return true;
	else return false;
}

void ACPlayerCharacter::SetKeyState(UINT StateType, bool b)
{
	if (GetKeyState(StateType) ^ b)
	{
		if (b) KeyState += StateType;
		else KeyState -= StateType;
		//UE_LOG(LogTemp, Log, TEXT("KeyState : %f"), KeyState);
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

	if (!IsAttacked && (!GetState(PLAYER_BRUTEMODE_ORAORA) && !GetState(PLAYER_ULT_INVINCIBLE)))
	{
		GetMesh()->bPauseAnims = true;
		GetWorld()->GetTimerManager().SetTimer(HitReactTimerHandle, this, &ACPlayerCharacter::SetAnimPauseFree, 0.15f);
	}
}

bool ACPlayerCharacter::HitDamage(float e, ACEnemyCharacter* Attacker, FVector HitLocation, int Power)
{
	if (GetState(PLAYER_ROLL_INVINCIBLE))
	{
		if (!GetState(PLAYER_DODGED))
		{
			OnDodgedAttack();
		}
		UE_LOG(LogTemp, Log, TEXT("Player Roll Dodged"));
		return false;
	}
	else if (GetState(PLAYER_RAGDOLL) || GetState(PLAYER_GETTINGUP))
	{
		UE_LOG(LogTemp, Log, TEXT("Player in Ragdoll"));
		return false;
	}
	else if (GetState(PLAYER_ULT_INVINCIBLE))
	{
		UE_LOG(LogTemp, Log, TEXT("Player Using Ult"));
		return false;
	}

	ItemStat CurrStat = ItemStat();

	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetController());
	UIController->EquippedItemStat(CurrStat);

	UE_LOG(LogTemp, Log, TEXT("Player Defence = %f"), CurrStat._Defence);
	float DeffencePer = 1 - (CurrStat._Defence / 500.f);
	if (DeffencePer <= 0.1f) DeffencePer = 0.1f;
	UE_LOG(LogTemp, Log, TEXT("Player Defence Damage = %f"), DeffencePer);
	HP -= (e * DeffencePer);
	SetState(PLAYER_UI_INTERACTING, false);
	SetLastDealingEnemy(Attacker);
	
	UIController->AddRecentDamage(e * DeffencePer / MaxHP);


	ShowDamageUI(e * DeffencePer, HitLocation, true);

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

void ACPlayerCharacter::Grasped(ACharacter& GraspedEnemyCharacter, FName GraspBoneName)
{
	UnarmedOnAir.ExecuteIfBound();
	//GetMesh()->AttachToComponent(GraspedEnemyCharacter.GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, GraspBoneName);
	GetCapsuleComponent()->AttachToComponent(GraspedEnemyCharacter.GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, GraspBoneName);
	//SpringArmComponent->AttachToComponent(GraspedEnemyCharacter.GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, GraspBoneName);
	//SpringArmComponent->TargetArmLength = 1550.f;

	SetState(PLAYER_ROLLING, true);
}

void ACPlayerCharacter::UnGrasp()
{
	//GetMesh()->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	GetCapsuleComponent()->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	//SpringArmComponent->TargetArmLength = 550.f;
	//SpringArmComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	//SpringArmComponent->bUsePawnControlRotation = true;
	//SpringArmComponent->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	SetState(PLAYER_ROLLING, false);
	OnHitDown();
}

void ACPlayerCharacter::OnHitDown()
{
	if (!GetState(PLAYER_RAGDOLL)) //DOWN(RAGDOLL)
	{
		//UE_LOG(LogTemp, Log, TEXT("collision prifile name : %s"), *GetMesh()->GetCollisionProfileName().ToString());

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

		UCapsuleComponent* CapsuleComp = GetCapsuleComponent();

		GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));
		SetActorEnableCollision(true);

		GetMesh()->SetAllBodiesSimulatePhysics(false);
		GetMesh()->SetSimulatePhysics(false);
		GetMesh()->PutAllRigidBodiesToSleep();
		GetMesh()->bBlendPhysics = false;

		GetMesh()->AttachToComponent(CapsuleComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
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
		SetState(PLAYER_AIMING, false);
		StopAnimMontage();
		if (Dizzy.ExecuteIfBound())
		{
			SetState(PLAYER_STAMINA_REGAIN, false);
			SetState(PLAYER_STAMINA_RUNOUT, true);
			SetState(PLAYER_DIZZY, true);
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

void ACPlayerCharacter::DealtDamage(float AttackDamage, float DamageScale, ACharacter* TargetCharacter)
{
	//UltGauge += (FMath::Min(FMath::Floor(AttackDamage / 10.f), 10.f) * DamageScale) * 20.f;
	UltGauge += AttackDamage / 5.f;
	if (UltGauge > 100.f) UltGauge = 100.f;

	if (IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetController()))
	{
		UIController->SetCenterProgress(UltGauge / 100.f);
	}

	if (WeaponEquipped->IsA(ACBattleStaff::StaticClass()))
	{
		if (IsBruteMode()) return;
		IIWeapon* IW = Cast<IIWeapon>(WeaponEquipped);
		if (IW == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("WeaponEquipped Is Not Correct Type"));
			return;
		}
		//IW->AddBruteGauge((FMath::Min(FMath::Floor(AttackDamage / 10.f), 10.f) * (2.f + DamageScale)));
		IW->AddBruteGauge(AttackDamage * 2.5f);
	}
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

FTransform ACPlayerCharacter::GetSocketTransform(FName SocketName)
{
	if (GetMesh() == nullptr) return FTransform();
	return GetMesh()->GetSocketTransform(SocketName);
}

void ACPlayerCharacter::WeaponEffectActivate()
{
	IIWeapon* IW = Cast<IIWeapon>(WeaponEquipped);
	if (IW == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACPlayerCharacter Weapon Not Found"));
		return;
	}
	IW->ActivateEffect();
}

void ACPlayerCharacter::WeaponEffectDeactivate()
{
	IIWeapon* IW = Cast<IIWeapon>(WeaponEquipped);
	if (IW == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACPlayerCharacter Weapon Not Found"));
		return;
	}
	IW->DeactivateEffect();
}

void ACPlayerCharacter::SetWeaponEffectCharge(float e, bool IsLeft)
{
	IIWeapon* IW = Cast<IIWeapon>(WeaponEquipped);
	if (IW == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACPlayerCharacter Weapon Not Found"));
		return;
	}
	IW->SetCharge(e, IsLeft);
}

void ACPlayerCharacter::BruteRushContinue()
{
	if (GetState(PLAYER_DIED)) return;

	if (!WeaponEquipped->IsA(ACBattleStaff::StaticClass())) return;
	if (GetState(PLAYER_BRUTEMODE_ORAORA))
	{
		BruteRush0.Execute(BruteRushComboCounter < 1 ? true : false);
		BruteRushComboCounter += 1;
	}
	else
	{
		if (IsBruteMode() && BruteRushComboCounter > 0)
		{
			FinishPunch.Execute();
		}
		//else
		//{
		//	SetState(PLAYER_ATTACKING, false);
		//}
		BruteRushComboCounter = 0;
	}

	//float e = FMath::FRandRange(0.f, 1.f);
	//if (e > 0.2f)
	//{
	//}
	//UE_LOG(LogTemp, Log, TEXT("e : %f, %d"), e, int32(e * 100.f) % 20 / 4);
}

bool ACPlayerCharacter::IsBruteMode()
{
	if (WeaponEquipped == nullptr) return false;
	if (!WeaponEquipped->IsA(ACBattleStaff::StaticClass())) return false;
	if (ACBattleStaff* BS = Cast<ACBattleStaff>(WeaponEquipped))
	{
		return BS->GetBruteMode();
	}
	return false;
}

void ACPlayerCharacter::ThrowStaffEffect()
{
	if (WeaponEquipped == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Weapon Not Found"));
		return;
	}
	if (!WeaponEquipped->IsA(ACBattleStaff::StaticClass()))
	{
		UE_LOG(LogTemp, Error, TEXT("Weapon Is Not BattleStaff"));
		return;
	}
	IIWeapon* IW = Cast<IIWeapon>(WeaponEquipped);
	if (IW == nullptr) return;
	
	IW->UltFunc0();
}

void ACPlayerCharacter::TurnBruteMode()
{
	if (WeaponEquipped == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Weapon Not Found"));
		return;
	}
	if (!WeaponEquipped->IsA(ACBattleStaff::StaticClass()))
	{
		UE_LOG(LogTemp, Error, TEXT("Weapon Is Not BattleStaff"));
		return;
	}
	IIWeapon* IW = Cast<IIWeapon>(WeaponEquipped);
	if (IW == nullptr) return;
	if (IW->GetBruteGauge() < 1.f) return;

	SwitchBruteMode(true);
	IW->UltFunc1();
}

void ACPlayerCharacter::Ult_ThrowStaffEffectDirect()
{
	if (!GetState(PLAYER_ULT_INVINCIBLE)) return;
	if (WeaponEquipped == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Weapon Not Found"));
		return;
	}
	if (!WeaponEquipped->IsA(ACBattleStaff::StaticClass()))
	{
		UE_LOG(LogTemp, Error, TEXT("Weapon Is Not BattleStaff"));
		return;
	}
	IIWeapon* IW = Cast<IIWeapon>(WeaponEquipped);
	if (IW == nullptr) return;

	IW->AddBruteGauge(300.f);
	SwitchBruteMode(true);
	IW->UltFunc2();
}

void ACPlayerCharacter::Ult_Jump()
{
	if (!GetState(PLAYER_ULT_INVINCIBLE)) return;

	UnarmedJump.Execute();
}

void ACPlayerCharacter::Ult_PunchInit()
{
	if (!GetState(PLAYER_ULT_INVINCIBLE)) return;

	if (WeaponEquipped == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Weapon Not Found"));
		return;
	}
	if (!WeaponEquipped->IsA(ACBattleStaff::StaticClass()))
	{
		UE_LOG(LogTemp, Error, TEXT("Weapon Is Not BattleStaff"));
		return;
	}
	IIWeapon* IW = Cast<IIWeapon>(WeaponEquipped);
	if (IW == nullptr) return;
	FTransform Playertransform = GetActorTransform();
	Playertransform.SetLocation(Playertransform.GetLocation() + FVector(0.f, 0.f, -90.f));
	IW->SpawnWeaponEffect(E_ULT_JUMP, Playertransform, 0.f);

	//SetState(PLAYER_BS_JUMP_UP, true);

	LaunchCharacter(GetActorUpVector() * 1500.f, false, true);

	// Punch Initiate
	UltFinishPunch.Execute();

	OverrideBoneTransform.Execute(PLAYER_MESH_BONE_SPINE1, FRotator(0.f, 0.f, 15.f));
	OverrideBoneTransform.Execute(PLAYER_MESH_BONE_SPINE2, FRotator(0.f, 0.f, 15.f));
}

void ACPlayerCharacter::Ult_Airbone()
{
	if (!GetState(PLAYER_ULT_INVINCIBLE)) return;

	//SetState(PLAYER_BS_JUMP_UP, false);

	GetCharacterMovement()->GravityScale = 0.1f;
	GetMovementComponent()->StopMovementImmediately();

	UnarmedOnAir.Execute(); // Airbone Anim Loop
}

void ACPlayerCharacter::Ult_Land()
{
	if (!GetState(PLAYER_ULT_INVINCIBLE)) return;

	if (WeaponEquipped == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Weapon Not Found"));
		return;
	}
	if (!WeaponEquipped->IsA(ACBattleStaff::StaticClass()))
	{
		UE_LOG(LogTemp, Error, TEXT("Weapon Is Not BattleStaff"));
		return;
	}
	IIWeapon* IW = Cast<IIWeapon>(WeaponEquipped);
	if (IW == nullptr) return;

	// Get Launch Direction
	FVector Destination;
	FVector Direction;
	IW->GetCurrentHammerEffectLocation(Destination);
	if (!Destination.IsZero())
	{
		Direction = (Destination - GetActorLocation()).GetSafeNormal();
	}
	else
	{
		Direction = GetActorForwardVector() + GetActorUpVector() * -1.f;
	}

	// Leap Effect
	FTransform Playertransform = GetActorTransform();
	Playertransform.SetLocation(Playertransform.GetLocation() + FVector(0.f, 0.f, -90.f));

	Playertransform.SetRotation(FQuat(Direction.Rotation()));
	IW->SpawnWeaponEffect(E_ULT_JUMP_AIR, Playertransform, 0.f);

	LaunchCharacter(Direction * 3000.f, false, true);
	GetCharacterMovement()->GravityScale = 1;

	GetMesh()->bPauseAnims = true;
	GetWorld()->GetTimerManager().ClearTimer(HitReactTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(HitReactTimerHandle, FTimerDelegate::CreateLambda(
		[&]	{
			SetAnimPauseFree();
		}), 0.15f, false
	);
	UltLand.ExecuteIfBound();

	OverrideBoneTransform.Execute(PLAYER_MESH_BONE_SPINE1, FRotator(0.f, 0.f, 30.f));
	OverrideBoneTransform.Execute(PLAYER_MESH_BONE_SPINE2, FRotator(0.f, 0.f, 30.f));

}

void ACPlayerCharacter::Ult_HitGround()
{
	if (!GetState(PLAYER_ULT_INVINCIBLE)) return;

	if (WeaponEquipped == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Weapon Not Found"));
		return;
	}
	if (!WeaponEquipped->IsA(ACBattleStaff::StaticClass()))
	{
		UE_LOG(LogTemp, Error, TEXT("Weapon Is Not BattleStaff"));
		return;
	}
	IIWeapon* IW = Cast<IIWeapon>(WeaponEquipped);
	if (IW == nullptr) return;
	FTransform EffectSpawnTransform = GetActorTransform();
	EffectSpawnTransform.SetLocation(EffectSpawnTransform.GetLocation() + GetActorUpVector() * -90.f);

	IW->SpawnWeaponEffect(E_ULT_HITGROUND, EffectSpawnTransform, 1.5f);
	IW->PlaySoundEffect(SE_ULT_HITGROUND_A, EffectSpawnTransform.GetLocation());
	IW->MeleeAttackHitCheck(4, 2.5f, 300.f);

	GetMesh()->bPauseAnims = true;
	GetWorld()->GetTimerManager().ClearTimer(HitReactTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(HitReactTimerHandle, FTimerDelegate::CreateLambda(
		[&] {
			IIWeapon* IW = Cast<IIWeapon>(WeaponEquipped);
			if (IW == nullptr) return;
			FTransform EffectSpawnTransform = GetActorTransform();
			EffectSpawnTransform.SetLocation(EffectSpawnTransform.GetLocation() + GetActorUpVector() * -90.f);
			EffectSpawnTransform.SetScale3D(FVector(2.f));
			IW->SpawnWeaponEffect(E_ULT_HITGROUND, EffectSpawnTransform, 1.5f);
			IW->PlaySoundEffect(SE_ULT_HITGROUND_B, EffectSpawnTransform.GetLocation(), 1.2f);
			IW->MeleeAttackHitCheck(4, 3.f, 500.f);
			SetAnimPauseFree();
			Ult_Backflip();
		}), 0.25f, false
	);
}

void ACPlayerCharacter::Ult_Backflip()
{
	if (!GetState(PLAYER_ULT_INVINCIBLE)) return;

	if (WeaponEquipped == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Weapon Not Found"));
		return;
	}
	if (!WeaponEquipped->IsA(ACBattleStaff::StaticClass()))
	{
		UE_LOG(LogTemp, Error, TEXT("Weapon Is Not BattleStaff"));
		return;
	}
	IIWeapon* IW = Cast<IIWeapon>(WeaponEquipped);
	if (IW == nullptr) return;

	IW->UltFunc3();

	OverrideBoneTransform.Execute(PLAYER_MESH_BONE_SPINE1, FRotator(0.f, 0.f, 0.f));
	OverrideBoneTransform.Execute(PLAYER_MESH_BONE_SPINE2, FRotator(0.f, 0.f, 0.f));

	Backflip.Execute();
	
	//SetState(PLAYER_ULT_INVINCIBLE, false);
}

void ACPlayerCharacter::SwitchWeaponHoldingHand(bool ToLeft)
{
	WeaponEquipped->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	WeaponEquipped->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), ToLeft? tempRifleSocket : RifleSocket);
}

void ACPlayerCharacter::SpawnAndGraspBeacon()
{
	IIWeapon* IW = Cast<IIWeapon>(WeaponEquipped);
	if (IW == nullptr || !WeaponEquipped->IsA(ACRifleStaff::StaticClass()))
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponEquipped Is Not Currect Type"));
	}

	IW->UltFunc0();
}

void ACPlayerCharacter::ThrowBeacon()
{
	IIWeapon* IW = Cast<IIWeapon>(WeaponEquipped);
	if (IW == nullptr || !WeaponEquipped->IsA(ACRifleStaff::StaticClass()))
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponEquipped Is Not Currect Type"));
	}

	IW->UltFunc1();
}

float ACPlayerCharacter::GetCameraArmLength()
{
	return SpringArmComponent->TargetArmLength;
}
