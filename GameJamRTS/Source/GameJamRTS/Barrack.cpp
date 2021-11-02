// Fill out your copyright notice in the Description page of Project Settings.


#include "Barrack.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABarrack::ABarrack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	{
		wchar_t* path = L"/Game/Widgets/BP_UnitSelection";
		static ConstructorHelpers::FClassFinder<UUserWidget> theClass(path);
		if (theClass.Succeeded())
			m_pBarrackWidgetClass = theClass.Class;
	}

}

// Called when the game starts or when spawned
void ABarrack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABarrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABarrack::OnClick()
{
	// Open the spawn unit HUD
	if (!m_pBarrackWidget)
	m_pBarrackWidget = CreateWidget<UBarrackWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), m_pBarrackWidgetClass);

	if (!m_Visible)
	{
		m_pBarrackWidget->AddToViewport(0); // Problematic with multiplayer ?
		m_Visible = true;
	}
	
	// Open the currently spawning units HUD
}

void ABarrack::OnDeselect()
{
	if (m_pBarrackWidget && m_Visible)
	{
		m_pBarrackWidget->RemoveFromParent();
		m_Visible = false;
	}
		
}