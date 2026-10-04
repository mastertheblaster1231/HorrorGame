// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "InteractionLineTrace.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HORRORGAME_API UInteractionLineTrace : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractionLineTrace();
	
	FHitResult ShootTrace(const UObject* WorldContextObject,
const FVector Start,
const FVector End,
ETraceTypeQuery TraceChannel,
bool bTraceComplex,
const TArray< AActor* >& ActorsToIgnore, 
EDrawDebugTrace::Type DrawDebugType,
bool bIgnoreSelf);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
