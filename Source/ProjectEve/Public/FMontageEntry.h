#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Animation/AnimMontage.h"
#include "EMontageType.h"
#include "FMontageEntry.generated.h"
/**
 *
 */
USTRUCT(BlueprintType)
struct FMontageEntry:public FTableRowBase
{
    GENERATED_BODY()

    // 몽타주 식별 이름 (예: "Move_DashLeft", "Weapon_Attack")
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
    FName MontageName;

    // 몽타주 애셋 참조
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
    UAnimMontage* MontageAsset;

    // 몽타주 타입
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
    EMontageType MontageType;

    //// 방향 범위 (Movement 타입에만 적용, -1~1)
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage", meta = (EditCondition = "MontageType == EMontageType::Movement"))
    //float MinDirection = -1.0f;

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage", meta = (EditCondition = "MontageType == EMontageType::Movement"))
    //float MaxDirection = 1.0f;

    // 재생 속도
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
    float PlayRate = 1.0f;
};