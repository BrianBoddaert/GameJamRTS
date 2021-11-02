// Fill out your copyright notice in the Description page of Project Settings.


#include "MaterialManager.h"


// Sets default values
AMaterialManager::AMaterialManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> redMaterial(TEXT("/Game/Toony_Tiny_RTS_Set/Materials/Units/MI_Units_Red"));
	m_Materials.insert(std::pair<FString, UMaterialInterface*>("MI_Units_Red", redMaterial.Object));

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> blueMaterial(TEXT("/Game/Toony_Tiny_RTS_Set/Materials/Units/MI_Units_Blue"));
	m_Materials.insert(std::pair<FString, UMaterialInterface*>("MI_Units_Red", blueMaterial.Object));


}

AMaterialManager::~AMaterialManager()
{
	
}

// Called when the game starts or when spawned
void AMaterialManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMaterialManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UMaterialInterface* AMaterialManager::GetMaterialByName(const FString& name)
{
	if (m_Materials.find(name) != m_Materials.end())
		return m_Materials.at(name);

	return nullptr;
}
