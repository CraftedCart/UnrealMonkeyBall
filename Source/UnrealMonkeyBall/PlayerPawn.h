// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DolphinWorker.h"
#include "PlayerPawn.generated.h"

UCLASS()
    class UNREALMONKEYBALL_API APlayerPawn : public APawn
{
    GENERATED_BODY()

    public:
        DolphinWorker *wkr;

        float posX = 0.0f;
        float posY = 0.0f;
        float posZ = 0.0f;

        float camX = 0.0f;
        float camY = 0.0f;
        float camZ = 0.0f;

        float camRotX = 0.0f;
        float camRotY = 0.0f;

        UCameraComponent *cam;
        UStaticMeshComponent *mesh;

    public:
        // Sets default values for this pawn's properties
        APlayerPawn();

    protected:
        // Called when the game starts or when spawned
        virtual void BeginPlay() override;
        virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    public:
        // Called every frame
        virtual void Tick(float DeltaTime) override;

        // Called to bind functionality to input
        virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};
