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
private:
	float currentTime=0.0f;

	bool isRun = true;

	EMoveState MoveState = EMoveState::STOP;

	FVector InputPlayerVector;
	FVector InputCamVector;
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

	void Movestart();

	void Movestop();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void GetMovementAngle();


public:
	UPROPERTY(EditDefaultsOnly,Category="Input")
	class UInputAction* IA_L_Stick;

	UPROPERTY(EditDefaultsOnly,Category="Input")
	class UInputAction* IA_R_Stick;

	UPROPERTY(EditDefaultsOnly,Category="Input")
	class UInputAction* IA_Jump;
};
