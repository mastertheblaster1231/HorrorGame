// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGunComponent.h"


// Sets default values for this component's properties
UPlayerGunComponent::UPlayerGunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	mainGunComponent =CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Main_Gun"));
	secondGunComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Second_Gun"));
	thirdGunComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Third_Gun"));
	

	// ...
}


// Called when the game starts
void UPlayerGunComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerGunComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

