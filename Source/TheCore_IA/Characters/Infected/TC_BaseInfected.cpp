// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Infected/TC_BaseInfected.h"

// Sets default values
ATC_BaseInfected::ATC_BaseInfected()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATC_BaseInfected::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATC_BaseInfected::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATC_BaseInfected::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

