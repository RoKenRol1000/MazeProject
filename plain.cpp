#include "plain.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

std::vector<Vertex> Plain::Generate()
{
    std::vector<Vertex> result;
    QVector3D pos;
    const QVector3D norm {0.f, 0.f, -1.f};
    QVector2D uvMap;

    for (size_t size = 0; size < 4; ++size)
    {
        pos = {_startX + _width * (size %2), _startY + _height * (size / 2), _startZ};
        uvMap = {1.f * static_cast<int>(_width) * (size%2), 1.f * static_cast<int>(_height) *(size/2)};
        result.emplace_back(pos, norm, uvMap);
    }
    return result;
}
