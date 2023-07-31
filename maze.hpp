#ifndef MAZE_HPP
#define MAZE_HPP

#include <memory>
#include "grid.hpp"

typedef enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

// Indicates which directions are open from this cell 
typedef struct VisitationLabel
{
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    VisitationLabel(bool up = false, bool down = false, bool left = false, bool right = false);
    bool is_visited();
    void mark_coming(Direction visitors_direction);
    void mark_going(Direction going_to);
} VisitationLabel;


class Maze
{
public:
    Maze(int screen_w, int screen_h, int amount_cells_x, int amount_cells_y);
    void init_maze();
    int get_cells_x() const { return cells_x; };
    int get_cells_y() const { return cells_y; };
    int get_cell_width() const { return cell_w; };
    int get_cell_height() const { return cell_h; };
    const VisitationLabel &get_grid_value_at(int r, int c) const;
    bool has_hit_wall(float x, float y, float radius) const;
private:
    std::unique_ptr<Grid<VisitationLabel>> grid;
    bool in_bounds(int c, int r) const;
    int screen_w;
    int screen_h;
    int cells_x;
    int cells_y;
    int cell_w;
    int cell_h;
};

#endif