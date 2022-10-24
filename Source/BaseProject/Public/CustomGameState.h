// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CustomGameState.generated.h"

/**
 * 
 */
UCLASS()
class BASEPROJECT_API ACustomGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	int32 Score = 0;

};
