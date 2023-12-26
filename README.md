<!-- ABOUT THE PROJECT -->
## Introduction
This game, developed with C++ and SDL2, uniquely combines a shooter game's thrills with the educational challenge of vocabulary memorization. Designed to make learning exhilarating, it features three vocabulary categories: finance, natural science, and computer science. Players encounter ten words per category and have ten seconds to remember the spelling of each word. Once memorized, players need to eliminate English letters in the correct order to spell the words. Mistakes in the sequence or getting hit by a letter cost health points. The objective is to complete the spellings before health points run out. This game tests memory and spelling skills and players' agility under pressure.

<p align="center">
  <img src=https://github.com/AndyLinGitHub/SDL2-Game-Programming/blob/master/image/demo.gif>
</p>

Full Demo Video: https://youtu.be/DuKH1ZL2wAA

## Installation
### Windows
You can download here: https://drive.google.com/file/d/1mmjflhpLGcYuKDt9sCSm94FbqjxE031J/view?usp=drive_link for Windows, or you can download the files in this repository and set up environment with SDL2 to execute this project.

### Linux
```
git clone git@github.com:AndyLinGitHub/SDL2-Game-Programming.git
cd SDL2-Game-Programming
git clone https://github.com/libsdl-org/SDL.git -b SDL2
git clone https://github.com/libsdl-org/SDL_mixer -b SDL2
git clone https://github.com/libsdl-org/SDL_image -b SDL2
git clone https://github.com/libsdl-org/SDL_ttf -b SDL2
mkdir build
cd build
cmake ..
make
./sdl2_game
```
