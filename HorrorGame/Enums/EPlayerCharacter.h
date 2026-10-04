#pragma once
#include "CoreMinimal.h"
#include "EPlayerCharacter.generated.h"
UENUM(BlueprintType)
enum class EPlayerCharacterState : uint8
{
	None     UMETA(DisplayName = "None"),
	Walking  UMETA(DisplayName = "Walking"),
	Running  UMETA(DisplayName = "Running"),
	Crouch   UMETA(DisplayName = "Crouch"),
	Climbing UMETA(DisplayName = "Climbing"),
};

/*Present Weapon User using..*/
UENUM(BlueprintType)
enum class EPlayersPresentWeapon: uint8
{
	None       UMETA(DisplayName = "None"),
	Pistol     UMETA(DisplayName = "Pistol"),
	ShotGun    UMETA(DisplayName = "ShotGun"),
	MachineGun UMETA(DisplayName = "MachineGun")
	
};