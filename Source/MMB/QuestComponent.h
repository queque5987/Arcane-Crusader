// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MMB_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UQuestComponent();

protected:
	virtual void BeginPlay() override;
	void Quest0();
	void Quest1();
	void Quest2();
	void Quest3();
	void Quest4();
	void Quest5();
	void Quest6();
	/*Tutorial 1*/
	void Init_Quest0();
	/*Tutorial 2*/
	void Init_Quest1();
	/*Tutorial 4*/
	void Init_Quest2();
	/*Hunt 1*/
	void Init_Quest3();
	/*Hunt 2*/
	void Init_Quest4();
	/*Hunt 3*/
	void Init_Quest5();
	/*Hunt 4*/
	void Init_Quest6();
	/*Tutorial 5*/
	void Init_Quest7();
	/*Tutorial 6*/
	void Init_Quest8();
	/*Tutorial 7*/
	void Init_Quest9();
private:
	//Deprecated 20240531 Editor Only Function
	AActor* FindActorByLabel(TSubclassOf<AActor> FindClass, FString Label);
	AActor* FindActorByTag(TSubclassOf<AActor> FindClass, FName Tag);
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnQuestCleared(int RewardIndex);
	void OnQuestInitialize(int InitIndex);
		
};
