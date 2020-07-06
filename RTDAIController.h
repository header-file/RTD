#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RTDAIController.generated.h"

UCLASS()
class RTD_API ARTDAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ARTDAIController();
	void StartTree(FString Path);

	class UBlackboardComponent* GetBB() { return BB; }

protected:
	UPROPERTY(EditDefaultsOnly)
		class UBehaviorTreeComponent* BT;

	UPROPERTY(EditDefaultsOnly)
		class UBlackboardComponent* BB;
};
