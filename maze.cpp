#include <stack>
#include <algorithm>
#include <vector>
#include <time.h>
#include <stdlib.h>
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

void VisitationLabel::mark_coming(Direction visitor_came_from)
{
    switch (visitor_came_from)
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
    grid->at(cells_y - 1, cells_x / 2).down = true;
    std::vector<Direction> directions = {UP, DOWN, LEFT, RIGHT}; // used to randomly choose the path with shuffle
    path.push(start);
    while (!path.empty())
    {
        RC cur = path.top();
        path.pop();
        std::random_shuffle(directions.begin(), directions.end());
        for (auto d : directions)
        {
            RC try_direction = position_by_direction(cur, d);
            if (!in_bounds(try_direction.c, try_direction.r))
            {
                continue;
            }
            VisitationLabel &target = grid->at(try_direction.r, try_direction.c);
            if (target.is_visited())
            {
                continue;
            }
            grid->at(cur.r, cur.c).mark_going(d);
            target.mark_coming(d);
            path.push(try_direction);
        }
    }
}

VisitationLabel Maze::get_grid_value_at(int r, int c) const
{
    return grid->at(c, r);
}

bool Maze::in_bounds(int c, int r)
{
    return (c >= 0 && c < cells_x) && (r >= 0 && r < cells_y);
}
