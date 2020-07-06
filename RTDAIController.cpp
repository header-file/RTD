#include "RTDAIController.h"
#include "RTDEnemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ARTDAIController::ARTDAIController()
{
	BT = CreateDefaultSubobject<UBehaviorTreeComponent>("BT");
	BB = CreateDefaultSubobject<UBlackboardComponent>("BB");
}

void ARTDAIController::StartTree(FString Path)
{
	Path = "/Game/BP/Enemies/" + Path;

	UBehaviorTree* tree = Cast<UBehaviorTree>(StaticLoadObject(UBehaviorTree::StaticClass(), NULL, *Path));
	
	if (tree != NULL)
	{
		BB->InitializeBlackboard(*tree->BlackboardAsset);
		BT->StartTree(*tree);
	}
}
