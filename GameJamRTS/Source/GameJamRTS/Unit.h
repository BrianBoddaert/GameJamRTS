// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Animation/SkeletalMeshActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Unit.generated.h"

UCLASS()
class GAMEJAMRTS_API AUnit : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnit();

	void Initialize(int team); // Has to be called when being spawned!

	void SetDestination(const FVector& destination);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool IsWalking   = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		bool IsAttacking = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveTo();
	FVector m_Direction;
	FVector m_Destination;
	float m_WalkSpeed = 1.0f;
	int m_Team = 1;



	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//	USkeletalMeshComponent* m_pSkeletalMesh;
//
//private:



};
