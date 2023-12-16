#ifndef NODE_H
#define NODE_H

#include <vector>
#include <memory>

class Node final
{
    //TO DO: improve
    size_t _x = 0;
    size_t _y = 0;
    bool _visited = false;
    std::vector<std::shared_ptr<Node>> _neighbours;
public:
    Node() noexcept = default;
    Node(size_t x, size_t y) noexcept;

    inline void AddNeighbour(std::shared_ptr<Node> node) noexcept
    {
        _neighbours.push_back(node);
    }

    inline std::vector<std::shared_ptr<Node>>::const_iterator NeighboursBegin() const noexcept
    {
        return _neighbours.begin();
    }
    inline std::vector<std::shared_ptr<Node>>::const_iterator NeighboursEnd() const noexcept
    {
        return _neighbours.end();
    }

    inline void SetVisit(bool value) noexcept
    {
        _visited = value;
    }
    inline bool IsVisit() const noexcept
    {
        return _visited;
    }

    bool operator==(const Node& node) const noexcept;

    size_t GetX() const noexcept;
    size_t GetY() const noexcept;
};

#endif // NODE_H
