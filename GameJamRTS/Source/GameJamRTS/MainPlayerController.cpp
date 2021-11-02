// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

AMainPlayerController::AMainPlayerController()
{
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableTouchEvents = true;
    DefaultMouseCursor = EMouseCursor::GrabHand;
}