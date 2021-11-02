// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "SelectableObject.h"
#include "Building.generated.h"

UCLASS(Abstract)
class GAMEJAMRTS_API ABuilding : public AActor, public SelectableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintCallable)
	//	virtual void OnClick() {};

	virtual void OnClick() override {};
	virtual void OnDeselect() override {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* m_pMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
