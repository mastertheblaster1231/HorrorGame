// Fill out your copyright notice in the Description page of Project Settings.


#include "ClimbComponent.h"
#include "HorrorGameCharacter.h"
#include "GameActors/BaseActionObjects.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UClimbComponent::UClimbComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UClimbComponent::StartClimbing()
{
	if (ladderObject)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("ladder woekingfsafsdfsdfdsafds"),true);
		character = Cast<ACharacter>(GetOwner());		
		if ( character)
		{
			if (AHorrorGameCharacter* playerCharacter = Cast<AHorrorGameCharacter>(character))
			{
				playerCharacter->PlayerActionState = EPlayerCharacterState::Climbing;
				playerCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
				/*climbInputvalue = 1;*/
				FVector setClimbLocation = ladderObject->MeshComponent->GetComponentLocation();
				playerCharacter->GetMovementComponent()->StopMovementImmediately();
				playerCharacter->SetActorLocation(FVector(setClimbLocation.X,setClimbLocation.Y,setClimbLocation.Z+55.0f));
				ladderheight = (ladderheight/1.6)-playerCharacter->GetActorLocation().Z;
				playerCharacter->GetCharacterMovement()->bUseControllerDesiredRotation = false;
				playerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
				
			}
			
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("fuck thats intrsting"),true);
			
		}
	}
}

void UClimbComponent::StopClimbing()
{
	
	if ( character)	
	{
		
		
		character->GetCharacterMovement()->SetMovementMode(MOVE_Falling);
		
		if (AHorrorGameCharacter* playerCharacter = Cast<AHorrorGameCharacter>(character))
		{
			playerCharacter->PlayerActionState = EPlayerCharacterState::Walking;
			playerCharacter->GetCharacterMovement()->bUseControllerDesiredRotation = true;
			playerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
			ladderheight = 0.0f;
		}
		ladderObject = nullptr;
		climbInputvalue = 0.f;
		
		
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("fuck he fell down "),true);
		
		
	}
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Out of box	"),true);
}

void UClimbComponent::ClimbLedge_Implementation(FVector ClimbLocation)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green,
			FString::Printf(TEXT("ClimbLedge running in: %s"), *GetClass()->GetName()));
	}
}

void UClimbComponent::tickClimbComponent(float forwardValue)
{
		if (!ladderObject ||forwardValue == 0.f)  
		{return;}
	if (!character) return;
	
	if (FMath::IsNearlyZero(climbInputvalue))
	{
		return;
	}
	FVector upVector =  ladderObject->GetActorUpVector();	
	if (AHorrorGameCharacter* playerCharacter = Cast<AHorrorGameCharacter>(character))
	{
		if (ladderheight < playerCharacter->GetActorLocation().Z)
		{
			FVector startLocation  = playerCharacter->GetActorLocation()+ playerCharacter->GetActorForwardVector()*60.f+ playerCharacter->GetActorUpVector()*100;
			FVector endLocation = startLocation + (startLocation.UpVector* -100);
			TArray<AActor*> ignoreActors;
			FHitResult hitResult;	
			
			UKismetSystemLibrary::LineTraceSingle(GetWorld() , startLocation, 
				endLocation,
				TraceTypeQuery1,
				false,
				ignoreActors,
				EDrawDebugTrace::ForDuration,
				hitResult,
				true);
			
			if (hitResult.bBlockingHit)
			{
				ClimbLedge(hitResult.ImpactPoint);
			}
		}
	}
		
	character->AddActorWorldOffset(upVector*climbInputvalue*GetWorld()->GetDeltaSeconds()*40.0f, true);
	
}	


// Called when the game starts
void UClimbComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UClimbComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

