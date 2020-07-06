#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RTDStageManager.generated.h"

#define MAXSTAGES 20
#define MAXENEMY 50

UCLASS()
class RTD_API ARTDStageManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ARTDStageManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SetEnemy();
	void SpawnEnemy();

public:
	UFUNCTION(BlueprintCallable)
		void SetEnemies(class ARTDEnemy* Enemy, int Stage, int Num);

	UFUNCTION(BlueprintCallable)
		void SetStageStart(bool b) { IsStageStart = b; }

	UFUNCTION(BlueprintCallable)
		void SetStageEnd(bool b) { IsStageEnd = b; }

	UFUNCTION(BlueprintCallable)
		void SetEnemyCount(int i, int Num) { EnemyCount[i] = Num; }

	UFUNCTION(BlueprintCallable)
		void SetCurrentEnemy(int Num) { CurrentEnemy = Num; }

	
	UFUNCTION(BlueprintPure)
		int GetMaxStages() { return MAXSTAGES; }

	UFUNCTION(BlueprintPure)
		TSubclassOf<class ARTDEnemy> GetClass(int i) { return EnemyClass[i]; }

	UFUNCTION(BlueprintPure)
		bool GetStageStart() { return IsStageStart; }

	UFUNCTION(BlueprintPure)
		bool GetStageEnd() { return IsStageEnd; }

	UFUNCTION(BlueprintPure)
		class ARTDEnemy* GetEnemy(int Stage, int Num) { return Enemies[Stage][Num]; }

	UFUNCTION(BlueprintPure)
		FTransform GetStartTransform() { return StartTransform; }

	UFUNCTION(BlueprintPure)
		int GetEnemyCount(int i) { return EnemyCount[i]; }

	UFUNCTION(BlueprintPure)
		int GetCurrentEnemy() { return CurrentEnemy; }

protected:
	const struct FStageData* StageData;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
		TSubclassOf<class ARTDEnemy> EnemyClass[MAXSTAGES];

private:
	class ARTDEnemy* Enemies[MAXSTAGES][MAXENEMY];
	class URTDStageDataTable* DataTable;

	FTransform StartTransform;
	int EnemyCount[MAXSTAGES];
	int CurrentEnemy;

	bool IsStageStart;
	bool IsStageEnd;

	FTimerHandle SpawnHandle;
};
