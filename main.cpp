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
    Maze maze(screen_w, screen_h, amount_cells_horizontal, amount_cells_vertical);
    Player player(3.0f, screen_w / 2, screen_h - 15);
    maze.init_maze();
    InitWindow(screen_w, screen_h, "maze");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        player.update(maze);
        BeginDrawing();
        ClearBackground(WHITE);
        draw_maze(maze);
        draw_player(player);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}