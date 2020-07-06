#include "RTDPawn.h"
#include "Global.h"
#include "RTDBlock.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "RTDTower.h"
#include "RTDBlockGrid.h"

ARTDPawn::ARTDPawn(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	for (int i = 0; i < MAXTYPE; i++)
		Level[i] = 0;

	IsGameOver = true;
}

void ARTDPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UCameraComponent* OurCamera = PC->GetViewTarget()->FindComponentByClass<UCameraComponent>())
			{
				FVector Start = OurCamera->GetComponentLocation();
				FVector End = Start + (OurCamera->GetComponentRotation().Vector() * 8000.0f);
				TraceForBlock(Start, End, true);
			}
		}
		else
		{
			FVector Start, Dir, End;
			PC->DeprojectMousePositionToWorld(Start, Dir);
			End = Start + (Dir * 8000.0f);
			TraceForBlock(Start, End, false);
		}
	}
}

void ARTDPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ResetVR", EInputEvent::IE_Pressed, this, &ARTDPawn::OnResetVR);
	PlayerInputComponent->BindAction("TriggerClick", EInputEvent::IE_Pressed, this, &ARTDPawn::TriggerClick);
	PlayerInputComponent->BindAction("Cancel", EInputEvent::IE_Pressed, this, &ARTDPawn::Cancel);
	PlayerInputComponent->BindAction("Synthesis", EInputEvent::IE_Pressed, this, &ARTDPawn::Synthesis);
}

void ARTDPawn::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
	Super::CalcCamera(DeltaTime, OutResult);

	OutResult.Rotation = FRotator(-90.0f, -90.0f, 0.0f);
}

void ARTDPawn::SetSelectedTower(ARTDTower * Tower)
{
	if(SelectedTower != NULL)
		SelectedTower->SetSelected(false);

	SelectedTower = Tower;
	SelectedTower->SetSelected(true);
}

void ARTDPawn::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ARTDPawn::TriggerClick()
{
	if (IsGameOver) return;

	if (CurrentBlockFocus)
	{
		CurrentBlockFocus->HandleClicked();
	}
}

void ARTDPawn::Cancel()
{
	if (SelectedTower == NULL) return;

	SelectedTower->SetSelected(false);
	SelectedTower = NULL;
}

void ARTDPawn::Synthesis()
{
	if (SelectedTower == NULL) return;

	int Type = SelectedTower->GetType();
	int Grade = SelectedTower->GetGrade();
	int Index = SelectedTower->GetBlock()->GetIndex();

	if (Grade > 3) return;

	for (int i = 0; i < 31; i++)
	{
		ARTDBlock* Block = Grid->GetBlock(i);
		class ARTDTower* tower = Block->GetTower();

		if (tower == NULL) continue;

		int type = tower->GetType();
		int grade = tower->GetGrade();
		int index = Block->GetIndex();

		if (Type == type && Grade == grade)
		{
			if (Index == index) continue;

			Block->Deconstruct();

			SelectedTower->Synthesize();

			break;
		}
	}
}

void ARTDPawn::Upgrade(int Type)
{
	if (Money < (Level[Type] + 1))
		return;

	Money -= (Level[Type] + 1);
	Level[Type]++;
}

void ARTDPawn::TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers)
{
	if (IsGameOver) return;

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
	if (bDrawDebugHelpers)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red);
		DrawDebugSolidBox(GetWorld(), HitResult.Location, FVector(20.0f), FColor::Red);
	}
	if (HitResult.Actor.IsValid())
	{
		ARTDBlock* HitBlock = Cast<ARTDBlock>(HitResult.Actor.Get());
		if (CurrentBlockFocus != HitBlock)
		{
			if (CurrentBlockFocus)
			{
				CurrentBlockFocus->Highlight(false);
			}
			if (HitBlock)
			{
				HitBlock->Highlight(true);
			}
			CurrentBlockFocus = HitBlock;
		}
	}
	else if (CurrentBlockFocus)
	{
		CurrentBlockFocus->Highlight(false);
		CurrentBlockFocus = nullptr;
	}
}