#include "draw.hpp"

void draw_maze(const Maze &maze)
{
    int cells_x = maze.get_cells_x();
    int cells_y = maze.get_cells_y();
    int cell_width = maze.get_cell_width();
    int cell_height = maze.get_cell_height();
    // Draw black grid lines to separate the window into cells
    Vector2 start = (Vector2){0, 0};
    Vector2 end = (Vector2){(float)cells_x * cell_width, 0};
    for (int r = 0; r < cells_y; ++r)
    {
        start.y = r * cell_height;
        end.y = start.y;
        DrawLineV(start, end, BLACK);
    }
    start.y = 0;
    end.y = cells_y * cell_height;
    for (int c = 0; c < maze.get_cells_x(); ++c)
    {
        start.x = c * cell_height;
        end.x = c * cell_height;
        DrawLineV(start, end, BLACK);
    }
    // Draw the path
    for (int r = 0; r < cells_y; ++r)
    {
        for (int c = 0; c < cells_x; ++c)
        {
            Vector2 upper_left   = (Vector2){(float) c      * cell_width, (float) r      * cell_height};
            Vector2 upper_right  = (Vector2){(float)(c + 1) * cell_width, (float) r      * cell_height};
            Vector2 bottom_left  = (Vector2){(float) c      * cell_width, (float)(r + 1) * cell_height};
            Vector2 bottom_right = (Vector2){(float)(c + 1) * cell_width, (float)(r + 1) * cell_height};
            const VisitationLabel &v = maze.get_grid_value_at(r, c);
            if (v.up)
            {
                DrawLineV(upper_left, upper_right, WHITE);
            }
            if (v.down)
            {
                DrawLineV(bottom_left, bottom_right, WHITE);
            }
            if (v.left)
            {
                DrawLineV(upper_left, bottom_left, WHITE);
            }
            if (v.right)
            {
                DrawLineV(upper_right, bottom_right, WHITE);
            }
        }
    }
}

void draw_player(const Player &player) {
    DrawCircleV(player.get_position(), player.get_radius(), BLUE);
}