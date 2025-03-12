// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimEve.h"
#include "Eve.h"

void UAnimEve::NativeBeginPlay()
{
	Eve = Cast<AEve>(TryGetPawnOwner());

}

void UAnimEve::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!Eve) return;
	FVector Velocity = Eve->GetVelocity();
	Speed = Velocity.Size2D();

	WalkForward = FVector::DotProduct(Velocity, Eve->GetActorForwardVector() / 800.0f);

	WalkRight = FVector::DotProduct(Velocity, Eve->GetActorRightVector() / 800.0f);

	WalkAngle = CalculateDirection(Velocity, Eve->GetControlRotation());
}

void UAnimEve::NativeInitializeAnimation()
{

}
