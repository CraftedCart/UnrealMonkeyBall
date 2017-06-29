// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
    Super::BeginPlay();

    wkr = new DolphinWorker(this);

    TArray<UCameraComponent*> comps;

    this->GetComponents(comps);
    for (UCameraComponent *comp : comps) {
        cam = comp;
        UE_LOG(LogTemp, Warning, TEXT("Found camera component"));
    }

    TArray<UStaticMeshComponent*> meshes;

    this->GetComponents(meshes);
    for (UStaticMeshComponent *comp : meshes) {
        mesh = comp;
        UE_LOG(LogTemp, Warning, TEXT("Found mesh component"));
        break; //TODO: Breaking is a bit hacky, but it works!
    }
}

void APlayerPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    wkr->shouldStop = true;
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FRotator camRot(camRotX, camRotY, 0.0f);

    mesh->SetWorldLocation(FVector(posX * 100.0f, posZ * 100.0f, posY * 100.0f), false);
    cam->SetWorldLocation(FVector(camX * 100.0f, camZ * 100.0f, camY * 100.0f), false);
    cam->SetWorldRotation(camRot, false);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

