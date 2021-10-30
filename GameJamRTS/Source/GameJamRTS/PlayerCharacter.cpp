// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
	:m_ZoomSpeed{2000.0f}
	,m_CameraSpeed{ 1000.0f }
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	pCameraBoom->SetupAttachment(RootComponent, "headSocket");
	pCameraBoom->TargetArmLength = 0.0f;
	pCameraBoom->bUsePawnControlRotation = true;
	pCameraBoom->bInheritPitch = false;
	pCameraBoom->bInheritYaw = false;
	pCameraBoom->bInheritRoll = false;
	//pCameraBoom->AddRelativeRotation(FRotator(0, 45, 45));

	pPlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	
	pPlayerCamera->SetupAttachment(pCameraBoom, USpringArmComponent::SocketName);
	pPlayerCamera->bUsePawnControlRotation = false;

	
	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveUp);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	InputComponent->BindAxis("Zoom", this, &APlayerCharacter::ZoomCamera);
}

void APlayerCharacter::ZoomCamera(float Axis)
{
	if (Axis == 0.f)
		return;

	Axis *= -1; // Flipping axis

	if (pCameraBoom->TargetArmLength >= 1000.f && Axis > 0.f)
		return;
	if (pCameraBoom->TargetArmLength <= 0.f && Axis < 0.f)
		return;

	pCameraBoom->TargetArmLength += Axis * m_ZoomSpeed * GetWorld()->GetDeltaSeconds();
}

void APlayerCharacter::MoveUp(float Axis) // Up
{
	if (Axis == 0)
		return;

	FVector dir{ 0.71f,0.71f,0 };
	auto pos = GetActorLocation();

	SetActorLocation(pos + dir*Axis* m_CameraSpeed * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::MoveRight(float Axis)
{
	if (Axis == 0)
		return;

	FVector dir{ -0.71f,0.71f,0 };
	auto pos = GetActorLocation();

	SetActorLocation(pos + dir * Axis * m_CameraSpeed * GetWorld()->GetDeltaSeconds());
}
