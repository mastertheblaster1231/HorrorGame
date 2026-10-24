#pragma once

#include "CoreMinimal.h"
#include "Enums/GunAmmo.h" // Replace with the header containing EAmmoType
#include "GunData.generated.h"

USTRUCT(BlueprintType)
struct FGunData
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    FName GunSocketName;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    FTransform GunTransform;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    FName GunName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    float Damage ;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    float Range ;

    // Time between shots, in seconds
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    float FireRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    int32 MagazineSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    float ReloadTime ;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
     EGunAmmoType AmmoType = EGunAmmoType::None;
     
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    float Spread;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    int32 PelletsPerShot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    bool bAutomatic ;
};