UnrealMonkeyBall
================

A kinda buggy way to get Super Monkey Ball 2 in Unreal Engine. This utilises Dolphin Emulator to run the game, while
Unreal grabs memory from Dolphin to position the ball and camera. This repo comes bundled with PseudonymousBN's
Propulsion Drive stage in Unreal.

UNIX sockets are required for Dolphin's MemoryWatcher, therefore you'll need to be running macOS or Linux.

Video: https://www.youtube.com/watch?v=bB0EwkMoHqw

Usage
=====

1. Copy the provided Locations.txt into `path/to/Dolphin/directory/MemoryWatcher/Locations.txt`. For example, on macOS,
it should be in `~/Library/Application Support/Dolphin/MemoryWatcher/Locations.txt`. You may have to create the
MemoryWatcher directory.

2. Edit the source to point to the location of the MemoryWatcher socket. The socket will be at
`DolphinDir/MemoryWatcher/MemoryWatcher`. Change the variable `*path` in `DolphinWorker::Run()` in the file
`Worker.cppSource/UnrealMonkeyBall/DolphinWorker.cpp`.

3. Compile and hit play in Unreal Engine

4. Launch Dolphin Emulator, and enable "Background Input" in the controls. This is so that Dolphin can still be
controlled when focused on the Unreal Engine window.

5. Launch Super Monkey Ball 2 in Dolphin

