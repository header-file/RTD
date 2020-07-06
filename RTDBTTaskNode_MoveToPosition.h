// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RTDBTTaskNode_MoveToPosition.generated.h"

/**
 * 
 */
UCLASS()
class RTD_API URTDBTTaskNode_MoveToPosition : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) {};
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) {};

private:
	class ARTDAIController* Controller;
	class ARTDEnemy* Enemy;
	class UBlackboardComponent* BB;
};
