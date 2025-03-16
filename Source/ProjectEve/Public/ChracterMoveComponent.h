// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterBaseComponent.h"
#include "EMoveState.h"
#include "ChracterMoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTEVE_API UChracterMoveComponent : public UCharacterBaseComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UChracterMoveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	float getCharacterAngle() { return CurrentCharacterAngle; };
	float getInputAngle() { return StickMagnitude; };
	float getAngleDifference() { return AngleDifference; };

private:
	float currentTime=0.0f;

	bool isRun = true;

	float CurrentCharacterAngle=0.0f;

	float InputAngle =0.0f;

	float AngleDifference =0.0f;

	float StickMagnitude = 0.0f;

    FVector PreviousVelocity;

    float PreviousSpeed;

    float Acceleration; //가속도


protected:
	//인풋 바인딩 함수
	void SetupInputBinding(class UEnhancedInputComponent* input) override;

private:
	//카메라 시선 입력 함수
	void LookUp(const struct FInputActionValue& InputValue);

	//캐릭터 무브 입력 함수
	void Move(const struct FInputActionValue& InputValue);

	void RunCheck();

	void Jump();

	void OnMoveStarted(const FInputActionValue& Value);

	void Movestop();

	void StartSprint();


public:
	UPROPERTY(EditDefaultsOnly,Category="Input")
	class UInputAction* IA_L_Stick;

	UPROPERTY(EditDefaultsOnly,Category="Input")
	class UInputAction* IA_R_Stick;

	UPROPERTY(EditDefaultsOnly,Category="Input")
	class UInputAction* IA_Jump;

		UPROPERTY(EditDefaultsOnly,Category="Input")
	class UInputAction* IA_L_StickClick;

		UPROPERTY(EditDefaultsOnly,Category="Input")
	class UInputAction* IA_R_StickClick;
};
