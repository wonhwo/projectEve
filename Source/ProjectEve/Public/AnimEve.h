// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EMoveState.h"
#include "EMontageType.h"
#include "FMontageEntry.h"
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

	class UChracterMoveComponent* MoveComp;

	class UMontageDataAsset* DataAsset;

	class UDataManagerComponent* DataComp;
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	float WalkForward=0.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	float WalkRight=0.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	float WalkAngle=0.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	float ChangeAngle=0.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	float Speed=0.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	float StickAngle=0.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	EMoveState MoveState;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	float PreviousSpeed = 0.0f;


	EMoveState movementType= EMoveState::IDLE;

public:
	UFUNCTION()
	void AnimNotify_IdleState();




	void PlayMontage(EMontageType type);

};
