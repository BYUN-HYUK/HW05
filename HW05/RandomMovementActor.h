#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomMovementActor.generated.h"

UCLASS()
class HW05_API ARandomMovementActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARandomMovementActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	int32 CurrentX;
	int32 CurrentY;

	int32 MoveCount;

	// 총 이동거리 
	double TotalDistanceMoved;

	// 총 이벤트 발생 횟수
	int32 EventCount;

	int32 GetRandomStep();
	void MoveCharacterRandomly();

	// 이벤트 발생 여부 (50%) 
	bool ShouldGenerateEvent();

	double CalculateDistance(int32 X1, int32 Y1, int32 X2, int32 Y2);

};