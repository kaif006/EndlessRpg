#include "RenderWindow.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Entity.hpp"

using namespace std;

RenderWindow::RenderWindow()
{}

RenderWindow::RenderWindow(const char* title, int width, int height, bool fullScreen): window(NULL), renderer(NULL)
{
    int flags = 0;
    if(fullScreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
    if(window == NULL)
    {
        cout << "Failed to initialize window" << SDL_GetError() <<  endl;
    } 

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
    
SDL_Texture* RenderWindow::loadTexture(const char* file_path)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, file_path);

    if(texture == NULL)
    {
        cout << "Failed to load texture" << SDL_GetError() << endl;
    }
    return texture;
}
    
void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::renderEntity(Entity &entity, float scale)
{
    SDL_Rect src; // source rect
    src.x = entity.getCurrentFrame().x;
    src.y = entity.getCurrentFrame().y;
    src.w = entity.getCurrentFrame().w;
    src.h = entity.getCurrentFrame().h;

    SDL_Rect des; // destination rect
    des.x = entity.getPosition().x;
    des.y = entity.getPosition().y;
    des.w = entity.getCurrentFrame().w * scale;
    des.h = entity.getCurrentFrame().h * scale;
    
    SDL_RenderCopy(renderer, entity.getTexture(), &src, &des);
}

void RenderWindow::renderBG(SDL_Texture* tex)
{
    SDL_RenderCopy(renderer, tex, NULL, NULL);
}

void RenderWindow::renderMap(MapGenerator& mapGen) 
{
    mapGen.renderMap(renderer);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

SDL_Renderer* RenderWindow::getRenderer()
{
    return renderer;
}