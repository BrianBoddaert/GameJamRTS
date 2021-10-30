// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/CharacterMovementComponent.h"
#include "Unit.h"
#include "MaterialManager.h"

// Sets default values
AUnit::AUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);



}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	SetDestination(FVector(-100,0,0));

	Initialize(1);
}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsWalking)
		MoveTo();
}



void AUnit::SetDestination(const FVector & destination)
{
	m_Destination = destination;
	m_Direction = destination.GetSafeNormal();
	IsWalking = true;
}

void AUnit::MoveTo()
{
	AddMovementInput(m_Direction, m_WalkSpeed);

	// v Check if reached destination
	float offset = 1.0f;
	if (FVector::Dist(GetActorLocation(), m_Destination) < offset)
		IsWalking = false;

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