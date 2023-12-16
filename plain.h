#ifndef PLAIN_H
#define PLAIN_H

#include "globject.h"
#include <QOpenGLTexture>
#include <QDir>
#include <QImage>
#include <memory>

class Plain final: public GLObject
{
    inline static const std::vector<int> indices {0, 1 ,2 , 1, 3, 2};
    float _width = 1.0;
    float _height = 1.0;
    float _startX = 0;
    float _startY = 0;
    float _startZ = 0;
public:
    ~Plain() noexcept override = default;
    Plain() noexcept = default;
    inline Plain(float width = 1.0, float height = 1.0, float startX = 0, float startY = 0, float startZ = 0):
        _width(width), _height(height), _startX(startX), _startY(startY), _startZ(startZ)
    {}
    Plain(const Plain&) noexcept = default;
    Plain(Plain&&) noexcept = default;

    Plain& operator=(const Plain&) noexcept = default;
    Plain& operator=(Plain&&) noexcept = default;

    std::vector<Vertex> Generate() override;
    inline static const std::vector<int>& GetIndices() noexcept
    {
        return indices;
    }
};

#endif
