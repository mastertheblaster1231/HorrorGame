#pragma once
#include "CoreMinimal.h" 
#include "ItemStruct.generated.h"

USTRUCT(BlueprintType)
struct FItemProperties{

GENERATED_BODY()

public :
 UPROPERTY(EditAnywhere, BlueprintReadWrite)
 FName itemName = NAME_None;
 
 UPROPERTY(EditAnyWhere, BlueprintReadWrite)
 FName socketName = NAME_None;
 
 UPROPERTY(EditAnywhere, BlueprintReadWrite)
 int32 itemQuantity = 1;
 
 UPROPERTY(EditAnywhere, BlueprintReadWrite)
 UStaticMesh* itemMesh= nullptr;
 
 UPROPERTY(EditAnywhere, BlueprintReadWrite)
 USkeletalMesh* itemSkeletalMesh = nullptr;
 
 UPROPERTY(EditAnywhere, BlueprintReadWrite)
 UTexture2D* Thumbnail = nullptr;
};