#pragma once
#include <SDL.h>
#include <memory>
using namespace std;

class Rect {
public:
    int x, y, width, height;
    Rect(int x, int y, int width, int height);
};

class Room {
public:
    Rect bounds;
    Room(int x, int y, int width, int height);
};

class BSPNode {
public:
    Rect bounds;
    std::unique_ptr<BSPNode> left;
    std::unique_ptr<BSPNode> right;
    Room* room;

    BSPNode(const Rect& bounds) : bounds(bounds), room(nullptr) {}
};

class MapGenerator {
public:
    MapGenerator(int width = 1200, int height = 720);
    void renderMap(SDL_Renderer* renderer);

private:
    bool splitNode(BSPNode& node, int minRoomSize);
    void createRooms(BSPNode& node, int minRoomSize);
    void connectRooms(BSPNode& node, SDL_Renderer* renderer);

    BSPNode root;
};
