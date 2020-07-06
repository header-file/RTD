#include "RTDBlock.h"
#include "Global.h"
#include "RTDBlockGrid.h"
#include "RTDPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "RTDTower.h"
#include "Kismet/GameplayStatics.h"

ARTDBlock::ARTDBlock()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> OverMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> ClickedMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, OverMaterial(TEXT("/Game/Puzzle/Meshes/OverMaterial.OverMaterial"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
			, ClickedMaterial(TEXT("/Game/Materials/CubeMaterial.CubeMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(0.5f,0.5f,0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f,0.f,25.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.BaseMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &ARTDBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &ARTDBlock::OnFingerPressedBlock);

	// Save a pointer to the orange material
	OverMaterial = ConstructorStatics.OverMaterial.Get();
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	ClickedMaterial = ConstructorStatics.ClickedMaterial.Get();

	ConstructorHelpers::FClassFinder<ARTDTower> tower(L"Blueprint'/Game/BP/BpCRTDTower.BpCRTDTower_C'");
	if (tower.Succeeded()) TowerClass = tower.Class;

	IsConstructed = false;
}

void ARTDBlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}


void ARTDBlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	HandleClicked();
}

void ARTDBlock::HandleClicked()
{
	if (OwningGrid->GetPlayer()->GetGameOver()) return;

	if (!IsConstructed)
	{
		//µ· Ã¼Å© & µ· °è»ê
		int CurMoney = OwningGrid->GetPlayer()->GetMoney();
		if (CurMoney < TOWERPRICE) return;

		OwningGrid->GetPlayer()->SetMoney(CurMoney - TOWERPRICE);
		ConstructTower();
	}
	else
		OwningGrid->GetPlayer()->SetSelectedTower(Tower);
}

void ARTDBlock::Highlight(bool bOn)
{
	if (IsConstructed) return;

	if (bOn)
	{
		BlockMesh->SetMaterial(0, OverMaterial);
	}
	else
	{
		BlockMesh->SetMaterial(0, BaseMaterial);
	}
}

void ARTDBlock::Deconstruct()
{
	Tower->Destroy();
	Tower = NULL;

	IsConstructed = false;

	BlockMesh->SetMaterial(0, BaseMaterial);
}

void ARTDBlock::ConstructTower()
{
	IsConstructed = true;

	// Change material
	BlockMesh->SetMaterial(0, ClickedMaterial);

	FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 90.0f);
	ARTDTower* NewTower = GetWorld()->SpawnActor<ARTDTower>(TowerClass, SpawnLocation, FRotator::ZeroRotator);
	Tower = NewTower;
	Tower->SetBlock(this);
}
