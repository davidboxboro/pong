# Pong

A C++/SFML Pong game against a computer-controlled paddle, with four difficulty levels, paddle-motion-dependent ball deflection, randomized backgrounds, and textured balls.

## Build and play

Open `pong.xcodeproj` in Xcode and configure the SFML 2 framework paths for your installation. Set `RESOURCE_PATH` in `pong/constants.hpp` to the absolute path of this checkout's `pong/Resources/` directory, then build and run.

Move the mouse to control the right paddle. Press **E**, **M**, **H**, or **I** to start at Easy, Medium, Hard, or Impossible difficulty. First to three points wins; choose a difficulty again to restart.
