// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameMode.h"
#include "CustomARPawn.h"
#include "CustomGameState.h"
#include "LogUtils.h"
#include "CustomActor.h"

ACustomGameMode::ACustomGameMode() {
	DefaultPawnClass = ACustomARPawn::StaticClass();
	GameStateClass = ACustomGameState::StaticClass();

	PrimaryActorTick.bCanEverTick = true;
}

void ACustomGameMode::StartPlay() {
	info("before begin play, current score: %d", GetScore());

	Super::StartPlay();

	GetWorldTimerManager().SetTimer(Ticker, this, &ACustomGameMode::SpawnCube, 4.f, true, 0.f);
}

int32 ACustomGameMode::GetScore() const {
	ACustomGameState *CustomGameState = GetGameState<ACustomGameState>();
	if (!CustomGameState) {
		return 0;
	}

	return CustomGameState->Score;
}

void ACustomGameMode::SetScore(int32 NewScore) {
	ACustomGameState* CustomGameState = GetGameState<ACustomGameState>();
	if (!CustomGameState) {
		return;
	}

	CustomGameState->Score = NewScore;
}

void ACustomGameMode::SpawnCube() const {
	FActorSpawnParameters SpawnInfo;
	FRotator Rotator(0, 0, 0);
	FVector Location(FMath::RandRange(-300.f, 300.f), 0, 0);
	ACustomActor* CustomActor = GetWorld()->SpawnActor<ACustomActor>(Location, Rotator, SpawnInfo);
}
