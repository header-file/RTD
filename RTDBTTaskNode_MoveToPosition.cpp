#include "RTDBTTaskNode_MoveToPosition.h"
#include "RTDEnemy.h"
#include "RTDAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type URTDBTTaskNode_MoveToPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Controller = Cast<ARTDAIController>(OwnerComp.GetAIOwner());
	BB = Controller->GetBB();
	Enemy = Cast<ARTDEnemy>(Controller->GetPawn());
	BB->SetValueAsObject("SelfActor", Enemy);

	int Count = Enemy->GetDestCount();
	FVector Next = Enemy->GetDestination(Count);
	FVector Now = Enemy->GetActorLocation();

	BB->SetValueAsVector("Next", Next);
	BB->SetValueAsVector("Now", Now);

	FPathFollowingRequestResult Result;
	Result.Code = Controller->MoveToLocation(Next, 20.0f, false);
	
	BB->SetValueAsString("Result", FString::FromInt(Result.Code));
	
	float Dist = FVector::DistXY(Now, Next);
	if (Dist < 20.0f)
		Enemy->SetDestCount(Count + 1);

	BB->SetValueAsFloat("Dist", Dist);

	return EBTNodeResult::Succeeded;
}