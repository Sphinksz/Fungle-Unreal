// Copyright Epic Games, Inc. All Rights Reserved.

#include "FunglePlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "FungleCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "HeadMountedDisplayTypes.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AFunglePlayerController::AFunglePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AFunglePlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void AFunglePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AFunglePlayerController::MoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AFunglePlayerController::MoveRight);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AFunglePlayerController::MoveForward(const FInputActionValue& AxisValue)
{
	APawn* ControlledPawn = GetPawn();
	if (const float DirectionValue = AxisValue.Get<float>(); DirectionValue != 0.0f && ControlledPawn != nullptr)
	{
		const FRotator Rotation = ControlRotation;
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		ControlledPawn->AddMovementInput(Direction, DirectionValue);
	}
}

void AFunglePlayerController::MoveRight(const FInputActionValue& AxisValue)
{
	APawn* ControlledPawn = GetPawn();
	if (const float DirectionValue = AxisValue.Get<float>(); DirectionValue != 0.0f && ControlledPawn != nullptr)
	{
		const FRotator Rotation = ControlRotation;
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		ControlledPawn->AddMovementInput(Direction, DirectionValue);
	}
}
