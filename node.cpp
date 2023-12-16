#include "node.h"


Node::Node(size_t x, size_t y) noexcept: _x(x), _y(y)
{}



bool Node::operator==(const Node& node) const noexcept
{
    return _x == node._x && _y == node._y;
}

size_t Node::GetX() const noexcept
{
    return _x;
}
size_t Node::GetY() const noexcept
{
    return _y;
}
