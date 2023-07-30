#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>

class Player {
public:
    Player(float velocity, float start_x, float start_y);
    void update();
    Vector2 get_position() const;
private:
    float velocity;
    Vector2 position;
};

#endif