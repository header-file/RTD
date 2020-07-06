#include "RTDStageManager.h"
#include "Engine/World.h"
#include "RTDStageDataTable.h"
#include "RTDEnemy.h"
#include "ConstructorHelpers.h"
#include "TimerManager.h"

ARTDStageManager::ARTDStageManager()
{
 	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<ARTDEnemy> spider1(L"/Game/BP/Enemies/BpCRTDEnemy_Spider.BpCRTDEnemy_Spider_C");
	if (spider1.Succeeded()) EnemyClass[0] = spider1.Class;

	ConstructorHelpers::FClassFinder<ARTDEnemy> spider2(L"/Game/BP/Enemies/BpCRTDEnemy_Spider2.BpCRTDEnemy_Spider2_C");
	if (spider2.Succeeded()) EnemyClass[1] = spider2.Class;

	ConstructorHelpers::FClassFinder<ARTDEnemy> spider3(L"/Game/BP/Enemies/BpCRTDEnemy_Spider3.BpCRTDEnemy_Spider3_C");
	if (spider3.Succeeded()) EnemyClass[2] = spider3.Class;

	ConstructorHelpers::FClassFinder<ARTDEnemy> rlv1(L"/Game/BP/Enemies/BpCRTDEnemy_RLV.BpCRTDEnemy_RLV_C");
	if (rlv1.Succeeded()) EnemyClass[3] = rlv1.Class;

	ConstructorHelpers::FClassFinder<ARTDEnemy> rlv2(L"/Game/BP/Enemies/BpCRTDEnemy_RLV2.BpCRTDEnemy_RLV2_C");
	if (rlv2.Succeeded()) EnemyClass[4] = rlv2.Class;

	ConstructorHelpers::FClassFinder<ARTDEnemy> rlv3(L"/Game/BP/Enemies/BpCRTDEnemy_RLV3.BpCRTDEnemy_RLV3_C");
	if (rlv3.Succeeded()) EnemyClass[5] = rlv3.Class;

	ConstructorHelpers::FClassFinder<ARTDEnemy> drone1(L"/Game/BP/Enemies/BpCRTDEnemy_Drone.BpCRTDEnemy_Drone_C");
	if (drone1.Succeeded()) EnemyClass[6] = drone1.Class;

	ConstructorHelpers::FClassFinder<ARTDEnemy> drone2(L"/Game/BP/Enemies/BpCRTDEnemy_Drone2.BpCRTDEnemy_Drone2_C");
	if (drone2.Succeeded()) EnemyClass[7] = drone2.Class;

	ConstructorHelpers::FClassFinder<ARTDEnemy> drone3(L"/Game/BP/Enemies/BpCRTDEnemy_Drone3.BpCRTDEnemy_Drone3_C");
	if (drone3.Succeeded()) EnemyClass[8] = drone3.Class;

	ConstructorHelpers::FClassFinder<ARTDEnemy> boss1(L"/Game/BP/Enemies/BpCRTDEnemy_Boss.BpCRTDEnemy_Boss_C");
	if (boss1.Succeeded()) EnemyClass[9] = boss1.Class;

	StartTransform = FTransform::Identity;
	StartTransform.SetRotation(FVector(0.0f, 0.0f, 0.0f).ToOrientationQuat());
	StartTransform.SetTranslation(FVector(1400.0f, -1800.0f, 110.0f));
	StartTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
}

void ARTDStageManager::BeginPlay()
{
	Super::BeginPlay();

	//DataTable = NewObject<URTDStageDataTable>();
	//IsStageStart = true;
}

void ARTDStageManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (IsStageStart)
		SetEnemy();*/

	/*if (Count == 0)
	{
		IsStageStart = true;
		StageCount++;
	}*/
}

void ARTDStageManager::SetEnemy()
{
	//StageData = DataTable->GetStageRow(FName(*FString::FromInt(StageCount)));
	//EnemyCount = StageData->Count;

	//IsStageStart = false;

	////타임 핸들러로 1초 후에 SpawnEnemy() 호출
	//GetWorld()->GetTimerManager().SetTimer(SpawnHandle, this, &ARTDStageManager::SpawnEnemy, 1.0f, false, 1.0f);
}

void ARTDStageManager::SpawnEnemy()
{
	//Enemies[Count] = GetWorld()->SpawnActor<ARTDEnemy>(EnemyClass[Count], StartTransform);

	//Count++;

	//if (Count >= EnemyCount) return;

	////타임 핸들러로 1초 후에 재호출
	//GetWorld()->GetTimerManager().SetTimer(SpawnHandle, this, &ARTDStageManager::SpawnEnemy, 1.0f, false, 1.0f);
}

void ARTDStageManager::SetEnemies(class ARTDEnemy* Enemy, int Stage, int Num)
{
	Enemies[Stage][Num] = Enemy;
}

