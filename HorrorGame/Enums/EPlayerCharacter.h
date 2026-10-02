#pragma once
#include "CoreMinimal.h"
#include "EPlayerCharacter.generated.h"
UENUM(BlueprintType)
enum class EPlayerCharacterState : uint8
{
	None    UMETA(DisplayName = "None"),
	Walking UMETA(DisplayName = "Walking"),
	Running UMETA(DisplayName = "Running"),
	Crouch  UMETA(DisplayName = "Crouch"),
};