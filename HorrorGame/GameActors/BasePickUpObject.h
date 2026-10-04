// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/ItemStruct.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ItemInteract.h"
#include "BasePickUpObject.generated.h"

class AHorrorGameCharacter;
class USphereComponent;
UCLASS()
class HORRORGAME_API ABasePickUpObject : public AActor, public IItemInteract
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasePickUpObject();
	
	UFUNCTION()
	virtual void InteractItem_Implementation(AHorrorGameCharacter* playerCharacter) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* itemMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* itemInteractionZone;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform itemTransformation;
	
#pragma region ObjectProperties
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly , Category = "Properties")
	AHorrorGameCharacter* refPlayerCharacter; //Reference PlayerCharacter
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	FItemProperties ItemProperties;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	FVector normalItemScale = FVector(0.6f, 0.6f, 0.6f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	FVector pickedItemScale = FVector(0.3f, 0.3f, 0.3f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	bool bisPicked;
#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
