#include "RTDEnemy_Boss.h"
#include "RTDEnemy.h"

ARTDEnemy_Boss::ARTDEnemy_Boss()
{
	IsBoss = true;
	DefenseRate = 0.99f;
}

void ARTDEnemy_Boss::Damage(int Type, float Damage, int Level, int Grade)
{
	Super::Damage(Type, Damage, Level, Grade);

	float RealDamage = (Damage * (Grade + 1)) * (1.0f + (Level / 10.0f)) * (1 - DefenseRate);

	if ((BadStatus & (int)STATUS::BURN) == 1)
		RealDamage *= 1.1f;

	HP -= RealDamage;

	if (HP <= 0.0f)
		IsDead = true;
}
