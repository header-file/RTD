#include "RTDDataTable.h"

URTDDataTable::URTDDataTable()
{
	EnemyDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, *EnemyPath));
}

const FEnemyData* URTDDataTable::GetEnemyRow(FName RowName)
{
	if (EnemyDataTable == NULL) return NULL;

	return EnemyDataTable->FindRow<FEnemyData>(RowName, L"");
}
