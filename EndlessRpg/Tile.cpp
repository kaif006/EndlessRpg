#include "Game.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Tile.hpp"

Tile::Tile(double x, double y, SDL_Texture* tex): Entity(x,y,tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32 * 2; // tile width
    currentFrame.h = 32 * 2; // tile height
}
