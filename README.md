# Pong Game

C++ implementation of the classic Pong game.

## Dependencies

- SDL2
- CMake


For Ubuntu-based systems, you can install the dependencies using:

```bash
sudo apt install libsdl2-dev cmake
```

For Arch-based systems, you can install the dependencies using:

```bash
sudo pacman -S sdl2 cmake
```

For RPM-based systems like Fedora, you can install the dependencies using:

```bash
sudo dnf install SDL2-devel cmake
```

## Building 

To install the Pong game, clone the repository and navigate to the project directory:

```bash
git clone https://www.github.com/kmr-ankitt/pong.git
cd pong
```

Build the project using CMake:

```bash
cmake -S . -B build
cmake --build build
```

## Running

Run the binary to start the game:

```bash
./build/pong
```
