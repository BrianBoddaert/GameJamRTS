// Fill out your copyright notice in the Description page of Project Settings.


#include "ServiceLocator.h"
#include "MaterialManager.h"
#include "MoneyManager.h"

AServiceLocator* AServiceLocator::m_pInstance = nullptr;

AServiceLocator* AServiceLocator::GetInstance(UWorld* world)
{
	if (!m_pInstance)
		m_pInstance = world->SpawnActor<AServiceLocator>(FVector(0, 0, 0), FRotator(0, 0, 0));

	return m_pInstance;
}

AServiceLocator::~AServiceLocator()
{
	m_pInstance = nullptr;
	m_pMaterialManager = nullptr;
	m_MoneyManagers.clear();
}
AMoneyManager* AServiceLocator::GetMoneyManager(int player)
{
	if (m_MoneyManagers.find(player) == m_MoneyManagers.end())
		m_MoneyManagers.insert(std::pair<int,AMoneyManager*>(player, GetWorld()->SpawnActor<AMoneyManager>(FVector(0, 0, 0), FRotator(0, 0, 0))));
	
	return m_MoneyManagers.at(player);
}

AMaterialManager* AServiceLocator::GetMaterialManager()
{

	if (!m_pMaterialManager)
		m_pMaterialManager = GetWorld()->SpawnActor<AMaterialManager>(FVector(0, 0, 0), FRotator(0, 0, 0));

	return m_pMaterialManager;
}