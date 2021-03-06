// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitializeYawToRelative();

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();
	
}

void UOpenDoor::InitializeYawToRelative() {

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;
}

void UOpenDoor::OpenDoor(float DeltaTime) {


	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, 1.0f * DeltaTime);

	FRotator DoorRotation = Owner->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	Owner->SetActorRotation(DoorRotation);


}

void UOpenDoor::CloseDoor(float DeltaTime) {

	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, 1.0f * DeltaTime);

	FRotator DoorRotation = Owner->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	Owner->SetActorRotation(DoorRotation);
	
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);

	// Need to get AActor and pass into function.


	// Poll the Trigger Volume
	// If the ActorThatOpens is in the volume
	if(PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))   // checks for null assigned to PressurePlate
	{
		OpenDoor(DeltaTime);
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	// Check if its time to close the door

	CurrentTime = GetWorld()->GetTimeSeconds();

	if(CurrentTime - LastDoorOpenTime > DoorCloseDelay) {
		CloseDoor(DeltaTime);
	}

}

