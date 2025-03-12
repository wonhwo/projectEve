// Fill out your copyright notice in the Description page of Project Settings.


#include "ChracterMoveComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedPlayerInput.h"
#include "Eve.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AnimEve.h"

// Sets default values for this component's properties
UChracterMoveComponent::UChracterMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UChracterMoveComponent::BeginPlay()
{
	Super::BeginPlay();
	Eve->GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;

	Eve->bUseControllerRotationYaw = false;
	Eve->GetCharacterMovement()->bOrientRotationToMovement = true;

	// ...

}


// Called every frame
void UChracterMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	{
		//플레이어가 바라보는 방향으로 이동하고 카메라 회전에 영향을 받지 않도록 설정함
		FVector WorldDirection = FTransform(Eve->GetControlRotation()).TransformVector(Direction);
		WorldDirection.Z = 0;
		WorldDirection.Normalize();
		Eve->AddMovementInput(WorldDirection,Direction.Size());

		Direction = FVector::ZeroVector;
	}

	//GetMovementAngle();
}

void UChracterMoveComponent::SetupInputBinding(class UEnhancedInputComponent* input)
{
	Super::SetupInputBinding(input);

	input->BindAction(IA_R_Stick, ETriggerEvent::Triggered, this, &UChracterMoveComponent::LookUp);

	input->BindAction(IA_L_Stick, ETriggerEvent::Triggered, this, &UChracterMoveComponent::Move);

	input->BindAction(IA_Jump, ETriggerEvent::Started, this, &UChracterMoveComponent::Jump);

	input->BindAction(IA_L_Stick, ETriggerEvent::Started, this, &UChracterMoveComponent::Movestart);
	input->BindAction(IA_L_Stick, ETriggerEvent::Completed, this, &UChracterMoveComponent::Movestop);

}

void UChracterMoveComponent::LookUp(const struct FInputActionValue& InputValue)
{
	FVector2D valuse = InputValue.Get<FVector2D>();


	FRotator ControlRotation = Eve->GetControlRotation();
	float NewPitch = ControlRotation.Pitch + valuse.Y;

	NewPitch = FMath::Clamp(NewPitch, -35.0f, 35.0f);

	Eve->GetController()->SetControlRotation(FRotator(NewPitch, ControlRotation.Yaw+valuse.X, ControlRotation.Roll));

}

void UChracterMoveComponent::Move(const struct FInputActionValue& InputValue)
{
	FVector2D valuse = InputValue.Get<FVector2D>();
	//방향백터 구하기
	Direction.X = valuse.Y;
	Direction.Y = valuse.X;

	MoveState = EMoveState::WALK;

	FTimerHandle RunCheckTimer;
	//스틱 기울기에 따라 속도 최대치로 도달시 최대치 도달 2초후 하이퍼 달리기 발동
	if (Velocity == Eve->GetMovementComponent()->GetMaxSpeed()) {
		currentTime += GetWorld()->DeltaTimeSeconds;
		isRun = false;

		if (currentTime >= 2)RunCheck();
	}
	//스틱 기울기가 조금이라도 내려가면 하이퍼 달리기 종료
	if(Direction.Size()<=1.0f){
		isRun = true;
		currentTime = 0.0f;
		Eve->GetCharacterMovement()->MaxWalkSpeed = 800;
	}



}
//하이퍼 달리기 발동 함수
void UChracterMoveComponent::RunCheck()
{
	if (isRun)return;
	Eve->GetCharacterMovement()->MaxWalkSpeed = 1600;
	MoveState = EMoveState::RUN;

	UE_LOG(LogTemp, Log, TEXT("Run"));
}

void UChracterMoveComponent::Jump()
{
	Eve->Jump();
}

void UChracterMoveComponent::Movestart()
{
	MoveState = EMoveState::START;

}

void UChracterMoveComponent::Movestop()
{
	MoveState = EMoveState::STOP;
}

void UChracterMoveComponent::GetMovementAngle()
{

	UAnimEve* AnimIn = Cast<UAnimEve>(Eve->GetMesh()->GetAnimInstance());
	AnimIn->MoveState = this->MoveState;

	APlayerController* playerContoller = Cast<APlayerController>(Eve->GetController());

	FVector velocity = Eve->GetVelocity();

	FRotator rot = FRotator(0, Eve->GetControlRotation().Yaw, 0);

	float direction = AnimIn->CalculateDirection(velocity, rot);

	//(UKismetAnimationLibrary::CalculateDirection(velocity, Eve->GetControlRotation()));

	//InputPlayerVector = Eve->GetActorForwardVector();
	//InputCamVector = playerContoller->GetControlRotation().Vector();

	//// 3. 두 벡터 사이의 각도 계산
	//float DotProduct = FVector::DotProduct(InputPlayerVector, InputCamVector);
	//DotProduct = FMath::Clamp(DotProduct, -1.0f, 1.0f);
	//float AngleRadians = FMath::Acos(DotProduct);
	//float AngleDegrees = FMath::RadiansToDegrees(AngleRadians);
	//FVector CrossProduct = FVector::CrossProduct(InputPlayerVector, InputCamVector);
	//float Dir = CrossProduct.Z;

	//if (direction > 0.0f)
	//{
	//	AnimIn->WalkAngle = AngleDegrees;
	//}
	//else if (Dir < 0.0f)
	//{
	//	AnimIn->WalkAngle = -AngleDegrees;
	//}
	//else
	//{
	//	AnimIn->WalkAngle = 0.0f;
	//}

	//UE_LOG(LogTemp, Log, TEXT("%f"), AngleDegrees);
}

