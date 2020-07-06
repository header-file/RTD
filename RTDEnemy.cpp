#include "RTDEnemy.h"
#include "RTDAIController.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RTDDataTable.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "RTDPawn.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "WidgetComponent.h"

ARTDEnemy::ARTDEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	HPBar = CreateDefaultSubobject<UWidgetComponent>("HPBar");
	HPBar->SetupAttachment(RootComponent);

	FloatingText = CreateDefaultSubobject<UWidgetComponent>("FloatingText");
	FloatingText->SetupAttachment(RootComponent);

	PS_Burn = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Burn"));
	PS_Burn->SetupAttachment(RootComponent);

	PS_Freeze = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Freeze"));
	PS_Freeze->SetupAttachment(RootComponent);

	PS_Poison = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Poison"));
	PS_Poison->SetupAttachment(RootComponent);

	PS_Shock = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Shock"));
	PS_Shock->SetupAttachment(RootComponent);

	MaterialCount = 0.0f;
	Destinations[0] = FVector(900.0f, -1800.0f, 0.0f);
	IsStart = false;
	DestCount = 0;
	IsBoss = false;

	DefenseRate = 0.9f;
}

void ARTDEnemy::BeginPlay()
{
	Super::BeginPlay();

	//DataTable = NewObject<URTDDataTable>();
	//EnemyData = DataTable->GetEnemyRow(RowName);

	Controller = Cast<ARTDAIController>(GetController());
	Controller->StartTree(FString("BTEnemy"));

	PS_Burn->SetVisibility(false);
	PS_Freeze->SetVisibility(false);
	PS_Poison->SetVisibility(false);
	PS_Shock->SetVisibility(false);

	//HP = EnemyData->HP;
	//GetCharacterMovement()->MaxWalkSpeed = EnemyData->Speed;
}

void ARTDEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsBoss)
		DefenseRate = 0.95f;
}

void ARTDEnemy::Damage(int Type, float Damage, int Level, int Grade)
{
	//상태 이상 처리
	switch (Type)
	{
		case 0:
		{
			if ((BadStatus & (int)STATUS::BURN) == (int)STATUS::BURN) break;
			int random = rand() % 4;
			if (random < 3) break;

			BadStatus |= (int)STATUS::BURN;
			PS_Burn->SetVisibility(true);

			GetWorld()->GetTimerManager().SetTimer(BurnHandle, this, &ARTDEnemy::RecoverBurn, 1.0f, true, 5.0f);

			break;
		}
		case 1:
		{
			if ((BadStatus & (int)STATUS::FREEZE) == (int)STATUS::FREEZE) break;

			int random = rand() % 4;
			if (random < 3) break;

			BadStatus |= (int)STATUS::FREEZE;
			PS_Freeze->SetVisibility(true);

			GetCharacterMovement()->MaxWalkSpeed /= 2.0f;
			GetWorld()->GetTimerManager().SetTimer(FreezeHandle, this, &ARTDEnemy::RecoverFreeze, 1.0f, true, 3.0f);

			break;
		}
		case 2:
		{
			if ((BadStatus & (int)STATUS::POISON) == (int)STATUS::POISON) break;

			int random = rand() % 3;
			if (random < 2) break;

			BadStatus |= (int)STATUS::POISON;
			PS_Poison->SetVisibility(true);
			IsPoisoned = true;

			GetWorld()->GetTimerManager().SetTimer(PoisonHandle, this, &ARTDEnemy::Poison, 0.1f, true, 0.1f);

			break;
		}
		case 3:
		{
			if ((BadStatus & (int)STATUS::STUN) == (int)STATUS::STUN) break;

			int random = rand() % 5;
			if (random < 4) break;

			BadStatus |= (int)STATUS::STUN;
			PS_Shock->SetVisibility(true);

			GetCharacterMovement()->MaxWalkSpeed = 0.0f;
			GetWorld()->GetTimerManager().SetTimer(StunHandle, this, &ARTDEnemy::RecoverStun, 1.0f, true, 2.0f);

			break;
		}
		case 4:
		{
			if (IsLaunching) break;

			int random = rand() % 5;
			if (random < 4) break;

			FVector Velocity = FVector(0.0f, 0.0f, 900.0f);
			//FVector Velocity = FVector(GetActorForwardVector().X, GetActorForwardVector().Y, -0.07f) * -10000.0f;
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
			GetCharacterMovement()->MaxWalkSpeed = 0.0f;
			LaunchCharacter(Velocity, true, true);

			IsLaunching = true;
			GetWorld()->GetTimerManager().SetTimer(LaunchHandle, this, &ARTDEnemy::FinishLaunch, 1.0f, false, 2.0f);
			break;
		}
		default:
			break;
	}

	float RealDamage = (Damage * (Grade + 1)) * (1.0f + (Level / 10.0f)) * (1 - DefenseRate);

	if ((BadStatus & (int)STATUS::BURN) == 1)
		RealDamage *= 1.1f;

	HP -= RealDamage;

	if (HP <= 0.0f)
		IsDead = true;
}

void ARTDEnemy::Poison()
{
	if (HP < MaxHP / 100.0f) return;

	HP -= 0.1f;

	if (HP <= 0.0f)
		IsDead = true;
}

void ARTDEnemy::RecoverBurn()
{
	if ((BadStatus & (int)STATUS::BURN) != (int)STATUS::BURN) return;

	BadStatus ^= (int)STATUS::BURN;
	PS_Burn->SetVisibility(false);
}

void ARTDEnemy::RecoverFreeze()
{
	if ((BadStatus & (int)STATUS::FREEZE) != (int)STATUS::FREEZE) return;

	BadStatus ^= (int)STATUS::FREEZE;
	PS_Freeze->SetVisibility(false);

	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
}

void ARTDEnemy::RecoverStun()
{
	if ((BadStatus & (int)STATUS::STUN) != (int)STATUS::STUN) return;

	BadStatus ^= (int)STATUS::STUN;
	PS_Shock->SetVisibility(false);

	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
}

void ARTDEnemy::FinishLaunch()
{
	IsLaunching = false;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
}

void ARTDEnemy::ToggleHP()
{
	if (IsShowHP)
	{
		IsShowHP = false;

		HPBar->SetVisibility(false);
	}
	else
	{
		IsShowHP = true;

		HPBar->SetVisibility(true);
	}
}

void ARTDEnemy::SetState(float Hp, float Speed)
{
	HP = MaxHP = Hp;
	GetCharacterMovement()->MaxWalkSpeed = Speed;
	MaxSpeed = Speed;
}

