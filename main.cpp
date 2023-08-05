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
    const int amount_collectables = 10;
    int collected = 0;
    Maze maze(screen_w, screen_h, amount_cells_horizontal, amount_cells_vertical, amount_collectables);
    Player player(3.0f, screen_w / 2, screen_h - 15, 12.0f);
    maze.init_maze();
    const float status_text_x = maze.get_cell_width()/2;
    const float status_text_y = maze.get_cell_height()/2;
    const int font_size = 20;
    InitWindow(screen_w, screen_h, "maze");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        player.update_position(maze);
        const Vector2 &pos = player.get_position();
        if (maze.has_collected_collectable(pos.x, pos.y))
        {
            maze.remove_collectable(pos.x, pos.y);
            ++collected;
        }
        if (maze.has_reached_exit(pos.x, pos.y))
        {
            maze = Maze(screen_w, screen_h, amount_cells_horizontal, amount_cells_vertical, amount_collectables);
            maze.init_maze();
            player = Player(3.0f, screen_w / 2, screen_h - 15, 12.0f);
            collected = 0;
        }
        BeginDrawing();
        ClearBackground(WHITE);
        draw_maze(maze);
        draw_player(player);
        DrawText(TextFormat("Collected %i/%i", collected, amount_collectables), status_text_x, status_text_y, font_size, GREEN);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}