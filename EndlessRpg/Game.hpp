#pragma once 
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "MapGenerator.hpp"

using namespace std;

class Game
{
protected:
    bool isRunning;
    RenderWindow window;
    vector <Entity*> entities;
    Player* player;
    MapGenerator mapGenerator;
    bool mapGenerated;

public:
    Game();
    ~Game();
    void init(const char* title, int width, int height, bool fullScreen);
    void initLevel();
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running();
};