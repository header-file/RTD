// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "RTDStageDataTable.generated.h"

USTRUCT(BlueprintType)
struct FStageData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		FName BPName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		float Count;
};

UCLASS()
class RTD_API URTDStageDataTable : public UObject
{
	GENERATED_BODY()
	
public:
	URTDStageDataTable();
	const FStageData* GetStageRow(FName RowName);

private:
	const FString StagePath = "/Game/BP/StageSheet";
	UDataTable* StageDataTable;
};
