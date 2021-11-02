// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoneyManager.generated.h"

class AServiceLocator;

UCLASS()
class GAMEJAMRTS_API AMoneyManager : public AActor
{
	GENERATED_BODY()
public:

private:
	AMoneyManager() = default;
	~AMoneyManager() = default;

	friend class AServiceLocator;

	int m_PlayerNumber;
};
