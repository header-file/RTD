// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RTDPawn.generated.h"

#define MAXTYPE 8

UCLASS(config=Game)
class ARTDPawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

public:
	void SetSelectedTower(class ARTDTower* Tower);

	void SetGrid(class ARTDBlockGrid* BlockGrid) { Grid = BlockGrid; }

public:
	UFUNCTION(BlueprintPure)
		int GetMoney() { return Money; }

	UFUNCTION(BlueprintPure)
		int GetLife() { return Life; }

	UFUNCTION(BlueprintPure)
		int GetLevel(int Type) { return Level[Type]; }

	UFUNCTION(BlueprintPure)
		class ARTDTower* GetSelectedTower() { return SelectedTower; }

	UFUNCTION(BlueprintPure)
		bool GetGameOver() { return IsGameOver; }


	UFUNCTION(BlueprintCallable)
		void SetMoney(int Num) { Money = Num; }

	UFUNCTION(BlueprintCallable)
		void SetLife(int Left) { Life = Left; }

	UFUNCTION(BlueprintCallable)
		void SetLevel(int Type, int Num) { Level[Type] = Num; }

	UFUNCTION(BlueprintCallable)
		void SetGameOver(bool b) { IsGameOver = b; }


	UFUNCTION(BlueprintCallable)
		void Synthesis();

	UFUNCTION(BlueprintCallable)
		void Upgrade(int Type);

protected:
	void OnResetVR();
	void TriggerClick();
	void Cancel();
	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		class ARTDBlock* CurrentBlockFocus;

private:
	class ARTDTower* SelectedTower;
	class ARTDBlockGrid* Grid;

	int Level[MAXTYPE];

	int Money = 30;
	int Life = 10;

	bool IsGameOver;
};
