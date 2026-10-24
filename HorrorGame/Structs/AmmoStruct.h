#pragma once
#include "CoreMinimal.h" 
#include "Enums/GunAmmo.h"
#include "AmmoStruct.generated.h"

USTRUCT(BlueprintType)
struct FGunAmmoProperties
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EGunAmmoType AmmoType;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 AmmoCount;
	
};