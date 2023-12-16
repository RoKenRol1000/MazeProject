#ifndef PARALLELEPIPED_H
#define PARALLELEPIPED_H

#include "globject.h"

class Parallelepiped final: public GLObject
{
    float _width = 1.0;
    float _height = 1.0;
    float _startX = 0;
    float _startY = 0;
    float _startZ = 0;

    std::vector<Vertex> GenerateFacet(float width, float height) const noexcept;
    void RotateFacet(std::vector<Vertex>::iterator facetBegin, std::vector<Vertex>::iterator facetEnd, QVector3D axis, float angle) const noexcept;
public:
    ~Parallelepiped() noexcept override = default;
    Parallelepiped() noexcept = default;
    inline Parallelepiped(float width = 1.0, float height = 1.0, float startX = 0, float startY = 0, float startZ = 0):
        _width(width), _height(height), _startX(startX), _startY(startY), _startZ(startZ)
    {}
    Parallelepiped(const Parallelepiped&) noexcept = default;
    Parallelepiped(Parallelepiped&&) noexcept = default;

    Parallelepiped& operator=(const Parallelepiped&) noexcept = default;
    Parallelepiped& operator=(Parallelepiped&&) noexcept = default;

    std::vector<Vertex> Generate() override;
};

#endif // PARALLELEPIPED_H
