#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Enums/EPlayerCharacter.h"
#include "GameActors/BasePickUpObject.h"
#include "Structs/ItemStruct.h"
#include "HorrorGameCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;
class UInteractionLineTrace;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class AHorrorGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	
protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* RunAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* CrouchAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InteractAction;
	
	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* DetachAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;
	


public:

	/** Constructor */
	AHorrorGameCharacter();	
#pragma region CharacterMovement
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CharacterMovement")
	float walkSpeed     = 250.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CharacterMovement")
	float runSpeed      = 500.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CharacterMovement")
	float crouchSpeed   =  200.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CharacterMovement")
	float crouchCapsuleHeight= 60.0f;
	

	
#pragma endregion
#pragma region Interactvariables
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interact")
	float lineTraceLength = 200.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interact", meta = (AllowPrivateAccess = "true"))
	ABasePickUpObject* pickUpItem;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Interact")
	TMap<FName, FItemProperties> InventoryObjectsMap;
	
	
#pragma endregion 
#pragma region EnumsRegion
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AnimationStates")
	EPlayerCharacterState PlayerActionState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AnimationStates")
	EPlayersPresentWeapon PlayersPresentWeapon;
	

	
#pragma  endregion 
	
#pragma region Components
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInteractionLineTrace* InteractionLineTrace;
#pragma endregion
	
	
protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:
	
	UFUNCTION(BlueprintCallable)
	virtual void BeginPlay() override;

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();
	
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoRun();
	
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void ToggleCrouch();
	
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void Interact();
	
	UFUNCTION(BlueprintCallable)
	virtual void DetachPickedItem();

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
private:
	bool bIsRunning;
};

