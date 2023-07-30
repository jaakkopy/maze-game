#include "player.hpp"

Player::Player(float velocity, float start_x, float start_y)
{
    this->velocity = velocity;
    this->position = (Vector2){start_x, start_y};
}

void Player::update()
{
    if (IsKeyDown(KEY_RIGHT)) position.x += velocity;
    if (IsKeyDown(KEY_LEFT))  position.x -= velocity;
    if (IsKeyDown(KEY_UP))    position.y -= velocity;
    if (IsKeyDown(KEY_DOWN))  position.y += velocity;
}

Vector2 Player::get_position() const
{
    return position; 
}
