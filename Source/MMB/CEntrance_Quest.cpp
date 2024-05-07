// Fill out your copyright notice in the Description page of Project Settings.


#include "CEntrance_Quest.h"

ACEntrance_Quest::ACEntrance_Quest()
{
	PrimaryActorTick.bCanEverTick = true;

	GateNum = 6;
	GateWidth = 200.f;
	OpenGateSpeed = 120.f;

	Collider = CreateDefaultSubobject<UBoxComponent>(FName("Collider"));
	SetRootComponent(Collider);
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetActorEnableCollision(true);
	Collider->SetBoxExtent(FVector(800.f, 10.f, 800.f));

	ConstructorHelpers::FObjectFinder<UStaticMesh> GatePrag(TEXT("/Game/Isometric_World/Sky_Temple/Meshes/Runes/SM_Temple_Rune_02.SM_Temple_Rune_02"));
	int j = 1;
	float c = 0.f;
	for (int i = 0; i < GateNum; i++)
	{
		UStaticMeshComponent* StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent_") + i);
		StaticMeshComponent->SetStaticMesh(GatePrag.Object);
		StaticMeshComponent->SetupAttachment(Collider);
		FTransform T = FTransform();
		T.SetLocation(FVector(j * c + GateWidth / 2.5, 0.f, 0.f));
		UE_LOG(LogTemp, Log, TEXT("%f"), j * c);
		StaticMeshComponent->SetRelativeTransform((T));

		StaticMeshComponents.Add(StaticMeshComponent);
		j *= -1;
		if (j < 0) c += GateWidth;
		RandomGateOpenSequence.Add(new float());
	}




	EnterCollider = CreateDefaultSubobject<UBoxComponent>(FName("EnterCollider"));

	EnterCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	EnterCollider->SetBoxExtent(FVector(1000.f, 1000.f, 600.f));

	EnterCollider->SetupAttachment(Collider);
	SetActorEnableCollision(true);
}

void ACEntrance_Quest::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACEntrance_Quest::OnGateOverlapBegin);
	EnterCollider->OnComponentBeginOverlap.AddDynamic(this, &ACEntrance_Quest::OnOverlapBegin);
	//EnterCollider->OnComponentEndOverlap.AddDynamic(this, &ACEntrance_Quest::OnOverlapEnd);
}

void ACEntrance_Quest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Log, TEXT("Ticking"));
	for (int i = 0; i < StaticMeshComponents.Num(); i++)
	{
		UStaticMeshComponent* SM = StaticMeshComponents[i];

		float Speed = *RandomGateOpenSequence[i];
		if (Speed < OpenGateSpeed)
		{
			*RandomGateOpenSequence[i] += OpenGateSpeed * DeltaTime;
			continue;
		}
		else Speed = OpenGateSpeed;
		FTransform T = SM->GetRelativeTransform();
		FVector L = T.GetLocation();
		if (OpenGate ? (L.Z <= GateWidth * -3) : (L.Z >= 0)) continue;
		L += FVector(0.f, 0.f, DeltaTime * Speed * (OpenGate ? -1 : 1));
		T.SetLocation(L);
		SM->SetRelativeTransform(T);
	}
}

void ACEntrance_Quest::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(OtherActor))
	{
		if (ACPlayerController* PCC = Cast<ACPlayerController>(PC->GetController()))
		{
			if (PCC->CheckQuest_Cleared(CheckQuest))
			{
				SetOpenGate(true);
			}
		}
	}
}

void ACEntrance_Quest::OnGateOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (DialogueTable == nullptr) return;
	if (!bPrintDialogueRandom) return;
	if (DialogueIndex.Num() <= 0) return;
	if (ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(OtherActor))
	{
		FNPCDialoguesRow* DialogueTableRow = DialogueTable->FindRow<FNPCDialoguesRow>(FName(FString::FormatAsNumber(DialogueIndex[0])), FString(""));

		if (ACPlayerController* PCC = Cast<ACPlayerController>(PC->GetController()))
		{
			PCC->AlertSwingby(3.f, (*DialogueTableRow).NPCDialogue);
		}
		UE_LOG(LogTemp, Log, TEXT("%s : %s"), *(*DialogueTableRow).NPCName.ToString(), *(*DialogueTableRow).NPCDialogue.ToString());
	}
}

void ACEntrance_Quest::SetOpenGate(bool e)
{
	OpenGate = e;
	for (float* Sequence : RandomGateOpenSequence)
	{
		*Sequence = FMath::RandRange(0.f, OpenGateSpeed);
	}
}

//void ACEntrance_Quest::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
	//SetOpenGate(false);
//}
