// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionLineTrace.h"
#include "Components/ClimbComponent/ClimbComponent.h"
#include "HorrorGameCharacter.h"
#include "GameActors/BaseActionObjects.h"


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
	EDrawDebugTrace::Type DrawDebugType, bool bIgnoreSelf , ACharacter* character)
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
	if (HitResult.bBlockingHit)
	{
		ABaseActionObjects* Object = Cast<ABaseActionObjects>(HitResult.GetActor());
		if (Object)
		{
			Object->InteractPhysicalObject_Implementation();
			if (Object->bisInteracting)
			{
				switch (Object->objectInteractionType)
				{
				case EItemActionType::Climb :
					{
						UClimbComponent* climbComponent =character->FindComponentByClass<UClimbComponent>();
						if (character &&  climbComponent)
						{
							GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT(" INteraction Workking"),true);
							climbComponent->ladderObject = Object;
							climbComponent->ladderheight = Object->GetActorScale().Z*100.0;
							climbComponent->StartClimbing();
						}
						break;
					}
					
					default:
					break;
				}
	
			}
		}	
	}
	
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

	// ..
}