#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "RTDDataTable.generated.h"

USTRUCT(BlueprintType)
struct FEnemyData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		float HP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		float Speed;
};

UCLASS()
class RTD_API URTDDataTable : public UObject
{
	GENERATED_BODY()

public:
	URTDDataTable();
	const FEnemyData* GetEnemyRow(FName RowName);

private:
	const FString EnemyPath = "/Game/BP/Enemies/EnemySheet";
	UDataTable* EnemyDataTable;
};
