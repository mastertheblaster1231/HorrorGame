#pragma once
#include "CoreMinimal.h"
#include "EInteractionPhysicalItem.generated.h"

UENUM(BlueprintType)
enum class EItemActionType : uint8
{
   None        UMETA(DisplayName  = "None" ),
   Climb       UMETA(DisplayName = "Climb" ),
   LowVault    UMETA(DisplayName = "LowVault"),
};