#include "RTDTower.h"
#include "Global.h"
#include "ConstructorHelpers.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "RTDEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "RTDTowerDataTable.h"
#include "RTDPawn.h"
#include "CLog.h"

ARTDTower::ARTDTower()
{
 	PrimaryActorTick.bCanEverTick = true;

	Type = (TYPE)(rand() % 8);

	int rare = (rand() % 20);

	if (rare < 1)
		Grade = GRADE::MAGIC;
	else
		Grade = GRADE::NORMAL;

	ConstructorHelpers::FObjectFinder<UParticleSystem> fire(TEXT("ParticleSystem'/Game/Materials/P_Fire.P_Fire'"));
	if (fire.Succeeded()) PS_Fire = fire.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> ice(TEXT("ParticleSystem'/Game/Materials/P_Ice.P_Ice'"));
	if (ice.Succeeded()) PS_Ice = ice.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> poison(TEXT("ParticleSystem'/Game/Materials/P_Poison.P_Poison'"));
	if (poison.Succeeded()) PS_Poison = poison.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> lightning(TEXT("ParticleSystem'/Game/Materials/P_Lightning.P_Lightning'"));
	if (lightning.Succeeded()) PS_Lightning = lightning.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> ground(TEXT("ParticleSystem'/Game/Materials/P_Ground.P_Ground'"));
	if (ground.Succeeded()) PS_Ground = ground.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> wind(TEXT("ParticleSystem'/Game/Materials/P_Wind.P_Wind'"));
	if (wind.Succeeded()) PS_Wind = wind.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> light(TEXT("ParticleSystem'/Game/Materials/P_Light.P_Light'"));
	if (light.Succeeded()) PS_Light = light.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> dark(TEXT("ParticleSystem'/Game/Materials/P_Dark.P_Dark'"));
	if (dark.Succeeded()) PS_Dark = dark.Object;

	AttackSphere = CreateDefaultSubobject<USphereComponent>("AttackRange");
	AttackSphere->SetupAttachment(RootComponent);

	Attack = 1.0f;
	AttackSpeed = 1.0f;
	AttackRange = 1.0f;

	IsSelected = false;
	IsSynthesized = false;

	for (int i = 0; i < MAXENEMY; i++)
		Enemies[i] = nullptr;
}

void ARTDTower::BeginPlay()
{
	Super::BeginPlay();

	/*FName rowname = FName(*FString::FromInt((int)Type + 1));
	DataTable = NewObject<URTDTowerDataTable>();
	TowerData = DataTable->GetTowerRow(rowname);

	Attack = TowerData->Attack;
	AttackSpeed = TowerData->Speed;
	AttackRange = TowerData->Range;*/
	
	GetWorld()->GetTimerManager().SetTimer(AttackHandle, this, &ARTDTower::AttackEnemy, 2.0f / AttackSpeed, true, 1.0f / AttackSpeed);
}

void ARTDTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARTDTower::SetData(float Atk, float AtkSpeed, float AtkRange)
{
	Attack = Atk;
	AttackSpeed = AtkSpeed;
	AttackRange = AtkRange;
}

void ARTDTower::LoadData(int TowerType, int TowerGrade, float Atk, float AtkSpeed, float AtkRange)
{
	Type = (TYPE)TowerType;
	Grade = (GRADE)TowerGrade;
	Attack = Atk;
	AttackSpeed = AtkSpeed;
	AttackRange = AtkRange;
}

void ARTDTower::Synthesize()
{
	Grade = (GRADE)((int)Grade + 1);
	Type = (TYPE)(rand() % 8);

	if ((int)Grade > 3)
		AttackRange += 1.0f;

	IsSynthesized = true;
}

void ARTDTower::AttackEnemy()
{
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (Enemies[i] == nullptr) continue;
		if (Enemies[i]->GetHP() <= 0.0f) continue;
		
		switch(Type)
		{
			case TYPE::FIRE:
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PS_Fire, Enemies[i]->GetActorTransform());
				break;
			}
			case TYPE::ICE:
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PS_Ice, Enemies[i]->GetActorTransform());
				break;
			}
			case TYPE::POISON:
			{
				FTransform trans;
				trans  = Enemies[i]->GetActorTransform();
				FVector Loc = FVector(trans.GetTranslation().X, trans.GetTranslation().Y, trans.GetTranslation().Z - 50.0f);
				trans.SetTranslation(Loc);

				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PS_Poison, trans);
				break;
			}
			case TYPE::LIGHTNING:
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PS_Lightning, Enemies[i]->GetActorTransform());
				break;
			}
			case TYPE::GROUND:
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PS_Ground, Enemies[i]->GetActorTransform());
				break;
			}
			case TYPE::WIND:
			{
				FTransform trans;
				trans = Enemies[i]->GetActorTransform();
				FVector Loc = FVector(trans.GetTranslation().X, trans.GetTranslation().Y, trans.GetTranslation().Z - 50.0f);
				trans.SetTranslation(Loc);

				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PS_Wind, trans);
				break;
			}
			case TYPE::LIGHT:
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PS_Light, Enemies[i]->GetActorTransform());
				break;
			}
			case TYPE::DARK:
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PS_Dark, Enemies[i]->GetActorTransform());
				break;
			}
		}

		int Level = Cast<ARTDPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->GetLevel((int)Type);

		Enemies[i]->Damage((int)Type, Attack, Level, (int)Grade);

		if (Type != TYPE::WIND)
			break;
	}
}

void ARTDTower::AddEnemy(ARTDEnemy * Enemy)
{
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (Enemies[i] != nullptr) continue;

		Enemies[i] = Enemy;
		break;
	}
}

void ARTDTower::RemoveEnemy(ARTDEnemy * Enemy)
{
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (Enemies[i] != Enemy) continue;

		Enemies[i] = nullptr;
	}
}

