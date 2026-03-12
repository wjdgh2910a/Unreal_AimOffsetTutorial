// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class AIMOFFSETTUTORIAL_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	float Speed;
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	float Direction;
	TObjectPtr<class ACharacter> Character;
	TObjectPtr<class UCharacterMovementComponent> CharacterMovement;
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	float AimRotationPitch = {};
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	float AimRotationCurYaw = {};
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	float AimRotationYawOffset = {};
	float TurningCurValue = {};
};
