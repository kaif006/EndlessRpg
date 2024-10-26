#include "Game.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Tile.hpp"
#include "Player.hpp"

Game::Game()
{}

Game::~Game()
{
    for(Entity* entity : entities) {
        delete entity;
    }
    entities.clear();

    delete player;
}

void Game::init(const char* title, int width, int height, bool fullScreen)
{
    
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = RenderWindow(title, width, height, fullScreen);
        isRunning = true;
    }
    else{isRunning = false;}

    // inititalize player and level
    initLevel();

    SDL_Texture* playerTex = window.loadTexture("C:\\Users\\pc\\Documents\\Coding\\sprites\\lancelot_.png");
    //entities.push_back(new Player(100, 100, playerTex, 4, 150));
    player = new Player(100, 20, playerTex, 4, 190);

    // generate map
    
    mapGenerated = true;

}

void Game::initLevel()
{
    /*SDL_Texture* platformTex = window.loadTexture("C:\\Users\\pc\\Documents\\Coding\\sprites\\Fire_4_16x16.png");
    SDL_Texture* ceilingTex = window.loadTexture("C:\\Users\\pc\\Documents\\Coding\\sprites\\Fire_19_16x16.png");
    SDL_Texture* diamondTex = window.loadTexture("C:\\Users\\pc\\Documents\\Coding\\sprites\\Fire_24_16x16.png");

    for(int x = 0; x <= 1280; x += 64)
     {
        entities.push_back(new Tile(x, 656, platformTex));
        if((x >= 192 && x <= 384) || (x >= 856))
            entities.push_back(new Tile(x, 400, ceilingTex));
        if(x > 384 && x < 856)
            entities.push_back(new Tile(x, 200, diamondTex));
     }*/
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    
    default:
        break;
    }

}

void Game::update()
{ 
    player->animate();
    //player->applyGravity();
    player->handleCollision(1280, 720);
    
    player->playerControls();
    
}

void Game::render()
{
    window.clear();
    SDL_Texture* BGtex = window.loadTexture("C:\\Users\\pc\\Documents\\Coding\\sprites\\WhatsApp Image 2024-07-03 at 8.45.57 PM.jpeg");
    //window.renderBG(BGtex);

    for(Entity* entity : entities)
    {
            window.renderEntity(*entity);
    }

    
    if (mapGenerated) 
    {
        mapGenerator.renderMap(window.getRenderer());
    }
    
    window.renderEntity(*player, 4.0f);

    window.display();
}

void Game::clean()
{
    window.cleanUp();
}

bool Game::running()
{
    return isRunning;
}
