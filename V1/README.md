# LittleStar V1

The goal of V1 is to learn [C++][C++_] and understand how a [3D][3D_] [game engine][GameEngine_] really works.
Every system is built from scratch to understand it.

## V1 Roadmap
- [x] Window creation (GLFW)
- [x] First triangle (OpenGL)
- [ ] Rendering (3D Models, Textures)
- [ ] Input (Keyboard, Mouse, Controller)
- [ ] Audio (Sound effects, Music)
- [ ] Event System
- [ ] Physics & Collision
- [ ] Scene Manager
- [ ] Scripting (Code execution in game)

## Building

First install the required [dependencies](#dependencies), if you don't already did it.

### Linux (tested)
```bash
git clone https://github.com/LorenzoLs-code/LittleStar
cd LittleStar/V1
mkdir build && cd build
cmake ..
make
```
Execute:
```bash
./LittleStar
```

### Windows (untested)
Should work with CMake and MinGW or MSVC:
```bash
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
```
Execute:
```bash
LittleStar.exe
```

> The Windows build is untested.
> If you get it working, please open an Issue!

### Mac (untested)
Should work with CMake and Xcode tools:
```bash
mkdir build && cd build
cmake ..
make
```
Execute:
```bash
./LittleStar
```

> The Mac build is untested.
> If you get it working, please open an Issue!

## Dependencies
- C++17
- OpenGL
- GLFW3
- GLEW

[3D_]: https://en.wikipedia.org/wiki/3D
[C++_]: https://en.wikipedia.org/wiki/C%2B%2B
[GameEngine_]: https://en.wikipedia.org/wiki/Game_engine
