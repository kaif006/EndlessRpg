#include "MapGenerator.hpp"

Rect::Rect(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {}

Room::Room(int x, int y, int width, int height)
    : bounds(x, y, width, height) {}

MapGenerator::MapGenerator(int width, int height) : root(Rect(0, 0, width, height)) {
    // Generate the map on construction
    splitNode(root, 10);
    createRooms(root, 10);
}


bool MapGenerator::splitNode(BSPNode& node, int minRoomSize) {
    bool splitHorizontally = (rand() % 2 == 0);
    int maxSize = (splitHorizontally ? node.bounds.height : node.bounds.width) - minRoomSize;

    if (maxSize <= minRoomSize) {
        return false;
    }

    int splitAt = rand() % (maxSize - minRoomSize) + minRoomSize;

    if (splitHorizontally) {
        node.left = std::make_unique<BSPNode>(Rect(node.bounds.x, node.bounds.y, node.bounds.width, splitAt));
        node.right = std::make_unique<BSPNode>(Rect(node.bounds.x, node.bounds.y + splitAt, node.bounds.width, node.bounds.height - splitAt));
    }
    else {
        node.left = std::make_unique<BSPNode>(Rect(node.bounds.x, node.bounds.y, splitAt, node.bounds.height));
        node.right = std::make_unique<BSPNode>(Rect(node.bounds.x + splitAt, node.bounds.y, node.bounds.width - splitAt, node.bounds.height));
    }

    return true;
}

void MapGenerator::createRooms(BSPNode& node, int minRoomSize) {
    if (node.left && node.right) {
        createRooms(*node.left, minRoomSize);
        createRooms(*node.right, minRoomSize);
    }
    else {
        int roomWidth = rand() % (node.bounds.width - minRoomSize) + minRoomSize;
        int roomHeight = rand() % (node.bounds.height - minRoomSize) + minRoomSize;

        int x = node.bounds.x + rand() % (node.bounds.width - roomWidth);
        int y = node.bounds.y + rand() % (node.bounds.height - roomHeight);

        node.room = new Room(x, y, roomWidth, roomHeight);
    }
}

void MapGenerator::connectRooms(BSPNode& node, SDL_Renderer* renderer) {
    if (node.left && node.right && node.left->room && node.right->room) {
        int leftX = node.left->room->bounds.x + node.left->room->bounds.width / 2;
        int leftY = node.left->room->bounds.y + node.left->room->bounds.height / 2;
        int rightX = node.right->room->bounds.x + node.right->room->bounds.width / 2;
        int rightY = node.right->room->bounds.y + node.right->room->bounds.height / 2;

        SDL_RenderDrawLine(renderer, leftX, leftY, rightX, rightY);
    }

    if (node.left) connectRooms(*node.left, renderer);
    if (node.right) connectRooms(*node.right, renderer);
}

void MapGenerator::renderMap(SDL_Renderer* renderer) {
    // Render rooms
    if (root.room) {
        SDL_Rect rect = { root.room->bounds.x, root.room->bounds.y, root.room->bounds.width, root.room->bounds.height };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    // Connect the rooms
    connectRooms(root, renderer);
}
