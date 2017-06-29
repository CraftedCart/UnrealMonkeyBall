// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class APlayerPawn;

class UNREALMONKEYBALL_API DolphinWorker : public FRunnable
{
    public:
        bool shouldStop = false;

    protected:
        FRunnableThread *thread;
        static APlayerPawn *actor;

    public:
        DolphinWorker(APlayerPawn *a);
        ~DolphinWorker();

        //FRunnable overloads
        virtual bool Init() override;
        virtual uint32 Run() override;
        virtual void Stop() override;

        float getWatcherFloat(FString &str);
        uint16 getWatcherUInt16(FString &str, uint8 offset);

};
