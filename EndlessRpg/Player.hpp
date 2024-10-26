#pragma once
#include "Game.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "RenderWindow.hpp"
#include "Entity.hpp"

class Player: public Entity
{
    int animeSpeed;
    int animeFrames;
    Vec2 velocity;
    //bool onGround = false;
    //double jumpForce = -15;
    int animeState;
    int lastDirection; // 1 = right   -1 = left

public: 
    Player(double x, double y, SDL_Texture*tex, int f, int s);

    void animate() override;
    //void applyGravity();

    void handleCollision(int screenWidth, int screenHeight);
    
    void playerControls();

};