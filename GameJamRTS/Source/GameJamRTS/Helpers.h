// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Helpers.generated.h"



UENUM()
enum eUnitType
{
	Infantry    UMETA(DisplayName = "Infantry"),
	Archer      UMETA(DisplayName = "Archer"),
	Commander   UMETA(DisplayName = "Commander"),
};

UCLASS()
class GAMEJAMRTS_API AHelpers : public AActor
{
	GENERATED_BODY()

public:
	AHelpers() = default;
	~AHelpers() = default;


private:

};