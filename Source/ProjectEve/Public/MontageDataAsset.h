// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FMontageEntry.h"
#include "EMontageType.h"
#include "MontageDataAsset.generated.h"
/**
 *
 */
UCLASS(BlueprintType)
class PROJECTEVE_API UMontageDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TMap<EMontageType, FMontageEntry> MontageDataAsset;
};