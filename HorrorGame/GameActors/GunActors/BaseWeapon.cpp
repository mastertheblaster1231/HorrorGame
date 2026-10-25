// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "HorrorGameCharacter.h"
#include "Components/SphereComponent.h"


// Sets default values
ABaseWeapon::ABaseWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	gunMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	interactionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Gun Collision"));
	interactionSphere->SetupAttachment(gunMeshComponent);
}

void ABaseWeapon::StartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ABaseWeapon::EndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ABaseWeapon::InteractItem_Implementation(AHorrorGameCharacter* playerCharacter)
{
	
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	interactionSphere->OnComponentBeginOverlap.AddDynamic(this,&ABaseWeapon::StartOverlap);
	interactionSphere->OnComponentEndOverlap.AddDynamic(this, &ABaseWeapon::EndOverlap);
}
// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

