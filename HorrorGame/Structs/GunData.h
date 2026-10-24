#pragma once

#include "CoreMinimal.h"
#include "AmmoStruct.h" // Replace with the header containing EAmmoType
#include "GunData.generated.h"

struct FGunData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    FName GunName = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    float Damage = 20.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    float Range = 10000.0f;

    // Time between shots, in seconds
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    float FireRate = 0.2f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    int32 MagazineSize = 12;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    float ReloadTime = 1.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    EAmmoType AmmoType = EAmmoType::PistolAmmo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    float Spread = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    int32 PelletsPerShot = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    bool bAutomatic = false;
};