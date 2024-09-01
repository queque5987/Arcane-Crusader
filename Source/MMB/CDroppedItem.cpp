// Fill out your copyright notice in the Description page of Project Settings.


#include "CDroppedItem.h"
#include "PCH.h"

// Sets default values
ACDroppedItem::ACDroppedItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComponent);

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Collider->SetSphereRadius(200.f);
	Collider->SetupAttachment(StaticMeshComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> SMFinder(TEXT("/Game/Isometric_World/Sky_Temple/Meshes/Runes/SM_Temple_Rune_Sphere_01"));
	if (SMFinder.Succeeded()) StaticMeshComponent->SetStaticMesh(SMFinder.Object);

	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetCollisionProfileName(TEXT("Item"));
	SetActorScale3D(FVector(0.2f, 0.2f, 0.2f));
	//StaticMeshComponent->SetRelativeScale3D();
	OverlapingPlayerCharacter = nullptr;
}

// Called when the game starts or when spawned
void ACDroppedItem::BeginPlay()
{
	Super::BeginPlay();
	//Collider->OnComponentBeginOverlap.AddDynamic(this, &ACDroppedItem::OnOverlapBegin);
	//Collider->OnComponentEndOverlap.AddDynamic(this, &ACDroppedItem::OnOverlapEnd);
	
	float vDegree = FMath::RandRange(0.f, 30.f);
	float hDegree = FMath::RandRange(0.f, 359.f);
	float V = FMath::DegreesToRadians(vDegree);
	float H = FMath::DegreesToRadians(hDegree);
	float Power = 2.f;
	
	FVector DirNor = FVector(FMath::Sin(V) * FMath::Cos(H), FMath::Sin(V) * FMath::Sin(H), FMath::Cos(V));
	//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + DirNor * Power, FColor::Green, false, 10.f);
	//UE_LOG(LogTemp, Log, TEXT("Force Direction %s"), *DirNor.ToString());
	StaticMeshComponent->AddForce(DirNor * Power);
}

void ACDroppedItem::CheckSweepCharacter()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	FCollisionObjectQueryParams OQP(ECollisionChannel::ECC_Pawn);

	if (GetWorld()->SweepSingleByObjectType(
		HitResult,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		OQP,
		FCollisionShape::MakeSphere(300.f),
		Params
	))
	{	// Player Colided
		if (OverlapingPlayerCharacter != nullptr) return;

		OverlapingPlayerCharacter = Cast<ACPlayerCharacter>(HitResult.GetActor());
		if (OverlapingPlayerCharacter == nullptr) return;
		if (ACPlayerController* PCC = Cast<ACPlayerController>(OverlapingPlayerCharacter->GetController()))
		{
			PCC->ShowDroppedItemList(true, *this, PossessingItem);
		}
		return;
	}
	// Player Dettached
	if (OverlapingPlayerCharacter != nullptr)
	{
		if (ACPlayerController* PCC = Cast<ACPlayerController>(OverlapingPlayerCharacter->GetController()))
		{
			PCC->ShowDroppedItemList(false, *this, PossessingItem);
		}
		OverlapingPlayerCharacter = nullptr;
		return;

	}
}

// Called every frame
void ACDroppedItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckSweepCharacter();
	//DrawDebugSphere(GetWorld(), GetActorLocation(), 300.f, 32.f, FColor::Green);
}

//Deprecated
void ACDroppedItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(OtherActor))
	{
		if (ACPlayerController* PCC = Cast<ACPlayerController>(PC->GetController()))
		{
			PCC->ShowDroppedItemList(true, *this, PossessingItem);
		}
	}
}

//Deprecated
void ACDroppedItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(OtherActor))
	{
		if (ACPlayerController* PCC = Cast<ACPlayerController>(PC->GetController()))
		{
			PCC->ShowDroppedItemList(false, *this, PossessingItem);
			UE_LOG(LogTemp, Log, TEXT("DropItem : EndOverlap"));
		}
	}
}

void ACDroppedItem::SetPossessingItem(UCInventoryItemData& ItemData)
{
	PossessingItem = &ItemData;

	if (AMMBGameModeBase* GM = Cast<AMMBGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		int32 R = ItemData.GetRarity();
		UMaterialInstance* Mat = GM->GetDropItemMaterial(R);
		if (Mat != nullptr)
		{
			//UMaterialInstanceDynamic* MID = UMaterialInstanceDynamic::Create(Mat, StaticMeshComponent);
			//if (MID != nullptr) StaticMeshComponent->SetMaterial(0, MID);
			StaticMeshComponent->SetMaterial(0, Mat);
		}
	}
}
