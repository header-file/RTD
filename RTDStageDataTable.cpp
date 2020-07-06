#include "RTDStageDataTable.h"

URTDStageDataTable::URTDStageDataTable()
{
	StageDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, *StagePath));
}

const FStageData * URTDStageDataTable::GetStageRow(FName RowName)
{
	if (StageDataTable == NULL) return NULL;

	return StageDataTable->FindRow<FStageData>(RowName, L"");
}
