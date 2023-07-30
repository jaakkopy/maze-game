#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>
#include "maze.hpp"

class Player {
public:
    Player(float velocity, float start_x, float start_y);
    void update(const Maze &maze);
    Vector2 get_position() const;
private:
    float velocity;
    Vector2 position;
};

#endif