// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Animation/SkeletalMeshActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Unit.generated.h"

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

	UFUNCTION()
		void CapsuleComponentOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY()
		TArray<AUnit*> m_EnemiesInRange;

	UPROPERTY()
		AUnit* m_pCurrentTarget = nullptr;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveTo();
	AUnit* FindNearestEnemy();
	bool CheckIfStillAttacking() const;

	FVector m_Direction;
	FVector m_Destination;

	float m_OffsetWithCurrentTarget = FLT_MAX;
	bool m_OrderedToWalkByPlayer = false;
	float m_WalkSpeed = 0.3f;
	float m_MinimalOffsetToFindANewEnemy = 200.0f;
	float m_MinimalDifferenceToAttackANewEnemy = 50.0f;
	float m_MinimalOffsetToStopAttacking = 50.0f;


};
