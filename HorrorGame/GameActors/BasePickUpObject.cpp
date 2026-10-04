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

void ABasePickUpObject::InteractItem_Implementation(AHorrorGameCharacter* playerCharacter)
{
	IItemInteract::InteractItem_Implementation(playerCharacter);
	
	if (!bisPicked)
	{
		if (refPlayerCharacter)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red,  FString::Printf(TEXT("Pick Up Working")));
			bisPicked = true;
			refPlayerCharacter->InventoryObjectsMap.FindOrAdd( ItemProperties.itemName,  ItemProperties);
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
			this->itemMesh->SetSimulatePhysics(false);
			this->SetActorEnableCollision(false);
			this->SetActorScale3D(pickedItemScale);
			this->AttachToComponent(refPlayerCharacter->GetMesh(), AttachmentRules, ItemProperties.socketName);
			refPlayerCharacter->pickUpItem = this;
		
		}else
		{
			refPlayerCharacter = Cast<AHorrorGameCharacter>(playerCharacter);
			InteractItem_Implementation(refPlayerCharacter);
		}
		
	}else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red,  FString::Printf(TEXT("Detaching Working")));
		bisPicked = false;
		FDetachmentTransformRules DetachmentTransformRules = FDetachmentTransformRules::KeepRelativeTransform;
		this->DetachFromActor(DetachmentTransformRules);
		this->itemMesh->SetSimulatePhysics(true);
		this->SetActorScale3D(normalItemScale);
		this->SetActorEnableCollision(true);
	}
	
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

