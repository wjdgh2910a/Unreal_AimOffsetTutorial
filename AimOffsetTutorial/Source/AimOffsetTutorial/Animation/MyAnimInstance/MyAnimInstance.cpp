// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/MyAnimInstance/MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/MyCharacter/MyCharacter.h"

void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<AMyCharacter>(TryGetPawnOwner());
	if(Character)
	{
		CharacterMovement = Character->GetCharacterMovement();
	}
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);	
	if(Character == nullptr || CharacterMovement == nullptr)
	{
		return;
	}

	FVector Velocity = CharacterMovement->Velocity;
	Speed = Velocity.Size2D();
	FRotator Rotation = Character->GetActorRotation();
	Direction = CalculateDirection(Velocity, Rotation);

	GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::Yellow, FString::Printf(TEXT("Speed: %f"), Speed));
	GEngine->AddOnScreenDebugMessage(2, 0.f, FColor::Yellow, FString::Printf(TEXT("Direction: %f"), Direction));

	float AimRotationPrevYaw = AimRotationCurYaw;
	AimRotationCurYaw = Character->GetActorRotation().Yaw;
	AimRotationPitch = Character->GetBaseAimRotation().Pitch;
	if (Speed != 0.f)
	{
		AimRotationYawOffset = 0;
	}
	else
	{
		AimRotationYawOffset -= AimRotationCurYaw - AimRotationPrevYaw;
		AimRotationYawOffset = UKismetMathLibrary::NormalizeAxis(AimRotationYawOffset);
		if(AimRotationYawOffset >= 90.f)
			Character->TurnLeftMontagePlay();
		else if(AimRotationYawOffset <= -90.f)
			Character->TurnRightMontagePlay();

		if(GetCurveValue(TEXT("Turning")) > 0.f)
		{
			float TuringPrevValue = TurningCurValue;
			TurningCurValue = GetCurveValue(TEXT("Rotation"));
			AimRotationYawOffset += TurningCurValue - TuringPrevValue;
			AimRotationYawOffset = FMath::Clamp(AimRotationYawOffset, -90.f, 90.f);
		}
		else
		{
		}
		GEngine->AddOnScreenDebugMessage(3, 0.f, FColor::Yellow, FString::Printf(TEXT("AimRotationYawOffset: %f"), AimRotationYawOffset));
	}


}
