// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RTDBlockGrid.generated.h"

#define MAXBLOCKS 31

/** Class used to spawn blocks and manage score */
UCLASS(minimalapi)
class ARTDBlockGrid : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* DummyRoot;

public:
	ARTDBlockGrid();

	class ARTDPawn* GetPlayer() { return Player; }

private:
	UPROPERTY(VisibleAnywhere)
		class ARTDBlock* Blocks[MAXBLOCKS];

public:
	UFUNCTION(BlueprintCallable)
		void SetBlocks(int i, ARTDBlock* Block);

protected:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

public:
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }

	ARTDBlock* GetBlock(int i) { return Blocks[i]; }

private:
	class ARTDPawn* Player;
};



