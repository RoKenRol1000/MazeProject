#include "parallelepiped.h"
#include "qmatrix4x4.h"
#include <QMatrix4x4>

std::vector<Vertex> Parallelepiped::GenerateFacet(float width, float height) const noexcept
{
    std::vector<Vertex> result;
    float step_x = width;
    float step_y = height;
    QVector3D norm {0.f, 0.f, -1.f};
    std::vector<QVector3D> square {{_startX, _startY, _startZ},
                {_startX + step_x, _startY, _startZ},
                {_startX + step_x, _startY + step_y, _startZ},

                {_startX + step_x, _startY + step_y, _startZ},
                {_startX, _startY + step_y, _startZ},
                {_startX, _startY, _startZ}};
    std::vector<QVector2D> uvMap {{0, 0}, {width, 0}, {width, height}, {width, height}, {0, height}, {0, 0}};
    for (int i = 0; i < square.size(); ++i)
    {
        result.emplace_back(square[i], norm, uvMap[i]);
    }
    return result;
}
void Parallelepiped::RotateFacet(std::vector<Vertex>::iterator facetBegin, std::vector<Vertex>::iterator facetEnd, QVector3D axis, float angle) const noexcept
{
    QMatrix4x4 matrix;
    matrix.rotate(angle, axis);
    for (auto item = facetBegin; item != facetEnd; ++item)
    {
        (*item).norm = matrix.map((*item).norm);
        (*item).posAttr = matrix.map((*item).posAttr);
    }
}

std::vector<Vertex> Parallelepiped::Generate()
{
    std::vector<Vertex> result;
    auto sideVertices = GenerateFacet(_width, _height);
    auto upVertices = GenerateFacet(_width, _width);

    for (int i =0 ; i < 6; i++)
    {
        if (i < 4){
            result.insert(result.end(), sideVertices.begin(), sideVertices.end());
            RotateFacet(result.begin() + i * sideVertices.size(), result.end(), {0, 1, 0}, 90 * i);
        }else{
            //result.insert(result.end(), upVertices.begin(), upVertices.end());
            //RotateFacet(result.begin() + i * upVertices.size(), result.end(), {1, 0, 0}, 90 * std::pow(-1, i%2));
        }

    }
    return result;
}
