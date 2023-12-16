#include "maze.h"

#include <stdexcept>
#include <stack>
#include <random>
#include <iostream>
#include <QDebug>
#include <fstream>
#include <queue>


void Maze::InitMaze()
{
   for (size_t y = 0; y < _height; ++y)
   {
       for (size_t x = 0; x < _width; ++x)
       {
            _maze.push_back(std::make_shared<Node>(Node{x, y}));
       }
   }
}

std::shared_ptr<Node> Maze::GetNode(size_t x, size_t y)
{
    return _maze[y * _width + x];
}

Maze::Maze(size_t width, size_t height, size_t startX, size_t startY):_width(width), _height(height), _startX(startX), _startY(startY)
{
    if (startX >= width || startY >= height)
    {
        throw std::invalid_argument("Start coordinates should be less than size of maze");
    }
    InitMaze();
}

void Maze::generete()
{
    std::random_device rd;
    std::mt19937 random{rd()};

    std::stack<std::shared_ptr<Node>> nodes;
    nodes.push(GetNode(_startX, _startY));

    while (!nodes.empty())
    {
        auto node = nodes.top();
        nodes.pop();
        node->SetVisit(true);
        int x = static_cast<int>(node->GetX()), y = static_cast<int>(node->GetY());
        std::vector<std::shared_ptr<Node>> unvisited;
        if (x + 1 < _width && !GetNode(x + 1, y)->IsVisit())
        {
            unvisited.push_back(GetNode(x + 1, y));
        }
        if (x - 1 >= 0 && !GetNode(x - 1, y)->IsVisit())
        {
            unvisited.push_back(GetNode(x - 1, y));
        }
        if (y + 1 < _height && !GetNode(x, y + 1)->IsVisit())
        {
            unvisited.push_back(GetNode(x, y + 1));
        }
        if (y - 1 >= 0 && !GetNode(x, y - 1)->IsVisit())
        {
            unvisited.push_back(GetNode(x, y - 1));
        }
        if (unvisited.empty())
        {
            continue;
        }
        auto nextNode = unvisited[random() % unvisited.size()];
        node->AddNeighbour(nextNode);
        nextNode->AddNeighbour(node);
        nodes.push(node);
        nodes.push(nextNode);
    }
    RemoveVisit();
    std::vector<std::string> str;
    std::ofstream f("./maze.txt");
    for (int j = 0; j <  3 * _height; ++j)
    {
        str.emplace_back();
        for (int i = 0; i < _width; ++i)
        {
            if (j%3 != 1)
            {
                str[j]+="###";
                continue;
            }
            str[j]+="# #";
        }
    }
    for (size_t y = 0; y < _height; ++y)
    {

        for (size_t x = 0; x < _width; ++x)
        {
            auto node = GetNode(x, y);
            int checkSum = 0;
            for (auto i = node->NeighboursBegin(); i != node->NeighboursEnd(); ++i)
            {
                int dx = static_cast<int>((*i)->GetX()) - x;
                int dy = static_cast<int>((*i)->GetY()) - y;
                if (dx > 0)
                {
                    checkSum += 1;
                }
                if (dx < 0)
                {
                    checkSum += 2;
                }
                if (dy > 0)
                {
                    checkSum += 4;
                }
                if (dy < 0)
                {
                    checkSum += 8;
                }
                str[(3 * y + 1 + dy)][3 * x + 1 + dx] = ' ';
            }
        }
    }
    for (auto& item: str)
    {
        f<<item<<std::endl;
    }
}
