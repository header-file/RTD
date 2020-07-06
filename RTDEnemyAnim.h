#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RTDEnemyAnim.generated.h"


UCLASS()
class RTD_API URTDEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
		float Speed;

	UPROPERTY(BlueprintReadOnly)
		bool IsDead;

	UPROPERTY(BlueprintReadOnly)
		bool IsStuned;

	UPROPERTY(BlueprintReadOnly)
		bool IsLaunching;

private:
	class ARTDEnemy* Enemy;
};
