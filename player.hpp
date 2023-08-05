#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>
#include "maze.hpp"

class Player
{
public:
    Player(float velocity, float start_x, float start_y, float radius);
    void update_position(const Maze &maze);
    Vector2 get_position() const;
    float get_radius() const;

private:
    void check_position(const Maze &maze, Vector2 original_position);
    float radius;
    float velocity;
    Vector2 position;
};

#endif