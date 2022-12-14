// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "CustomARPawn.generated.h"

UCLASS()
class BASEPROJECT_API ACustomARPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACustomARPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnScreenTouch(ETouchIndex::Type FingerIndex, FVector ScreenPos);

	bool WorldHitTest(FVector2D ScreenPos, FHitResult& OutResult);

public:
	UPROPERTY(Category="ArProj", VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent = nullptr;

	UPROPERTY(Category="ArProj", VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComponent = nullptr;
};
