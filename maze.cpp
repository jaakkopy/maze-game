#include <stack>
#include <algorithm>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "maze.hpp"

VisitationLabel::VisitationLabel(bool up, bool down, bool left, bool right)
{
    this->up = up;
    this->down = down;
    this->left = left;
    this->right = right;
}

bool VisitationLabel::is_visited()
{
    return up || down || left || right;
}

void VisitationLabel::mark_going(Direction going_to)
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

void VisitationLabel::mark_coming(Direction visitors_direction)
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

Maze::Maze(int screen_w, int screen_h, int amount_cells_x, int amount_cells_y)
{
    this->screen_w = screen_w;
    this->screen_h = screen_h;
    this->cells_x = amount_cells_x;
    this->cells_y = amount_cells_y;
    this->cell_w = screen_w / cells_x;
    this->cell_h = screen_h / cells_y;
    this->grid = std::make_unique<Grid<VisitationLabel>>(cells_x, cells_y);
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

} RC;

RC position_by_direction(const RC &rc, Direction dir)
{
    int r = 0;
    int c = 0;
    switch (dir)
    {
    case UP:
        r = 1;
        break;
    case DOWN:
        r = -1;
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
    srand(time(NULL));
    std::stack<RC> path;
    RC start(cells_y - 1, cells_x / 2); // The starting position is the bottom middle cell
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
            if (!in_bounds(try_direction.c, try_direction.r))
            {
                continue;
            }
            VisitationLabel &target = grid->at(try_direction.c, try_direction.r);
            if (target.is_visited())
            {
                continue;
            }
            grid->at(cur.c, cur.r).mark_going(d);
            target.mark_coming(d);
            path.push(try_direction);
        }
    }
}

const VisitationLabel &Maze::get_grid_value_at(int r, int c) const
{
    return grid->at(c, r);
}


// TODO: miksei toimi?? Ei taida tunnistaa polkua oikein...
bool Maze::has_hit_wall(float x, float y) const
{
    // get the cell corresponding to these coordinates    
    int cell_col = x / cell_w;
    int cell_row = y / cell_h;
    if (!in_bounds(cell_col, cell_row)) {
        return true;
    }
    const VisitationLabel &label = grid->at(cell_col, cell_row); 

    bool has_left_wall  = !label.left;
    bool has_right_wall = !label.right;
    bool has_upper_wall = !label.up;
    bool has_lower_wall = !label.down;

    std::cout << "(" << cell_col << ", " << cell_row << ")" << ", HAS WALL UP: " << has_upper_wall << " HAS WALL DOWN: " << has_lower_wall << " HAS WALL LEFT: " << has_left_wall << " HAS WALL RIGHT: " << has_right_wall << std::endl;

    // check which wall of the cell the coordinates would correspond to, if any
    float cell_upper_y = (float)cell_row * cell_h;
    float cell_lower_y = (float)(cell_row + 1) * cell_h;
    float cell_left_x  = (float)cell_col * cell_w;
    float cell_right_x = (float)(cell_col + 1) * cell_w;

    bool has_hit_left  = (x <= cell_left_x)  && has_left_wall;
    bool has_hit_right = (x >= cell_right_x) && has_right_wall;
    bool has_hit_lower = (y >= cell_lower_y) && has_lower_wall;
    bool has_hit_upper = (y <= cell_upper_y) && has_upper_wall;

    return has_hit_left || has_hit_right || has_hit_lower || has_hit_upper;
}

bool Maze::in_bounds(int c, int r) const
{
    return (c >= 0 && c < cells_x) && (r >= 0 && r < cells_y);
}