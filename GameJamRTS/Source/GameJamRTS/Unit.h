// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Animation/SkeletalMeshActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Unit.generated.h"


class UHealthComponent;

UCLASS()
class GAMEJAMRTS_API AUnit : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnit();

	void Initialize(int team); // Has to be called when being spawned!

	void SetDestination(const FVector& destination, bool byPlayerAction = false);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool IsWalking   = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		bool IsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colliders")
		class USphereComponent* m_pFindEnemyCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colliders")
		class USphereComponent* m_pAttackCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int m_Team = 0;

	UFUNCTION()
		void FindEnemyOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void FindEnemyOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//UFUNCTION()
	//	void AttackColliderOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//UFUNCTION()
	//	void AttackColliderOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UFUNCTION(BlueprintCallable)
		void AnimationHitPlayed();

	UPROPERTY()
		TArray<AUnit*> m_EnemiesInRange;

	//UPROPERTY()
	//	TArray<AUnit*> m_EnemiesInStrikingRange;

	UPROPERTY()
		AUnit* m_pCurrentTarget = nullptr;

	bool Damage(float amount); // returns if dead
	void Heal(float amount);
	bool IsDead() const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveTo();
	AUnit* FindNearestEnemy();
	bool CheckIfStillAttacking() const;

	// Can be changed
	float m_WalkSpeed = 0.3f;
	float m_MinimalOffsetToFindANewEnemy = 10.0f;
	float m_MinimalDifferenceToAttackANewEnemy = 1.0f;
	float m_MinimalOffsetToStopAttacking = 150.0f;
	float m_Damage = 50.0f;
	
	// Dont change
	float m_OffsetWithCurrentTarget = FLT_MAX;
	bool m_OrderedToWalkByPlayer = false;
	FVector m_Direction;
	FVector m_Destination;
	float m_AttackCooldown = 0;
	const float m_StrikingRange = 120.0f;
	//const float m_SphereRadiusKeepAttackingOffset = 10.0f;

	//Components
	UHealthComponent* m_pHealthComponent = nullptr;


};
