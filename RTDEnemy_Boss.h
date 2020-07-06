#pragma once

#include "CoreMinimal.h"
#include "RTDEnemy.h"
#include "RTDEnemy_Boss.generated.h"

UCLASS()
class RTD_API ARTDEnemy_Boss : public ARTDEnemy
{
	GENERATED_BODY()
	
public:
	ARTDEnemy_Boss();

	void Damage(int Type, float Damage, int Level, int Grade) override;
};
