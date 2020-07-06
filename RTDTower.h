// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RTDTower.generated.h"

#define MAXENEMY 10

enum class GRADE
{
	NORMAL = 0,
	MAGIC = 1,
	RARE = 2,
	EPIC = 3,
	UNIQUE = 4
};

enum class TYPE
{
	FIRE = 0,
	ICE = 1,
	POISON = 2,
	LIGHTNING = 3,
	GROUND = 4,
	WIND = 5,
	LIGHT = 6,
	DARK = 7
};

UCLASS()
class RTD_API ARTDTower : public AActor
{
	GENERATED_BODY()
	
public:	
	ARTDTower();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Synthesize();

	void SetBlock(class ARTDBlock* RtdBlock) { Block = RtdBlock; }
	void SetSelected(bool b) { IsSelected = b; }

	void AttackEnemy();

public:
	UFUNCTION(BlueprintPure)
		class ARTDBlock* GetBlock() { return Block; }

	UFUNCTION(BlueprintPure)
		int GetType() { return (int)Type; }

	UFUNCTION(BlueprintPure)
		int GetGrade() { return (int)Grade; }

	UFUNCTION(BlueprintPure)
		bool GetSelected() { return IsSelected; }

	UFUNCTION(BlueprintPure)
		bool GetSynthesized() { return IsSynthesized; }

	UFUNCTION(BlueprintPure)
		float GetAttackRange() { return AttackRange; }

	UFUNCTION(BlueprintPure)
		float GetAttack() { return Attack; }

	UFUNCTION(BlueprintPure)
		float GetAttackSpeed() { return AttackSpeed; }


	UFUNCTION(BlueprintCallable)
		void SetSynthesized(bool b) { IsSynthesized = b; }

	UFUNCTION(BlueprintCallable)
		void SetData(float Atk, float AtkSpeed, float AtkRange);

	UFUNCTION(BlueprintCallable)
		void LoadData(int TowerType, int TowerGrade, float Atk, float AtkSpeed, float AtkRange);

	UFUNCTION(BlueprintCallable)
		void AddEnemy(class ARTDEnemy* Enemy);

	UFUNCTION(BlueprintCallable)
		void RemoveEnemy(class ARTDEnemy* Enemy);

protected:
	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* PS_Fire;

	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* PS_Ice;

	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* PS_Poison;

	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* PS_Lightning;

	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* PS_Ground;

	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* PS_Wind;

	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* PS_Light;

	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* PS_Dark;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USphereComponent* AttackSphere;

protected:
	const struct FTowerData* TowerData;

private:
	TYPE Type;
	GRADE Grade;

	FTimerHandle AttackHandle;

	float Attack;
	float AttackRange;
	float AttackSpeed;

	class ARTDBlock* Block;

	class URTDTowerDataTable* DataTable;
	

	bool IsSelected;
	bool IsSynthesized;

	class ARTDEnemy* Enemies[MAXENEMY];
};
