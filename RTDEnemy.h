#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RTDEnemy.generated.h"

enum class STATUS
{
	BURN = 0b0001,
	FREEZE = 0b0010,
	POISON = 0b0100,
	STUN = 0b1000
};



UCLASS()
class RTD_API ARTDEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	ARTDEnemy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Damage(int Type, float Damage, int Level, int Grade);
	void Poison();
	void RecoverBurn();
	void RecoverFreeze();
	void RecoverStun();
	void FinishLaunch();

	void SetDestCount(int i) { DestCount = i; }

	FVector GetDestination(int i) { return Destinations[i]; }
	int GetDestCount() { return DestCount; }
	bool GetIsLaunching() { return IsLaunching; }

	UFUNCTION(BlueprintCallable)
		void ToggleHP();

public:
	UFUNCTION(BlueprintCallable)
		void SetState(float Hp, float Speed);

	UFUNCTION(BlueprintCallable)
		void SetDestination(FVector Location, int i) { Destinations[i] = Location; }

	UFUNCTION(BlueprintCallable)
		void SetIsStart(bool b) { IsStart = b; }

	UFUNCTION(BlueprintCallable)
		void SetIsDead(bool b) { IsDead = b; }

	UFUNCTION(BlueprintCallable)
		void SetIsFin(bool b) { IsFin = b; }

	UFUNCTION(BlueprintCallable)
		void SetMIDBody(class UMaterialInstanceDynamic* MID) { MIDBody = MID; }

	UFUNCTION(BlueprintCallable)
		void SetMIDHead(class UMaterialInstanceDynamic* MID) { MIDHead = MID; }

	UFUNCTION(BlueprintCallable)
		void SetCount(float f) { MaterialCount = f; }

	UFUNCTION(BlueprintCallable)
		void SetIsBoss(bool b) { IsBoss = b; }


	UFUNCTION(BlueprintPure)
		float GetMaxHP() { return MaxHP; }

	UFUNCTION(BlueprintPure)
		float GetHP() { return HP; }

	UFUNCTION(BlueprintPure)
		bool GetIsStart() { return IsStart; }

	UFUNCTION(BlueprintPure)
		class UMaterialInstance* GetMIBody() { return MIBody; }

	UFUNCTION(BlueprintPure)
		class UMaterialInstance* GetMIHead() { return MIHead; }

	UFUNCTION(BlueprintPure)
		float GetCount() { return MaterialCount; }

	UFUNCTION(BlueprintPure)
		bool GetDead() { return IsDead; }

	UFUNCTION(BlueprintPure)
		bool GetIsFin() { return IsFin; }

	UFUNCTION(BlueprintPure)
		bool GetIsPoisoned() { return IsPoisoned; }

	UFUNCTION(BlueprintPure)
		bool GetStuned() { if ((BadStatus & (int)STATUS::STUN) == (int)STATUS::STUN) return true;
							else return false; }

protected:
	UPROPERTY(EditDefaultsOnly)
		class UMaterialInstance* MIBody;

	UPROPERTY(EditDefaultsOnly)
		class UMaterialInstance* MIHead;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UParticleSystemComponent* PS_Burn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UParticleSystemComponent* PS_Freeze;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UParticleSystemComponent* PS_Poison;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UParticleSystemComponent* PS_Shock;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* HPBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* FloatingText;

	class UMaterialInstanceDynamic* MIDBody;
	class UMaterialInstanceDynamic* MIDHead;

	class ARTDAIController* Controller;
	const struct FEnemyData* EnemyData;

	FName RowName;

	int BadStatus;

	bool IsBoss;
	bool IsDead;

	float MaxHP;
	float HP;
	float MaxSpeed;
	float DefenseRate;

private:
	class URTDDataTable* DataTable;
	float MaterialCount;

	FTimerHandle BurnHandle;
	FTimerHandle FreezeHandle;
	FTimerHandle StunHandle;
	FTimerHandle PoisonHandle;
	FTimerHandle LaunchHandle;

	FVector Destinations[13];
	int DestCount;

	bool IsStart;
	bool IsFin;
	bool IsShowHP;
	bool IsPoisoned;
	bool IsLaunching;
};
