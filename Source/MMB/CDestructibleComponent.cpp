#include "CDestructibleComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "PCH.h"

UCDestructibleComponent::UCDestructibleComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetupAttachment(GetAttachParent());
	CollisionBody = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Body"));
	CollisionBody->SetupAttachment(this);
}

void UCDestructibleComponent::BeginPlay()
{
	Super::BeginPlay();
	UGeometryCollectionComponent* SMC = Cast<UGeometryCollectionComponent>(GetAttachParent());
	if (SMC == nullptr) return;
	//SMC->Collision
	CollisionBody->OnComponentBeginOverlap.AddDynamic(this, &UCDestructibleComponent::OnOverlap);
	CollisionBody->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel1, ECollisionResponse::ECR_Overlap);
	CollisionBody->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2, ECollisionResponse::ECR_Overlap);
	SMC->SetSimulatePhysics(false);

	UE_LOG(LogTemp, Log, TEXT("UCDestructibleComponent : %s"), *GetAttachParent()->GetName());
}

void UCDestructibleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCDestructibleComponent::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->IsA(ACEnemyCharacter::StaticClass())) return;

	UGeometryCollectionComponent* SMC = Cast<UGeometryCollectionComponent>(GetAttachParent());
	if (SMC == nullptr) return;
	SMC->SetSimulatePhysics(true);
	SMC->AddImpulse((SMC->GetComponentLocation() - OtherActor->GetActorLocation()).GetSafeNormal2D() * 300.f, NAME_None, true);
	CollisionBody->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel1, ECollisionResponse::ECR_Ignore);
	CollisionBody->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2, ECollisionResponse::ECR_Ignore);
	SMC->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel1, ECollisionResponse::ECR_Ignore);
	SMC->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2, ECollisionResponse::ECR_Ignore);
	
	GetWorld()->GetTimerManager().SetTimer(LifetimeHandle, FTimerDelegate::CreateLambda([&] {
		UGeometryCollectionComponent* SMC = Cast<UGeometryCollectionComponent>(GetAttachParent());
		//UE_LOG(LogTemp, Log, TEXT("UCDestructibleComponent No Move Simulate"));
		if (SMC == nullptr) return;
		SMC->SetSimulatePhysics(false);
		}), 3.f, false);
	//SMC->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}


