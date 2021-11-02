// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Helpers.h"
#include "BarrackWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAMRTS_API UBarrackWidget : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
		bool BuyUnit(const eUnitType& type); // returns success

};
