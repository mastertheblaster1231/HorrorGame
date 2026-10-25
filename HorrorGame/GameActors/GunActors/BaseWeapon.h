// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/ItemInteract.h"
#include "Structs/GunData.h"
#include "BaseWeapon.generated.h"

class USphereComponent;
class AHorrorGameCharacter;
UCLASS()
class HORRORGAME_API ABaseWeapon : public AActor, public IItemInteract
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeapon();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* interactionSphere;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	USkeletalMeshComponent* gunMeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	FGunData gun_Properties;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties")
	AHorrorGameCharacter* player_Character;
	
	
#pragma region GunFunctions
	
	
	UFUNCTION()
	void StartOverlap( UPrimitiveComponent* OverlappedComponent, AActor*OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
	void EndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	/*	
	UFUNCTION(BlueprintCallable)
	void AttachGun(FName SocketName);
	*/
	virtual void InteractItem_Implementation(AHorrorGameCharacter* playerCharacter) override;

#pragma endregion

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
