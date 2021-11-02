// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <map>
#include "CoreMinimal.h"
#include "ServiceLocator.generated.h"

class AMoneyManager;
class AMaterialManager;

UCLASS()
class GAMEJAMRTS_API AServiceLocator : public AActor
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static AServiceLocator* GetInstance(UWorld* world);

	UFUNCTION(BlueprintCallable)
	AMoneyManager* GetMoneyManager(int player);

	UFUNCTION(BlueprintCallable)
	AMaterialManager* GetMaterialManager();
private:
	AServiceLocator()  = default;
	~AServiceLocator();


	static AServiceLocator* m_pInstance;

	AMaterialManager* m_pMaterialManager = nullptr;
	std::map<int, AMoneyManager*> m_MoneyManagers;
};
