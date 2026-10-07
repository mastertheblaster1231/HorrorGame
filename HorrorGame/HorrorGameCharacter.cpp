// Copyright Epic Games, Inc. All Rights Reserved.

#include "HorrorGameCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "HorrorGame.h"
#include "Components/InteractionLineTrace.h"
#include "Interfaces/ItemInteract.h"

AHorrorGameCharacter::AHorrorGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	/*Components*/
	InteractionLineTrace = CreateDefaultSubobject<UInteractionLineTrace>(TEXT("InteractionLineTrace"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AHorrorGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started,   this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction,      ETriggerEvent::Triggered, this, &AHorrorGameCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AHorrorGameCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction,   ETriggerEvent::Triggered,this, &AHorrorGameCharacter::Look);
		EnhancedInputComponent->BindAction(RunAction,    ETriggerEvent::Started,  this, &AHorrorGameCharacter::DoRun);
		EnhancedInputComponent->BindAction(RunAction ,   ETriggerEvent::Completed,this, &AHorrorGameCharacter::DoRun);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started,  this, &AHorrorGameCharacter::ToggleCrouch);
		
		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent:: Started , this, &AHorrorGameCharacter::Interact);
		
		//Detach Item
		EnhancedInputComponent->BindAction(DetachAction, ETriggerEvent::Started, this,  &AHorrorGameCharacter::DetachPickedItem);
	}
	else
	{
		UE_LOG(LogHorrorGame, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AHorrorGameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AHorrorGameCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AHorrorGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	/*Crouch Properties*/
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->MaxWalkSpeedCrouched = crouchSpeed;
	GetCharacterMovement()->CrouchedHalfHeight = crouchCapsuleHeight;
}

void AHorrorGameCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)	
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AHorrorGameCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AHorrorGameCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void AHorrorGameCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void AHorrorGameCharacter::DoRun()	
{
	
	if (!bIsRunning)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Running"));
		GetCharacterMovement()->MaxWalkSpeed = runSpeed;
		PlayerActionState = EPlayerCharacterState::Running;
		
	}else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("StopRunning"));
		GetCharacterMovement()->MaxWalkSpeed = walkSpeed; 
		PlayerActionState = EPlayerCharacterState::Walking;
	}
	bIsRunning =!bIsRunning;
	
}

void AHorrorGameCharacter::ToggleCrouch()
{
	if (bIsCrouched)
	{
		UnCrouch();
		PlayerActionState = EPlayerCharacterState::Walking;
		
	}else
	{
		Crouch();
		GetCharacterMovement()->CrouchedHalfHeight = crouchCapsuleHeight;
		PlayerActionState = EPlayerCharacterState::Crouch;
	}
}

void AHorrorGameCharacter::InteractFunction()
{
	FVector playerCameraLocation;
	FRotator playerCameraRotation;
	
	GetController()->GetPlayerViewPoint(playerCameraLocation, playerCameraRotation);
	FVector endLocation = playerCameraLocation + playerCameraRotation.Vector()+( GetFollowCamera()->GetForwardVector()*lineTraceLength);
	TArray<AActor*> IgnoreActors;
	
	if (GetWorld())
	{
		FHitResult HitResult = 
			InteractionLineTrace->ShootTrace(GetWorld(), 
			                                 playerCameraLocation, 
			                                 endLocation,
			                                 TraceTypeQuery1,
			                                 false,
			                                 IgnoreActors,
			                                 EDrawDebugTrace::ForDuration,
			                                 true
			);	
		
		if (HitResult.bBlockingHit)
		{
			AActor* hitActor = HitResult.GetActor();
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red,  FString::Printf(TEXT("%s"), *HitResult.GetActor()->GetName()));
			if (hitActor->GetClass()->ImplementsInterface(UItemInteract::StaticClass()))
			{
				IItemInteract::Execute_InteractItem(hitActor, this);
			}
		}
	}
}

void AHorrorGameCharacter::Interact()
{
	if(pickUpItem == nullptr)
	{
		InteractFunction();
	}else
	{
		pickUpItem->itemMesh->SetVisibility(false);
		InteractFunction();
		/*DetachPickedItem();
		Interact();*/
	}
}

void AHorrorGameCharacter::DetachPickedItem()
{
	GEngine->AddOnScreenDebugMessage(
	-1,
	3.f,
	FColor::Yellow,
	TEXT("X DETACH CALLED")
);
	if (!pickUpItem) return;
	TArray<FName> inventoryObjectsNames;
	//TArray<ABasePickUpObject*> inventoryActorObjects;
	InventoryObjectsMap.GetKeys(inventoryObjectsNames);
	//InventoryObjectsMap.GenerateValueArray(inventoryActorObjects);
	int32  itemIndex =INDEX_NONE;
	
	if (pickUpItem!=nullptr)	
	{
		for (const auto& Item : InventoryObjectsMap)
		{
			if (Item.Key == pickUpItem->ItemProperties.itemName)
			{
				itemIndex =inventoryObjectsNames.Find(Item.Key);	
				pickUpItem->DetachPickedActor(this);
				InventoryObjectsMap.Remove(Item.Key);
				break;	
			}
		}
		if (pickUpItem == nullptr && itemIndex >0 )
		{
			--itemIndex;
			FName itemIndexReferenceName = inventoryObjectsNames[itemIndex];
			if (ABasePickUpObject** newPickUpItem = InventoryObjectsMap.Find(itemIndexReferenceName)){//used Dereference Operator
				pickUpItem = *newPickUpItem;
				pickUpItem->AttachPickedActor(this);
			}
		}
	}
}