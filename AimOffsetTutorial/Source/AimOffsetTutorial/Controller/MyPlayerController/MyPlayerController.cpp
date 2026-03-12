// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MyPlayerController/MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Character/MyCharacter/MyCharacter.h"

AMyPlayerController::AMyPlayerController()
{
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Look);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Fire);
	}
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	MyCharacter = GetPawn<AMyCharacter>();
}

void AMyPlayerController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	if(MyCharacter)
	{
		MyCharacter->StopTurnMontage();
		FRotator Rotation = MyCharacter->GetControlRotation();
		FRotator YawRotation(0, Rotation.Yaw, 0);
		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		MyCharacter->AddMovementInput(ForwardDirection, MovementVector.X);
		MyCharacter->AddMovementInput(RightDirection, MovementVector.Y);
	}
}

void AMyPlayerController::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if(MyCharacter)
	{
		MyCharacter->AddControllerYawInput(LookAxisVector.X);
		MyCharacter->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMyPlayerController::Fire(const FInputActionValue& Value)
{
	MyCharacter->Fire();
}
