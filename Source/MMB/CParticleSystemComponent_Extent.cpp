// Fill out your copyright notice in the Description page of Project Settings.


#include "CParticleSystemComponent_Extent.h"

bool UCParticleSystemComponent_Extent::operator<(const UCParticleSystemComponent_Extent* Other) const
{
	return this->GetLifeSpan() < Other->GetLifeSpan();
}

UCParticleSystemComponent_Extent::UCParticleSystemComponent_Extent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bAutoActivate = false;
	SetComponentTickEnabled(true);
}

void UCParticleSystemComponent_Extent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsActive() && LifeSpan <= 0.f)
	{
		Deactivate();
	}
	if (!IsActive() && LifeSpan <= -300.f)
	{
		DestroyComponent();
	}
	LifeSpan -= DeltaTime;
}

