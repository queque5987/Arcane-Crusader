#include "CEnemy_Barghest.h"
#include "Materials/Material.h"
#include "CEnemyAIController_Barghest.h"

ACEnemy_Barghest::ACEnemy_Barghest() : Super()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> SMFinder(TEXT("/Game/Enemy/Barghest/Mesh/SK_BARGHEST"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TailFinder(TEXT("/Game/Enemy/Barghest/Mesh/SK_BARGHEST_TAIL"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> ManeFinder(TEXT("/Game/Enemy/Barghest/Mesh/SK_BARGHEST_MANE"));
	
	if (SMFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SMFinder.Object);
		GetMesh()->SetWorldRotation(FRotator(0.f, -90.f, 0.f));
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	}

	SKTailComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TailComponent"));
	SKManeComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ManeComponent"));

	if (TailFinder.Succeeded()) SKTailComponent->SetSkeletalMesh(TailFinder.Object);
	if (ManeFinder.Succeeded()) SKManeComponent->SetSkeletalMesh(ManeFinder.Object);

	SKTailComponent->SetupAttachment(GetMesh());
	SKManeComponent->SetupAttachment(GetMesh());

	SKTailComponent->SetLeaderPoseComponent(GetMesh());
	SKManeComponent->SetLeaderPoseComponent(GetMesh());

	GetCharacterMovement()->MaxWalkSpeed = 200.f;

	AIControllerClass = ACEnemyAIController_Barghest::StaticClass();
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(GetMesh()->GetCollisionObjectType(), ECollisionResponse::ECR_Block);
}

void ACEnemy_Barghest::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FString AnimBPAdderss = "Class'/Game/Enemy/Barghest/Animation/BP_BarghestAnimBP.BP_BarghestAnimBP_C'";
	UClass* tempAnimBP = LoadObject<UClass>(nullptr, *AnimBPAdderss);
	if (!tempAnimBP) return;
	GetMesh()->SetAnimInstanceClass(tempAnimBP);
}

bool ACEnemy_Barghest::AttackHitCheck(int AttackType, float DamageScale)
{
	bool bResult = false;
	TArray<bool> AdditionalResults;
	FVector StartLocation;
	FVector EndLocation;
	float Radius = 0.f;
	FVector Scale = GetActorScale();
	float FScale = (Scale.X + Scale.Y + Scale.Z) / 3;

	StartLocation = GetMesh()->GetBoneLocation("BARGHEST_-Head");
	EndLocation = GetMesh()->GetBoneLocation("BARGHEST_-Head") + GetMesh()->GetRightVector() * 50.f;
	
	Radius = HeadRadius * FScale;

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	FCollisionObjectQueryParams OQP(ECollisionChannel::ECC_Pawn);

	bResult = GetWorld()->SweepSingleByObjectType(
		HitResult,
		StartLocation,
		EndLocation,
		FQuat::Identity,
		OQP,
		FCollisionShape::MakeSphere(Radius),
		Params
	);

	//DrawDebugSphere(GetWorld(), StartLocation, Radius, 32, bResult ? FColor::Green : FColor::Red);
	//DrawDebugSphere(GetWorld(), EndLocation, Radius, 32, bResult ? FColor::Green : FColor::Red);

	if (AdditionalResults.Num() > 0)
	{
		for (bool d : AdditionalResults)
		{
			bResult |= d;
		}
	}

	if (bResult)
	{
		if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(HitResult.GetActor()))
		{
			//UE_LOG(LogTemp, Log, TEXT("Hit At Actor : %s"), *HitResult.GetActor()->GetName());
			PC->HitDamage(AttackDamage * DamageScale, this, HitResult.Location, AttackPower);
		}
	}
	return bResult;
}

void ACEnemy_Barghest::HitDamage(float e, ACharacter& Attacker, FVector HitLocation)
{
	Super::HitDamage(e, Attacker, HitLocation);

	StopAnimMontage();

	DoHitReact.ExecuteIfBound();
}
