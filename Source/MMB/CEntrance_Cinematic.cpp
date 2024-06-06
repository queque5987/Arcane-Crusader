// Fill out your copyright notice in the Description page of Project Settings.


#include "CEntrance_Cinematic.h"

ACEntrance_Cinematic::ACEntrance_Cinematic() : Super()
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

	ConstructorHelpers::FObjectFinder<UStaticMesh> GatePrag(TEXT("/Game/Isometric_World/Sky_Temple/Meshes/Runes/SM_Temple_Rune_02"));
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

	CinematicCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CinematicCameraComponent"));
	CinematicCameraComponent->SetupAttachment(Collider);
}

void ACEntrance_Cinematic::Tick(float DeltaTime)
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


	if (DoCinematic)
	{
		FTransform CameraTransform = CinematicCameraComponent->GetComponentTransform();

		CameraTransform.SetLocation(
			FMath::Lerp(CameraTransform.GetLocation(), CinematicCameraFixedTransform.GetLocation(), CameraMoveSpeed)
		);
		CameraTransform.SetRotation(
			FMath::Lerp(CameraTransform.GetRotation(), CinematicCameraFixedTransform.GetRotation(), CameraMoveSpeed)
		);

		CinematicCameraComponent->SetWorldTransform(CameraTransform);

		//UE_LOG(LogTemp, Log, TEXT("P : %s ; C : %s"), *CameraTransform.GetLocation().ToString(), *CinematicCameraFixedTransform.GetLocation().ToString());

		if (
			FMath::IsNearlyEqual(CameraTransform.GetLocation().X, CinematicCameraFixedTransform.GetLocation().X, 300.f) &&
			FMath::IsNearlyEqual(CameraTransform.GetLocation().Y, CinematicCameraFixedTransform.GetLocation().Y, 300.f) &&
			FMath::IsNearlyEqual(CameraTransform.GetLocation().Z, CinematicCameraFixedTransform.GetLocation().Z, 300.f)
			)
		{
			DoCinematic = false;
			GetWorld()->GetTimerManager().SetTimer(CinematicTimerHandle, this, &ACEntrance_Cinematic::OnCinematicCameraArrived, CinematicTimelapse);
		}
	}
}

void ACEntrance_Cinematic::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACEntrance_Cinematic::OnGateOverlapBegin);

	EnterCollider->OnComponentBeginOverlap.AddDynamic(this, &ACEntrance_Cinematic::OnOverlapBegin);
	EnterCollider->OnComponentEndOverlap.AddDynamic(this, &ACEntrance_Cinematic::OnOverlapEnd);
}

void ACEntrance_Cinematic::OnGateOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (DialogueTable == nullptr) return;
	if (!bPrintDialogueRandom) return;
	if (DialogueIndex.Num() <= 0) return;
	PC = Cast<ACPlayerCharacter>(OtherActor);
	if (PC == nullptr) return;
	FNPCDialoguesRow* DialogueTableRow = DialogueTable->FindRow<FNPCDialoguesRow>(FName(FString::FormatAsNumber(DialogueIndex[0])), FString(""));

	if (ACPlayerController* PCC = Cast<ACPlayerController>(PC->GetController()))
	{
		PCC->AlertSwingby(3.f, (*DialogueTableRow).NPCDialogue);
	}
	UE_LOG(LogTemp, Log, TEXT("%s : %s"), *(*DialogueTableRow).NPCName.ToString(), *(*DialogueTableRow).NPCDialogue.ToString());
}

void ACEntrance_Cinematic::SetOpenGate(bool e)
{
	OpenGate = e;
	for (float* Sequence : RandomGateOpenSequence)
	{
		*Sequence = FMath::RandRange(0.f, OpenGateSpeed);
	}
}

void ACEntrance_Cinematic::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PC = Cast<ACPlayerCharacter>(OtherActor);
	if (IsValid(PC))
	{
		SetOpenGate(true);
		if (!Used)
		{
			ACPlayerController* PCC = Cast<ACPlayerController>(PC->GetController());
			if (IsValid(PCC))
			{
				FTransform PlayerCameraTransform = PC->CameraComponent->GetComponentTransform();
				CinematicCameraFixedTransform = CinematicCameraComponent->GetComponentTransform();
				CinematicCameraComponent->SetWorldTransform(PlayerCameraTransform);
				PCC->SetViewTargetWithBlend(CinematicCameraComponent->GetOwner());
				DoCinematic = true;
			}
			Used = true;
		}
	}
}

void ACEntrance_Cinematic::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ACPlayerCharacter>(OtherActor)) SetOpenGate(false);
}

void ACEntrance_Cinematic::OnCinematicCameraArrived()
{
	//ACPlayerCharacter* PC = Cast<ACPlayerCharacter>(AC);
	//if (!IsValid(PC))
	//{
	//	UE_LOG(LogTemp, Log, TEXT("Failed To Call Player"));
	//	return;
	//}
	ACPlayerController* PCC = Cast<ACPlayerController>(PC->GetController());
	if (IsValid(PCC))
	{
		UE_LOG(LogTemp, Log, TEXT("Cinematic Camera Arrived"));
		PCC->SetViewTargetWithBlend(PC->CameraComponent->GetOwner());
	}
}
