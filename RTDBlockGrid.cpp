#include "RTDBlockGrid.h"
#include "Global.h"
#include "RTDBlock.h"
#include "RTDPawn.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ARTDBlockGrid::ARTDBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;
}


void ARTDBlockGrid::SetBlocks(int i, ARTDBlock* Block)
{
	Blocks[i] = Block;
	Blocks[i]->SetIndex(i);
	Blocks[i]->SetGrid(this);
}

void ARTDBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<class ARTDPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	Player->SetGrid(this);
}

#undef LOCTEXT_NAMESPACE
