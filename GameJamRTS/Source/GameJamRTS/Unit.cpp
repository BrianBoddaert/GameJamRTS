// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/CharacterMovementComponent.h"
#include "Unit.h"
#include "Components/CapsuleComponent.h"
#include "MaterialManager.h"
#include "HealthComponent.h"

// Sets default values
AUnit::AUnit()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//
	m_pFindEnemyCollider = CreateDefaultSubobject<USphereComponent>(TEXT("FindEnemyRange"));
	m_pFindEnemyCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	m_pFindEnemyCollider->OnComponentBeginOverlap.AddDynamic(this, &AUnit::FindEnemyOverlapBegin);
	m_pFindEnemyCollider->OnComponentEndOverlap.AddDynamic(this, &AUnit::FindEnemyOverlapEnd);

	//m_pAttackCollider = CreateDefaultSubobject<USphereComponent>(TEXT("AttackCollider"));
	//m_pAttackCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//m_pAttackCollider->OnComponentBeginOverlap.AddDynamic(this, &AUnit::AttackColliderOverlapBegin);
	//m_pAttackCollider->OnComponentEndOverlap.AddDynamic(this, &AUnit::AttackColliderOverlapEnd);
	//
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	//GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AUnit::CapsuleComponentOnHit);

	m_pHealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	m_pHealthComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();

	m_pFindEnemyCollider->SetRelativeLocation(FVector(0, 0, 0));
	//m_pAttackCollider->SetRelativeLocation(FVector(0, 0, 0));

	// TEMP v
	Initialize(m_Team);


}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsAttacking)
		if (!CheckIfStillAttacking())
			IsAttacking = false;
		else
			m_AttackCooldown -= DeltaTime;


	if (FindNearestEnemy())
		SetDestination(m_pCurrentTarget->GetActorLocation());
	else
		IsWalking = false;

	if (IsWalking)
		MoveTo();
}

//void AUnit::AttackColliderOverlapBegin(class UPrimitiveComponent* overlappedComp, class AActor* otherActor, class UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
//{
//	if (IsAttacking || !otherActor || otherActor == this || !otherComp || !otherComp->ComponentHasTag("UnitHitbox"))
//		return;
//
//	AUnit* otherUnit = Cast<AUnit>(otherActor);
//	if (!otherUnit || otherUnit != m_pCurrentTarget)
//		return;
//
//	IsAttacking = true;
//
//	if (m_EnemiesInStrikingRange.Find(otherUnit) == INDEX_NONE)
//		m_EnemiesInStrikingRange.Add(otherUnit);
//
//}
//
//void AUnit::AttackColliderOverlapEnd(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex)
//{
//	if (!IsAttacking || !otherActor || otherActor == this || !otherComp || !otherComp->ComponentHasTag("UnitHitbox"))
//		return;
//
//	AUnit* otherUnit = Cast<AUnit>(otherActor);
//	if (!otherUnit || otherUnit != m_pCurrentTarget)
//		return;
//
//	IsAttacking = false;
//
//	m_EnemiesInStrikingRange.RemoveSingle(otherUnit);
//
//}

void AUnit::FindEnemyOverlapBegin(class UPrimitiveComponent* overlappedComp, class AActor* otherActor, class UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (!otherActor || otherActor == this || !otherComp || !otherComp->ComponentHasTag("UnitHitbox"))
		return;

	AUnit* otherUnit = Cast<AUnit>(otherActor);
	if (!otherUnit || otherUnit->m_Team == m_Team)
		return;
	//
	 // FOUND ENEMY
	if (m_EnemiesInRange.Find(otherUnit) == INDEX_NONE)
		m_EnemiesInRange.Add(otherUnit);

}

void AUnit::FindEnemyOverlapEnd(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex)
{
	if (!otherActor || otherActor == this || !otherComp || !otherComp->ComponentHasTag("UnitHitbox"))
		return;

	AUnit* otherUnit = Cast<AUnit>(otherActor);
	if (!otherUnit || otherUnit->m_Team == m_Team)
		return;

	m_EnemiesInRange.RemoveSingle(otherUnit);

}

