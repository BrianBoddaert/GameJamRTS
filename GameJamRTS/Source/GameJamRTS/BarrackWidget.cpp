// Fill out your copyright notice in the Description page of Project Settings.


#include "BarrackWidget.h"

bool UBarrackWidget::BuyUnit(const eUnitType& unitType) // returns success
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Test");

	return true;
}