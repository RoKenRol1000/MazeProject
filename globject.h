#ifndef GLOBJECT_H
#define GLOBJECT_H

#include <QVector3D>
#include <vector>

class QOpenGLShaderProgram;

struct Vertex
{
    QVector3D posAttr;
    QVector3D norm;
    QVector2D uvMap;
};

class GLObject
{
public:
    virtual ~GLObject() noexcept = default;
    GLObject() noexcept = default;
    GLObject(const GLObject&) noexcept = default;
    GLObject(GLObject&&) noexcept = default;

    GLObject& operator=(const GLObject&) noexcept = default;
    GLObject& operator=(GLObject&&) noexcept = default;

    virtual std::vector<Vertex> Generate() = 0;
};

#endif // GLOBJECT_H
