#include "RandomMovementActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ARandomMovementActor::ARandomMovementActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CurrentX = 0;
	CurrentY = 0;
	MoveCount = 0;

	//도전 과제 초기화
	TotalDistanceMoved = 0.0;
	EventCount = 0;
}

// Called when the game starts or when spawned
void ARandomMovementActor::BeginPlay()
{
	Super::BeginPlay();

	//도전 값 초기화 
	CurrentX = 0;
	CurrentY = 0;
	MoveCount = 0;
	TotalDistanceMoved = 0.0;
	EventCount = 0;

	UE_LOG(LogTemp, Warning, TEXT("ARandomMovementActor has spawned!Starting random movement simulation."));
	UE_LOG(LogTemp, Warning, TEXT("Initial Position : (%d, %d"), CurrentX, CurrentY);

	MoveCharacterRandomly();
}

// Called every frame
void ARandomMovementActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 ARandomMovementActor::GetRandomStep() {
	return FMath::RandRange(0, 1);
}

double ARandomMovementActor::CalculateDistance(int32 X1, int32 Y1, int32 X2, int32 Y2)
{
	double dx = static_cast<double>(X2 - X1);
	double dy = static_cast<double>(Y2 - Y1);
	return FMath::Sqrt(dx * dx + dy * dy);
}

void ARandomMovementActor::MoveCharacterRandomly() {
	for (int32 i = 0; i < 10; ++i)
	{
		MoveCount++;

		// 이전 좌표
		int32 PrevX = CurrentX;
		int32 PrevY = CurrentY;

		// 랜덤 이동
		int32 StepX = GetRandomStep();
		int32 StepY = GetRandomStep();

		// 새 좌표 계산
		CurrentX += StepX;
		CurrentY += StepY;

		// 이동거리 계산 및 출력 (유클리드 거리)
		double Distance = CalculateDistance(PrevX, PrevY, CurrentX, CurrentY);
		TotalDistanceMoved += Distance;

		// 이벤트 발생 확인 및 출력
		bool bEventOccurred = ShouldGenerateEvent();
		FString EventStatus = bEventOccurred ? TEXT("Event Occurred.") : TEXT("No Event.");

		if (bEventOccurred)
		{
			EventCount++;
		}

		UE_LOG(LogTemp, Log, TEXT("Step %d : Moved by (%d, %d). Current Position : (%d, %d). Distance : %.2f. %s"), MoveCount, StepX, StepY, CurrentX, CurrentY, Distance, *EventStatus);

	}
	UE_LOG(LogTemp, Warning, TEXT("Random Movement Simulation Complete."));
	// 총 이동거리 총 이벤트 발생 횟수 출력
	UE_LOG(LogTemp, Warning, TEXT("Total Distance Moved : %.2f"), TotalDistanceMoved);
	UE_LOG(LogTemp, Warning, TEXT("Total Events Occurred : %d"), EventCount);
}
// RandRange 활용하여 50% 확률로 이벤트 발생 
bool ARandomMovementActor::ShouldGenerateEvent()
{
	int32 RandomValue = FMath::RandRange(1, 100);
	float Probability = 50.0f;

	if (RandomValue <= Probability)
	{
		return true;
	}
	else
	{
		return false;
	}
}
