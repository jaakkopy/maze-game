#include <raylib.h>
#include <string.h>
#include <iostream>
#include <unordered_map>
#include "maze.hpp"
#include "player.hpp"
#include "draw.hpp"
#include <unistd.h>

int main(void)
{
    const int screen_w = 800;
    const int screen_h = 800;
    const int amount_cells_horizontal = 20;
    const int amount_cells_vertical = 20;
    const int amount_collectibles = 10;
    Maze maze(screen_w, screen_h, amount_cells_horizontal, amount_cells_vertical, amount_collectibles);
    Player player(3.0f, screen_w / 2, screen_h - 15, 12.0f);
    maze.init_maze();
    InitWindow(screen_w, screen_h, "maze");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        player.update_position(maze);
        const Vector2 &pos = player.get_position();
        if (maze.has_collected_collectable(pos.x, pos.y, player.get_radius()))
        {
            maze.mark_collected(pos.x, pos.y);
        }
        BeginDrawing();
        ClearBackground(WHITE);
        draw_maze(maze);
        draw_player(player);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}