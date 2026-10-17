// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/EInteractionPhysicalItem.h"
#include "GameFramework/Actor.h"
#include "BaseActionObjects.generated.h"

class UBoxComponent;
UCLASS()
class HORRORGAME_API ABaseActionObjects : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseActionObjects();
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* InteractionSpace;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Properties")
	EItemActionType objectInteractionType; 
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Properties")
	bool bisInteracting;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Properties")
	bool bcaninteact;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* MeshComponent;
	
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	   void InteractPhysicalObject();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	   void DisconnetPhysicalObject();
	
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
