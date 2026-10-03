// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickUpObject.generated.h"

UCLASS()
class HORRORGAME_API ABasePickUpObject : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasePickUpObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
