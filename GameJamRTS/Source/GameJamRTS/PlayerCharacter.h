// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "PlayerCharacter.generated.h"

class SelectableObject;

UCLASS()
class GAMEJAMRTS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* pCameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* pPlayerCamera;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void OnLeftMouseClick();
	void ClickActorResult(const FHitResult&);
	void MoveUp(float Axis);
	void MoveRight(float Axis);
	void ZoomCamera(float Axis);
	
	SelectableObject* m_pSelectedActor = nullptr;

	float m_ZoomSpeed;
	float m_CameraSpeed;

	bool CheckHitUnderMouse(FHitResult& result);

	bool CheckHit(FHitResult& result, const FVector& start, const FVector& dir);
};
