// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <map>
#include "MaterialManager.generated.h"

class AServiceLocator;

UCLASS()
class GAMEJAMRTS_API AMaterialManager : public AActor
{
	GENERATED_BODY()
	
public:	

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	UMaterialInterface* GetMaterialByName(const FString& name);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

private:
	// Sets default values for this actor's properties
	AMaterialManager();
	~AMaterialManager();

	friend class AServiceLocator;

	std::map<FString, UMaterialInterface*> m_Materials;
};
