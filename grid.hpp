#ifndef GRID_HPP
#define GRID_HPP

#include <vector>

template <typename T>
class Grid
{
public:
    Grid(int cols, int rows);
    T &at(int c, int r);
    bool is_in_bounds(int c, int r) const;

private:
    int cols;
    int rows;
    std::vector<T> cells;
};

template <typename T>
inline Grid<T>::Grid(int cols, int rows)
{
    this->cols = cols;
    this->rows = rows;
    this->cells = std::vector<T>(cols * rows, T());
}

template <typename T>
T &Grid<T>::at(int c, int r)
{
    return this->cells.at(r * cols + c);
}

template <typename T>
inline bool Grid<T>::is_in_bounds(int c, int r) const
{
    return (c >= 0 && c < cols) && (r >= 0 && r < rows);
}

#endif
