// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EMoveState.h"
#include "AnimEve.generated.h"

/**
 *
 */
UCLASS()
class PROJECTEVE_API UAnimEve : public UAnimInstance
{
	GENERATED_BODY()
private:
	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeInitializeAnimation() override;

private:
	class AEve* Eve;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	float WalkForward;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	float WalkRight;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	float WalkAngle=0.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	float Speed=0.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	EMoveState MoveState;
};
