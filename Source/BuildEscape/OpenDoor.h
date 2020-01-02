// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

private:

	// Vars for Opening door with relative Yaw
	float InitialYaw;
	float CurrentYaw;

	// Vars for Closing door
	float CurrentTime;
	float LastDoorOpenTime;

	// Vars for opening with PressurePlate
	AActor* ActorThatOpens;	// Pawn inherits from actor
	AActor* Owner; // The owning door

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Sets default values for this component's properties
	UOpenDoor();  // Constructor

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DelatTime);
	void CloseDoor(float DeltaTime);
	void InitializeYawToRelative();

	UPROPERTY(EditAnywhere)
	float TargetYaw = 90.0f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate; 
	
};
	

	

	

	
