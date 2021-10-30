// Fill out your copyright notice in the Description page of Project Settings.


#include "Knight.h"

// Sets default values
AKnight::AKnight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> bMesh(TEXT("/Game/Toony_Tiny_RTS_Set/Meshes/Characters_Prebuilt/Units/SK_Swordman"));
	GetMesh()->SetSkeletalMesh(bMesh.Object);
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Game/Toony_Tiny_RTS_Set/Meshes/Marker/SM_Marker"));
	
	//m_pSkeletalMesh
	//m_pSkeletalMesh->SetStaticMesh();
	
	//m_pDestinationPencilMesh = destinationSelectorMesh.Object;

}

// Called when the game starts or when spawned
void AKnight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKnight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

