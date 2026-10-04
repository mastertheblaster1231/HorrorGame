// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionLineTrace.h"


// Sets default values for this component's properties
UInteractionLineTrace::UInteractionLineTrace()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

FHitResult UInteractionLineTrace::ShootTrace(const UObject* WorldContextObject, const FVector Start, const FVector End,
	ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore,
	EDrawDebugTrace::Type DrawDebugType, bool bIgnoreSelf)
{
	FHitResult HitResult;
	UKismetSystemLibrary::LineTraceSingle(WorldContextObject, 
		Start, 
		End,
		TraceChannel,
		bTraceComplex,
		ActorsToIgnore,
		DrawDebugType,
		HitResult,
		bIgnoreSelf);
	return HitResult;
}


// Called when the game starts
void UInteractionLineTrace::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractionLineTrace::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

