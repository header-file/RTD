#include "RTDTowerDataTable.h"

URTDTowerDataTable::URTDTowerDataTable()
{
	TowerDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, *TowerPath));
}

const FTowerData * URTDTowerDataTable::GetTowerRow(FName RowName)
{
	if (TowerDataTable == NULL) return NULL;

	return TowerDataTable->FindRow<FTowerData>(RowName, L"");
}
