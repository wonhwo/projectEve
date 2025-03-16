// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimEve.h"
#include "Eve.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ChracterMoveComponent.h"
#include "DataManagerComponent.h"

void UAnimEve::NativeBeginPlay()
{
	Eve = Cast<AEve>(TryGetPawnOwner());
	DataComp = Cast<UDataManagerComponent>(Eve->DataManager);
	MoveComp = Cast<UChracterMoveComponent>(Eve->MoveComp);
}

void UAnimEve::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!Eve) return;
	FVector Velocity = Eve->GetVelocity();
	Speed = Velocity.Size2D();
	WalkAngle = CalculateDirection(Velocity, Eve->GetControlRotation());

		ChangeAngle = MoveComp->getAngleDifference();
		StickAngle = MoveComp->getInputAngle();

		ChangeAngle = 0.0f;

		FString StateString = UEnum::GetValueAsString(movementType);
		UE_LOG(LogTemp, Log, TEXT("State: %s"), *StateString);

}
void UAnimEve::NativeInitializeAnimation()
{

}
void UAnimEve::AnimNotify_IdleState()
{
	movementType = EMoveState::IDLE;
}

void UAnimEve::PlayMontage(EMontageType type)
{
}

