#pragma once
#include "CoreMinimal.h"
#include "GunAmmo.generated.h"

UENUM(BlueprintType)

enum class EGunAmmoType : uint8
{
	None       UMETA(DisplayName = "None"),
	pistolAmmo UMETA(DisplayName = "pistolAmmo"),
	shotGunAmmo UMETA(DisplayName = "shotgunAmmo"),
	machineGunAmmo UMETA(DisplayName = "machineGunAmmo")
	
};