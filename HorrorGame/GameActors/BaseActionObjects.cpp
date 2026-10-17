// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActionObjects.h"
#include "Components/BoxComponent.h"


// Sets default values
ABaseActionObjects::ABaseActionObjects()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InteractionSpace = CreateDefaultSubobject<UBoxComponent>("InteractionSpace");
}


void ABaseActionObjects::InteractPhysicalObject_Implementation()
{
	if (bcaninteact)
	{
		bisInteracting = true;
	}
}

void ABaseActionObjects::DisconnetPhysicalObject_Implementation()
{
	bisInteracting = false;
}

void ABaseActionObjects::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bcaninteact = true;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("can Intreat true"),true);
}

void ABaseActionObjects::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bcaninteact = false;	
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("can Intreact false "),true);
}

// Called when the game starts or when spawned
void ABaseActionObjects::BeginPlay()
{
	Super::BeginPlay();
	InteractionSpace->OnComponentBeginOverlap.AddDynamic(this, &ABaseActionObjects::BeginOverlap);
	InteractionSpace->OnComponentEndOverlap.AddDynamic(this, &ABaseActionObjects::EndOverlap);
	
	MeshComponent =  FindComponentByClass<USkeletalMeshComponent>();
	if (MeshComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Blueprint mesh: %s"), *MeshComponent->GetName());
	}
}

// Called every frame
void ABaseActionObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

