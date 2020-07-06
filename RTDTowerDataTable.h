#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "RTDTowerDataTable.generated.h"

USTRUCT(BlueprintType)
struct FTowerData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		float Range;
};

UCLASS()
class RTD_API URTDTowerDataTable : public UObject
{
	GENERATED_BODY()
	
public:
	URTDTowerDataTable();
	const FTowerData* GetTowerRow(FName RowName);

private:
	const FString TowerPath = "/Game/Bp/TowerSheet";
	UDataTable* TowerDataTable;
};
