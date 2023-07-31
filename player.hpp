#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>
#include "maze.hpp"

class Player {
public:
    Player(float velocity, float start_x, float start_y, float radius);
    void update(const Maze &maze);
    Vector2 get_position() const;
    float get_radius() const;
private:
    float radius;
    float velocity;
    Vector2 position;
};

#endif