void AUnit::SetDestination(const FVector& destination, bool byPlayerAction)
{
	if (byPlayerAction)
	{
		IsAttacking = false;
		m_OrderedToWalkByPlayer = true;
	}
	else if (m_OrderedToWalkByPlayer)
		return;

	m_Destination = destination;
	m_Direction = (destination - GetActorLocation()).GetSafeNormal();
	IsWalking = true;
}

void AUnit::MoveTo()
{
	AddMovementInput(m_Direction, m_WalkSpeed);

	// v Check if reached destination
	float offset = 1.0f;
	if (FVector::Dist(GetActorLocation(), m_Destination) < offset)
	{
		IsWalking = false;
		m_OrderedToWalkByPlayer = false;
	}
		

}

void AUnit::Initialize(int team)
{
	m_Team = team;
	auto materialManager = AMaterialManager::GetInstance(GetWorld());

	switch (team)
	{
	case 0: GetMesh()->SetMaterial(0, materialManager->GetMaterialByName("MI_Units_Blue"));  break;
	case 1: GetMesh()->SetMaterial(0, materialManager->GetMaterialByName("MI_Units_Red"));  break;
	}


}

AUnit* AUnit::FindNearestEnemy() // Also sets m_pCurrentTarget and m_OffsetWithCurrentTarget
{
	if (m_EnemiesInRange.Num() == 0)
		return nullptr;
	//
	FVector actorLocation = GetActorLocation();

	if (m_pCurrentTarget && !m_pCurrentTarget->IsDead())
		m_OffsetWithCurrentTarget = FVector::Dist(actorLocation, m_pCurrentTarget->GetActorLocation());
	else
	{
		m_pCurrentTarget = nullptr;
		m_OffsetWithCurrentTarget = FLT_MAX; // Asures we look for a new target if there is no target yet
	}
		

	if (m_OffsetWithCurrentTarget < m_MinimalOffsetToFindANewEnemy)
		return m_pCurrentTarget; // Enemy is close enough that we do not need to seek for a new one


	m_EnemiesInRange.RemoveAll([](const AUnit* unit) {
		return (unit == nullptr || unit->IsDead());
	});

	for (int32 i = 0; i < m_EnemiesInRange.Num(); i++) // Finding closest and removing dead enemies from the list
	{
			
		const float distanceToEnemy = FVector::Dist(actorLocation, m_EnemiesInRange[i]->GetActorLocation());
		if ((m_OffsetWithCurrentTarget - distanceToEnemy) > m_MinimalDifferenceToAttackANewEnemy) // If the newfound enemy is at least x closer than the previous closest.
		{
			// Changed to different enemy
			m_pCurrentTarget = m_EnemiesInRange[i];
			m_OffsetWithCurrentTarget = FVector::Dist(actorLocation, m_pCurrentTarget->GetActorLocation());
		}

	}


	if (m_OffsetWithCurrentTarget < m_StrikingRange)
		IsAttacking = true;

	return m_pCurrentTarget;
}

bool AUnit::CheckIfStillAttacking() const
{
	if (!m_pCurrentTarget || m_OffsetWithCurrentTarget > m_MinimalOffsetToStopAttacking)
		return false;


	return true;
}

bool AUnit::Damage(float amount)// returns if dead
{
	return m_pHealthComponent->Damage(amount);
}

void AUnit::Heal(float amount)
{
	m_pHealthComponent->Heal(amount);
}

bool AUnit::IsDead() const
{
	return m_pHealthComponent->GetHealth() <= 0;
}

void AUnit::AnimationHitPlayed()
{
	if (!IsAttacking || !m_pCurrentTarget || m_AttackCooldown > 0)
		return;

	m_AttackCooldown = 1.0f;
	if (!m_pCurrentTarget->Damage(m_Damage))
		return;

	m_pCurrentTarget->Destroy();
	m_pCurrentTarget = nullptr;
			
}