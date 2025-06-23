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

	//���� ���� �ʱ�ȭ
	TotalDistanceMoved = 0.0;
	EventCount = 0;
}

// Called when the game starts or when spawned
void ARandomMovementActor::BeginPlay()
{
	Super::BeginPlay();

	//���� �� �ʱ�ȭ 
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

		// ���� ��ǥ
		int32 PrevX = CurrentX;
		int32 PrevY = CurrentY;

		// ���� �̵�
		int32 StepX = GetRandomStep();
		int32 StepY = GetRandomStep();

		// �� ��ǥ ���
		CurrentX += StepX;
		CurrentY += StepY;

		// �̵��Ÿ� ��� �� ��� (��Ŭ���� �Ÿ�)
		double Distance = CalculateDistance(PrevX, PrevY, CurrentX, CurrentY);
		TotalDistanceMoved += Distance;

		// �̺�Ʈ �߻� Ȯ�� �� ���
		bool bEventOccurred = ShouldGenerateEvent();
		FString EventStatus = bEventOccurred ? TEXT("Event Occurred.") : TEXT("No Event.");

		if (bEventOccurred)
		{
			EventCount++;
		}

		UE_LOG(LogTemp, Log, TEXT("Step %d : Moved by (%d, %d). Current Position : (%d, %d). Distance : %.2f. %s"), MoveCount, StepX, StepY, CurrentX, CurrentY, Distance, *EventStatus);

	}
	UE_LOG(LogTemp, Warning, TEXT("Random Movement Simulation Complete."));
	// �� �̵��Ÿ� �� �̺�Ʈ �߻� Ƚ�� ���
	UE_LOG(LogTemp, Warning, TEXT("Total Distance Moved : %.2f"), TotalDistanceMoved);
	UE_LOG(LogTemp, Warning, TEXT("Total Events Occurred : %d"), EventCount);
}
// RandRange Ȱ���Ͽ� 50% Ȯ���� �̺�Ʈ �߻� 
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
