// Fill out your copyright notice in the Description page of Project Settings.

#include "DolphinWorker.h"
#include "PlayerPawn.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

APlayerPawn *DolphinWorker::actor;

DolphinWorker::DolphinWorker(APlayerPawn *a)
{
    UE_LOG(LogTemp, Warning, TEXT("DolphinWorker::DolphinWorker(APlayerPawn *a) called!"));
    actor = a;

    thread = FRunnableThread::Create(this, TEXT("DolphinWorker"), 0, TPri_Normal);
}

DolphinWorker::~DolphinWorker()
{
    delete thread;
}

bool DolphinWorker::Init() {
    UE_LOG(LogTemp, Warning, TEXT("DolphinWorker::Init() called!"));
    return true;
}

uint32 DolphinWorker::Run() {
    UE_LOG(LogTemp, Warning, TEXT("DolphinWorker::Run() called!"));

    const char *path = "/Users/Mike/Library/Application Support/Dolphin/MemoryWatcher/MemoryWatcher";
    int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (fd < 0)
        printf("Can't create socket: %d\n", errno);
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    unlink(path);
    strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);
    if (bind(fd, (struct sockaddr*) &addr, sizeof(addr)) < 0)
        printf("Can't bind: %d\n", errno);

    char buf[128];
    while (1)
    {
        //Get outta here if we should stop
        if (shouldStop) return 0;

        struct sockaddr remaddr;
        socklen_t addr_len;
        recvfrom(fd, buf, sizeof(buf), 0, &remaddr, &addr_len);

        FString str = FString(ANSI_TO_TCHAR(buf));
        if (str.StartsWith("805bc9a4")) {
            //X pos
            float f = getWatcherFloat(str);
            actor->posX = f;
        } else if (str.StartsWith("805bc9a8")) {
            //Y pos
            float f = getWatcherFloat(str);
            actor->posY = f;
        } else if (str.StartsWith("805bc9ac")) {
            //Z pos
            float f = getWatcherFloat(str);
            actor->posZ = f;
        } else if (str.StartsWith("0054e058")) {
            //X cam pos
            float f = getWatcherFloat(str);
            actor->camX = f;
        } else if (str.StartsWith("0054e05C")) {
            //Y cam pos
            float f = getWatcherFloat(str);
            actor->camY = f;
        } else if (str.StartsWith("0054e060")) {
            //Z pos
            float f = getWatcherFloat(str);
            actor->camZ = f;
        } else if (str.StartsWith("0054e070")) {
            //XY cam rot
            uint16 x = getWatcherUInt16(str, 0);
            uint16 y = getWatcherUInt16(str, 4);
            actor->camRotX = FRotator::DecompressAxisFromShort(x);
            actor->camRotY = -FRotator::DecompressAxisFromShort(y) - 90.0f;
        }
    }

    return 0;
}

void DolphinWorker::Stop() {

}

float DolphinWorker::getWatcherFloat(FString &str) {
    FString pStr = str.Mid(9, 8);
    const char *pChr = TCHAR_TO_ANSI(*pStr);
    uint32 num;
    float f;
    sscanf(pChr, "%x", &num);
    f = *((float*) &num);
    return f;
}

uint16 DolphinWorker::getWatcherUInt16(FString &str, uint8 offset) {
    FString pStr = str.Mid(9 + offset, 4);
    const char *pChr = TCHAR_TO_ANSI(*pStr);
    uint32 num;
    sscanf(pChr, "%x", &num);
    uint16 s = (short) num;
    return s;
}

