#include "player.hpp"

Player::Player(float velocity, float start_x, float start_y, float radius)
{
    this->velocity = velocity;
    this->radius = radius;
    this->position = (Vector2){start_x, start_y};
}

void Player::check_position(const Maze &maze, Vector2 original_position)
{
    if (maze.has_hit_wall(position.x, position.y, radius))
    {
        position = original_position;
    }
}

void Player::update_position(const Maze &maze)
{
    if (IsKeyDown(KEY_RIGHT))
    {
        Vector2 original = position;
        position.x += velocity;
        check_position(maze, original);
    }
    if (IsKeyDown(KEY_LEFT))
    {
        Vector2 original = position;
        position.x -= velocity;
        check_position(maze, original);
    }
    if (IsKeyDown(KEY_UP))
    {
        Vector2 original = position;
        position.y -= velocity;
        check_position(maze, original);
    }
    if (IsKeyDown(KEY_DOWN))
    {
        Vector2 original = position;
        position.y += velocity;
        check_position(maze, original);
    }
}

Vector2 Player::get_position() const
{
    return position;
}

float Player::get_radius() const
{
    return radius;
}