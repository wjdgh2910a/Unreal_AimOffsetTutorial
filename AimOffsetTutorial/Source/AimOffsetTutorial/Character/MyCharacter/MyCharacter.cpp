// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyCharacter/MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Animation/AnimMontage.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.f;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SocketOffset = FVector(0.f, 60.f, 80.f);
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacter::Fire()
{
	if(FireMontage && GetMesh()->GetAnimInstance()->Montage_IsPlaying(FireMontage) == false)
	{
		PlayAnimMontage(FireMontage);
	}
}

void AMyCharacter::TurnLeftMontagePlay()
{
	if(TurnLeftMontage/* && GetMesh()->GetAnimInstance()->Montage_IsPlaying(TurnLeftMontage) == false*/)
	{
		if(GetMesh()->GetAnimInstance()->Montage_IsPlaying(TurnLeftMontage) == false)
			PlayAnimMontage(TurnLeftMontage);
		else
		{
			float SequenceLength = TurnLeftMontage->GetPlayLength();
			float CurrentPosition = GetMesh()->GetAnimInstance()->Montage_GetPosition(TurnLeftMontage);

			float RemainingRatio = 1.0f - (CurrentPosition / SequenceLength);

			if (RemainingRatio <= 0.5f)
			{
				PlayAnimMontage(TurnLeftMontage);
			}
		}
	}
}

void AMyCharacter::TurnRightMontagePlay()
{
	if(TurnRightMontage /*&& GetMesh()->GetAnimInstance()->Montage_IsPlaying(TurnRightMontage) == false*/)
	{
		if(GetMesh()->GetAnimInstance()->Montage_IsPlaying(TurnRightMontage) == false)
			PlayAnimMontage(TurnRightMontage);
		else
		{
			float SequenceLength = TurnRightMontage->GetPlayLength();
			float CurrentPosition = GetMesh()->GetAnimInstance()->Montage_GetPosition(TurnRightMontage);

			float RemainingRatio = 1.0f - (CurrentPosition / SequenceLength);

			if (RemainingRatio <= 0.5f)
			{
				PlayAnimMontage(TurnRightMontage);
			}
		}
	}
}

void AMyCharacter::StopTurnMontage()
{
	if(TurnLeftMontage && GetMesh()->GetAnimInstance()->Montage_IsPlaying(TurnLeftMontage))
	{
		GetMesh()->GetAnimInstance()->Montage_Stop(0.2f, TurnLeftMontage);
	}
	if(TurnRightMontage && GetMesh()->GetAnimInstance()->Montage_IsPlaying(TurnRightMontage))
	{
		GetMesh()->GetAnimInstance()->Montage_Stop(0.2f, TurnRightMontage);
	}
}

