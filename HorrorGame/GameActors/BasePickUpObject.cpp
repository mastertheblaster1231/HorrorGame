// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePickUpObject.h"


// Sets default values
ABasePickUpObject::ABasePickUpObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABasePickUpObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePickUpObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

