// Fill out your copyright notice in the Description page of Project Settings.


#include "Eve.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "CharacterBaseComponent.h"
#include "ActionComponent.h"
#include "ChracterMoveComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "Project_Eve_PlayerController.h"

// Sets default values
AEve::AEve()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshTemp(TEXT("/Script/Engine.SkeletalMesh'/Game/Mesh/SK_Eve.SK_Eve'"));

	if (MeshTemp.Succeeded()) {
		GetMesh()->SetSkeletalMesh(MeshTemp.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0,0,-86),FRotator(0,-90,0));

	}
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(CapsuleComp);
	springArmComp->SetRelativeLocation(FVector(0, 60, 80));

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	cameraComp->SetupAttachment(springArmComp);

	BaseComp = CreateDefaultSubobject<UCharacterBaseComponent>(TEXT("BaseComp"));
	ActionComp = CreateDefaultSubobject<UActionComponent>(TEXT("ActionComp"));
	MoveComp = CreateDefaultSubobject<UChracterMoveComponent>(TEXT("MoveComp"));

}

// Called when the game starts or when spawned
void AEve::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* playerContoller=Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* subSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerContoller->GetLocalPlayer());

	if (subSys)
		subSys->AddMappingContext(IMC_Eve,0);
}

// Called every frame
void AEve::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEve::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	auto PlayerInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (PlayerInputComponent) {
		if (InputBindingDelegate.IsBound()) {
			InputBindingDelegate.Broadcast(PlayerInput);
		}
	}
}

