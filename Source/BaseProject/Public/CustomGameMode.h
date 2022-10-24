// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BASEPROJECT_API ACustomGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ACustomGameMode();
	virtual ~ACustomGameMode() = default;

	virtual void StartPlay() override;

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void SetScore(int32 NewScore);

	void SpawnCube() const;

private:

	FTimerHandle Ticker;
};
