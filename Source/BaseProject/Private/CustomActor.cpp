#include "CustomActor.h"
#include "LogUtils.h"

#define ArrLen(arr) sizeof(arr) / sizeof(*(arr))

// Sets default values
ACustomActor::ACustomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

#if 0
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshAsset.Succeeded()) {
		StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
	}
	else {
		err("couldn't load mesh asset");
	}

	const TCHAR* MaterialNames[] = {
		TEXT("Material'/Game/StarterContent/Materials/M_Wood_Floor_Walnut_Polished.M_Wood_Floor_Walnut_Polished'"),
		TEXT("Material'/Game/StarterContent/Materials/M_Ground_Grass.M_Ground_Grass'"),
		TEXT("Material'/Game/StarterContent/Materials/M_Brick_Clay_New.M_Brick_Clay_New'"),
		TEXT("Material'/Game/StarterContent/Materials/M_CobbleStone_Pebble.M_CobbleStone_Pebble'"),
		TEXT("Material'/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold'"),
	};
	auto MaterialAsset = ConstructorHelpers::FObjectFinder<UMaterial>(MaterialNames[FMath::Rand() % ArrLen(MaterialNames)]);
	if (MaterialAsset.Succeeded()) {
		StaticMeshComponent->SetMaterial(0, MaterialAsset.Object);
	}
	else {
		err("couldn't load material asset");
	}
#endif
}

// Called when the game starts or when spawned
void ACustomActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Time = GetGameTimeSinceCreation();
	float Scale = 2.f / (3.f - cosf(2 * Time));
	FVector RelLocation = FVector::Zero();
	RelLocation.X = Scale * cosf(Time);
	RelLocation.Y = Scale * sinf(2 * Time) / 2.f;

	InitMatrix.SetIdentity();
	InitMatrix.M[3][0] = InitLocation.X;
	InitMatrix.M[3][1] = InitLocation.Y;
	InitMatrix.M[3][2] = InitLocation.Z;

	FMatrix MovingMatrix = FMatrix::Identity;
	MovingMatrix.M[3][0] = RelLocation.X;
	MovingMatrix.M[3][1] = RelLocation.Y;
	MovingMatrix.M[3][2] = RelLocation.Z;

	FMatrix FinalMatrix = MovingMatrix * InitMatrix;
	SetActorTransform(FTransform(FinalMatrix));
}

void ACustomActor::PostInitializeComponents() {
	Super::PostInitializeComponents();

	InitLocation = GetActorLocation();
}

