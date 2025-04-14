// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBaseComponent.h"
#include "EMontageType.h"
#include "FMontageEntry.h"
#include "DataManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTEVE_API UDataManagerComponent : public UCharacterBaseComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDataManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    // 데이터 에셋 참조
    UPROPERTY(EditAnywhere, Category = "Animation")
    class UMontageDataAsset* MontageData;
public:
	TMap<EMontageType, FMontageEntry> CachedMontages;

};
