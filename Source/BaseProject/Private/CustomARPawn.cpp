// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomARPawn.h"
#include "ARBlueprintLibrary.h"
#include "LogUtils.h"
#include "CustomActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACustomARPawn::ACustomARPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
}

// Called when the game starts or when spawned
void ACustomARPawn::BeginPlay()
{
	Super::BeginPlay();

	UARSessionConfig* Config = NewObject<UARSessionConfig>();
	UARBlueprintLibrary::StartARSession(Config);
}

// Called every frame
void ACustomARPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACustomARPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!PlayerInputComponent) {
		return;
	}

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ACustomARPawn::OnScreenTouch);
}

void ACustomARPawn::OnScreenTouch(ETouchIndex::Type FingerIndex, FVector ScreenPos) {
	info("screen touched");
	FHitResult HitResult;
	if (!WorldHitTest(FVector2D(ScreenPos), HitResult)) {
		warn("nothing pressed");
		return;
	}

	// Get object of hit actor
	UClass* HitActorClass = UGameplayStatics::GetObjectClass(HitResult.GetActor());
	
	// if we've hit a target
	if (UKismetMathLibrary::ClassIsChildOf(HitActorClass, ACustomActor::StaticClass())) {
		debug("cube clicked!");
	}
}

bool ACustomARPawn::WorldHitTest(FVector2D ScreenPos, FHitResult& OutResult) {
	TObjectPtr<APlayerController> PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!PlayerController) {
		return false;
	}

	// Perform deprojection taking 2d clicked area and generating reference in 3d world-space
	FVector WorldPos, WorldDir;
	bool DeprojectionSuccess = UGameplayStatics::DeprojectScreenToWorld(PlayerController, ScreenPos, WorldPos, WorldDir);

	// Construct trace vector (from point clicked to 1000.0 units beyond in the same direction)
	FVector TraceEnd = WorldPos + WorldDir * 1000.f;

	// Perform line trace (Raycast)
	bool TraceSuccess = GetWorld()->LineTraceSingleByChannel(OutResult, WorldPos, TraceEnd, ECollisionChannel::ECC_WorldDynamic);

	return TraceSuccess;
}

