#include "RTDEnemyAnim.h"
#include "RTDEnemy.h"

void URTDEnemyAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Enemy = Cast<ARTDEnemy>(TryGetPawnOwner());
}

void URTDEnemyAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Enemy == NULL) return;

	Speed = Enemy->GetVelocity().Size();
	IsDead = Enemy->GetDead();

	IsStuned = Enemy->GetStuned();
	IsLaunching = Enemy->GetIsLaunching();
}