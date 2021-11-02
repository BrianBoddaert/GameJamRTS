// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "BarrackWidget.h"
#include "Barrack.generated.h"

UCLASS()
class GAMEJAMRTS_API ABarrack : public ABuilding
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABarrack();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnClick() override;
	void OnDeselect() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Class
	TSubclassOf<UBarrackWidget> m_pBarrackWidgetClass = nullptr;
	// Obj
	UBarrackWidget* m_pBarrackWidget = nullptr;

	bool m_Visible = false;
};
