#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Vec2.hpp"

class Entity
{
protected:
    Vec2 position;
    SDL_Rect currentFrame;
    SDL_Texture* texture;
public:
    Entity(double x, double y, SDL_Texture* tex);

    Vec2& getPosition();
    SDL_Texture* getTexture();
    SDL_Rect getCurrentFrame() const;

    virtual void animate();
    bool checkCollision(const Entity& other) const;
};