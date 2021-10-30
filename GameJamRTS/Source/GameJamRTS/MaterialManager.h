// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <map>
#include "MaterialManager.generated.h"


UCLASS()
class GAMEJAMRTS_API AMaterialManager : public AActor
{
	GENERATED_BODY()
	
public:	
	static AMaterialManager* GetInstance(UWorld* world);

	// Sets default values for this actor's properties
	AMaterialManager();
	~AMaterialManager();

	virtual void Tick(float DeltaTime) override;

	UMaterialInterface* GetMaterialByName(const FString& name);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

private:
	static AMaterialManager* m_pInstance;


	std::map<FString, UMaterialInterface*> m_Materials;
};
