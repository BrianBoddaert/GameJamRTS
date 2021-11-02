// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"



class GAMEJAMRTS_API SelectableObject
{
	
public:	
	// Sets default values for this actor's properties
	SelectableObject() = default;
	virtual void OnClick() = 0;
	virtual void OnDeselect() = 0;
};
