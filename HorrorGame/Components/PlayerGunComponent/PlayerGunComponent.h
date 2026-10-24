// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/GunData.h"
#include "PlayerGunComponent.generated.h"

struct FGunData;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class HORRORGAME_API UPlayerGunComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerGunComponent();
	
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* mainGunComponent;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* secondGunComponent;
	
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* thirdGunComponent;
	
	UPROPERTY(VisibleAnywhere)
	FGunData MainGunData ;

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};