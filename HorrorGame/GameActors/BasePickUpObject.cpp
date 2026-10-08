// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePickUpObject.h"
#include "HorrorGameCharacter.h"
#include "Components/SphereComponent.h"


// Sets default values
ABasePickUpObject::ABasePickUpObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ItemMesh"));
	
	itemInteractionZone = CreateDefaultSubobject<USphereComponent>(FName("ItemInteractionZone"));
	itemInteractionZone->SetupAttachment(itemMesh);
}

	void ABasePickUpObject::AttachPickedActor(AHorrorGameCharacter* playerCharacter)
	{
		if (playerCharacter)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red,  FString::Printf(TEXT("Pick Up Working")));
			bisPicked = true;
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
			this->itemMesh->SetSimulatePhysics(false);
			this->SetActorEnableCollision(false);
			this->SetActorScale3D(pickedItemScale);
			playerCharacter->InventoryObjectsMap.FindOrAdd( ItemProperties.itemName, this);
			this->AttachToComponent(playerCharacter->GetMesh(), AttachmentRules, ItemProperties.socketName);
			playerCharacter->pickUpItem = this; 
		}
	}

	void ABasePickUpObject::DetachPickedActor(AHorrorGameCharacter* playerCharacter)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red,  FString::Printf(TEXT("Detaching Working")));
		
		bisPicked = false;
		playerCharacter->pickUpItem = nullptr;
	    this->itemMesh->SetVisibility(true);
		FDetachmentTransformRules DetachmentTransformRules = FDetachmentTransformRules::KeepRelativeTransform;
		this->DetachFromActor(DetachmentTransformRules);
		this->itemMesh->SetSimulatePhysics(true);
		this->SetActorScale3D(normalItemScale);
		this->SetActorEnableCollision(true);
	}

	void ABasePickUpObject::InteractItem_Implementation(AHorrorGameCharacter* playerCharacter)
	{
		IItemInteract::InteractItem_Implementation(playerCharacter);
		
		  AttachPickedActor(playerCharacter);
		
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

