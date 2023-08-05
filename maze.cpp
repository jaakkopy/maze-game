#include <stack>
#include <algorithm>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "maze.hpp"

CellLabel::CellLabel(bool up, bool down, bool left, bool right)
{
    this->up = up;
    this->down = down;
    this->left = left;
    this->right = right;
}

bool CellLabel::is_visited()
{
    return up || down || left || right;
}

void CellLabel::mark_going(Direction going_to)
{
    switch (going_to)
    {
    case UP:
        up = true;
        break;
    case DOWN:
        down = true;
        break;
    case LEFT:
        left = true;
        break;
    case RIGHT:
        right = true;
        break;
    }
}

void CellLabel::mark_coming(Direction visitors_direction)
{
    // Visitor is going to certain direction, meaning the opposite direction's path is open from the perspective of the target cell
    switch (visitors_direction)
    {
    case UP:
        down = true;
        break;
    case DOWN:
        up = true;
        break;
    case LEFT:
        right = true;
        break;
    case RIGHT:
        left = true;
        break;
    }
}

Maze::Maze(int screen_w, int screen_h, int amount_cells_x, int amount_cells_y, unsigned int amount_collectibles)
{
    this->screen_w = screen_w;
    this->screen_h = screen_h;
    this->cells_x = amount_cells_x;
    this->cells_y = amount_cells_y;
    this->cell_w = screen_w / cells_x;
    this->cell_h = screen_h / cells_y;
    this->amount_collectibles = amount_collectibles;
}

typedef struct RC
{
    int r;
    int c;

    RC(int r, int c)
    {
        this->r = r;
        this->c = c;
    }

    bool operator==(RC const &rc)
    {
        return (r == rc.r) && (c == rc.c);
    }

} RC;

RC position_by_direction(const RC &rc, Direction dir)
{
    int r = 0;
    int c = 0;
    switch (dir)
    {
    case UP:
        r = -1;
        break;
    case DOWN:
        r = 1;
        break;
    case LEFT:
        c = -1;
        break;
    case RIGHT:
        c = 1;
        break;
    }
    return RC(rc.r + r, rc.c + c);
}

void Maze::init_maze()
{
    this->grid = std::make_unique<Grid<CellLabel>>(cells_x, cells_y);
    srand(time(NULL));
    std::stack<RC> path;
    RC start(cells_y - 1, cells_x / 2);                          // The starting position is the bottom middle cell
    std::vector<Direction> directions = {UP, DOWN, LEFT, RIGHT}; // used to randomly choose the path with shuffle
    path.push(start);
    while (!path.empty())
    {
        RC cur = path.top();
        path.pop();
        std::random_shuffle(directions.begin(), directions.end());
        for (auto d : directions)
        {
            const RC try_direction = position_by_direction(cur, d);
            if (!grid->is_in_bounds(try_direction.c, try_direction.r))
            {
                continue;
            }
            CellLabel &target = grid->at(try_direction.c, try_direction.r);
            if (target.is_visited())
            {
                continue;
            }
            CellLabel &current_label = grid->at(cur.c, cur.r);
            current_label.mark_going(d);
            target.mark_coming(d);
            path.push(try_direction);
        }
    }
    // Assign "collectables" to random cells.
    std::vector<RC> assigned_collectibles;
    while (assigned_collectibles.size() < amount_collectibles)
    {
        int random_c = rand() % (cells_x - 1);
        int random_r = rand() % (cells_y - 1);
        RC check(random_r, random_c);
        if (std::find(assigned_collectibles.begin(), assigned_collectibles.end(), check) == assigned_collectibles.end())
        {
            assigned_collectibles.push_back(check);
            CellLabel &random_spot = grid->at(random_c, random_r);
            random_spot.has_collectable = true;
        }
    }
    // Assign one exit cell on the top of the maze
    int random_c = rand() % (cells_x - 1);
    CellLabel &random_spot = grid->at(random_c, 0);
    random_spot.is_exit = true;
}

const CellLabel &Maze::get_grid_value_at(int r, int c) const
{
    return grid->at(c, r);
}

bool Maze::has_reached_exit(float x, float y) const
{
    int cell_col = x / cell_w;
    int cell_row = y / cell_h;
    if (!grid->is_in_bounds(cell_col, cell_row))
    {
        return false;
    }
    CellLabel &label = grid->at(cell_col, cell_row);
    return label.is_exit;
}

void Maze::remove_collectable(float x, float y)
{
    int cell_col = x / cell_w;
    int cell_row = y / cell_h;
    if (!grid->is_in_bounds(cell_col, cell_row))
    {
        return;
    }
    CellLabel &label = grid->at(cell_col, cell_row);
    label.has_collectable = false;
}

bool Maze::has_collected_collectable(float x, float y) const
{
    int cell_col = x / cell_w;
    int cell_row = y / cell_h;
    if (!grid->is_in_bounds(cell_col, cell_row))
    {
        return false;
    }
    const CellLabel &label = grid->at(cell_col, cell_row);
    if (!label.has_collectable)
    {
        return false;
    }
    return true;
}

bool Maze::has_hit_wall(float x, float y, float radius) const
{
    // get the cell corresponding to these coordinates
    int cell_col = x / cell_w;
    int cell_row = y / cell_h;
    if (!grid->is_in_bounds(cell_col, cell_row))
    {
        return true;
    }
    const CellLabel &label = grid->at(cell_col, cell_row);

    bool has_left_wall = !label.left;
    bool has_right_wall = !label.right;
    bool has_upper_wall = !label.up;
    bool has_lower_wall = !label.down;

    // check which wall of the cell the coordinates would correspond to, if any
    float cell_upper_y = (float)cell_row * cell_h;
    float cell_lower_y = (float)(cell_row + 1) * cell_h;
    float cell_left_x = (float)cell_col * cell_w;
    float cell_right_x = (float)(cell_col + 1) * cell_w;

    bool has_hit_left = (x - radius <= cell_left_x) && has_left_wall;
    bool has_hit_right = (x + radius >= cell_right_x) && has_right_wall;
    bool has_hit_lower = (y + radius >= cell_lower_y) && has_lower_wall;
    bool has_hit_upper = (y - radius <= cell_upper_y) && has_upper_wall;

    return has_hit_left || has_hit_right || has_hit_lower || has_hit_upper;
}