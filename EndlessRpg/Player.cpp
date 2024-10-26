#include "Game.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Player.hpp"

Player::Player(double x, double y, SDL_Texture* tex, int f, int s)
    : Entity(x, y, tex), animeFrames(f), animeSpeed(s)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32; // player Width
    currentFrame.h = 27; // player height

    animeState = 0; 
    lastDirection = 1; // 1 = right   -1 = left

}

void Player::animate()
{
    switch(animeState)
    {
        case 0: // Idle right
            currentFrame.y = 0;
            currentFrame.x = currentFrame.w * static_cast<int>((SDL_GetTicks() / animeSpeed) % animeFrames);
            break;
        case 1: // Run right
            currentFrame.y = 32;
            currentFrame.x = currentFrame.w * static_cast<int>((SDL_GetTicks() / animeSpeed) % animeFrames);
            break;
        case 2: // Run left
            currentFrame.y = 32;
            currentFrame.x = currentFrame.w * static_cast<int>((SDL_GetTicks() / animeSpeed) % animeFrames) + 128;
            break;
        case 3: // idle left
            currentFrame.y = 0;
            currentFrame.x = currentFrame.w * static_cast<int>((SDL_GetTicks() / animeSpeed) % animeFrames) + 128;
            break;
        case 4: // lolz
            currentFrame.y = 288;
            currentFrame.x = currentFrame.w * static_cast<int>((SDL_GetTicks() / animeSpeed) % animeFrames);
            break;
    }
}


void Player::handleCollision(int screenWidth, int screenHeight)
{
    // if (this != entity && checkCollision(*entity))
    // {
    //     Vec2 entPos = entity->getPosition();

    //     const int playerHeight = 120;
    //     const int playerWidth = 128;
    //     const int tilewidth = 64;

    //     int playerTop = position.y;
    //     int playerBottom = position.y + playerHeight;
    //     int playerLeft = position.x;
    //     int playerRight = position.x + playerWidth;

    //     int entityTop = entPos.y;
    //     int entityBottom = entPos.y + tilewidth;
    //     int entityLeft = entPos.x;
    //     int entityRight = entPos.x + tilewidth;

    //     std::cout << "Player Top: " << playerTop << ", Bottom: " << playerBottom << ", Left: " << playerLeft << ", Right: " << playerRight << std::endl;
    //     std::cout << "Entity Top: " << entityTop << ", Bottom: " << entityBottom << ", Left: " << entityLeft << ", Right: " << entityRight << std::endl;

        
    //     if (playerBottom <= entityTop) {
    //         // Player is above the entity
    //         //position.y = entityTop - playerHeight;
    //         velocity.y = 0;
    //         std::cout << "Player moved above entity" << std::endl;
    //     } 
    //     else if (playerTop >= entityBottom) {
    //         // Player is below the entity
    //         //position.y = entityBottom;
    //         velocity.y *= -1;
    //         std::cout << "Player moved below entity" << std::endl;
    //     } 
    //     else if (playerRight <= entityLeft) {
    //         // Player is to the left of the entity
    //         velocity.x = 0;
    //         std::cout << "Player moved left of entity" << std::endl;
    //     } 
    //     else if (playerLeft >= entityRight) {
    //         // Player is to the right of the entity
    //         velocity.x = 0;
    //         std::cout << "Player moved right of entity" << std::endl;
    //     }
    // }
        
    // check collision with screen boundry
    if (position.x < 0) 
    {
        position.x = 0;
    }
    if (position.x + currentFrame.w * 4 > screenWidth) 
    {
        position.x = screenWidth - (currentFrame.w * 4);
    }
    if (position.y < 0) 
    {
        position.y = 0;
    }
    if (position.y + currentFrame.h * 4 > screenHeight - 64) 
    {
            position.y = screenHeight - (currentFrame.h * 4 + 64);
    }

}

void Player::playerControls()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    velocity.x = 0;

    if (velocity.x == 0)
    {
        if (lastDirection == 1) 
        {
            animeState = 0; // idle right
        } else if (lastDirection == -1) 
        {
            animeState = 3; // idle left 
        }

    }

    if (state[SDL_SCANCODE_A]) //MOVE LEFT
    {
        velocity.x = -10;
        position.x += velocity.x;
        animeState = 2; // run left
        lastDirection = -1;
    }
    if (state[SDL_SCANCODE_D]) //MOVE Right
    {
        velocity.x = 10;
        position.x += velocity.x;
        animeState = 1; // run right
        lastDirection = 1;
    }
    if (state[SDL_SCANCODE_W]) //JUMP
    {
        velocity.y = -10;
        position.y += velocity.y;
        animeState = 1; // run right
        lastDirection = 1;
    }
    if (state[SDL_SCANCODE_S]) //MOVE LEFT
    {
        velocity.y = 10;
        position.y += velocity.y;
        animeState = 2; // run left
        lastDirection = -1;
    }
    if (state[SDL_SCANCODE_X]) //lolz
    {
        animeState = 4;
    }

}
