// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClimbComponent.generated.h"

struct FInputActionValue;
class ABaseActionObjects;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)

class HORRORGAME_API UClimbComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UClimbComponent();
	
	UPROPERTY(EditAnywhere, Category = "Interaction")
	ABaseActionObjects* ladderObject;
	
	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	ACharacter* character;
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void StartClimbing();
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void StopClimbing();
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Interaction")
	void ClimbLedge(FVector ClimbLocation);
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void tickClimbComponent(float forwardValue);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float climbInputvalue =0.0f;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ladderheight = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ladderClimbOffset = 200.0f;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
