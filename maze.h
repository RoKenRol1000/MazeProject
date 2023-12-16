#ifndef MAZE_H
#define MAZE_H

#include "Node.h"

class Maze final
{
    size_t _width;
    size_t _height;
    size_t _startX;
    size_t _startY;
    std::vector<std::shared_ptr<Node>> _maze;

    std::shared_ptr<Node> GetNode(size_t x, size_t y);
    void InitMaze();
public:
    Maze(size_t width, size_t height, size_t startX, size_t startY);
    void generete();

    inline std::shared_ptr<Node> GetRoot()
    {
        return GetNode(_startX, _startY);
    }
    inline void RemoveVisit()
    {
        for (auto& i: _maze)
        {
            (*i).SetVisit(false);
        }
    }
    inline std::vector<std::shared_ptr<Node>>::const_iterator MazeBegin() const noexcept
    {
        return _maze.begin();
    }
    inline std::vector<std::shared_ptr<Node>>::const_iterator MazeEnd() const noexcept
    {
        return _maze.end();
    }
};

#endif // MAZE_H
