// Fill out your copyright notice in the Description page of Project Settings.


#include "CParticleSystemExplode.h"

UCParticleSystemExplode::UCParticleSystemExplode()
{
	//SetTemplate(ParticleSystem);
}

void UCParticleSystemExplode::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	tempfloat += DeltaTime;
	//UE_LOG(LogTemp, Log, TEXT("Tick Component %f"), tempfloat);
}
