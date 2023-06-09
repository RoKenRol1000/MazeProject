#ifndef WALL_H
#define WALL_H

#include "globject.h"
#include <QOpenGLTexture>
#include <QDir>
#include <QImage>

class Wall final: public GLObject
{
    QOpenGLTexture* _texture;
    QOpenGLTexture* _normTexture;
public:
    ~Wall() noexcept override;
    Wall() noexcept;
    Wall(const Wall&) noexcept = default;
    Wall(Wall&&) noexcept = default;

    Wall& operator=(const Wall&) noexcept = default;
    Wall& operator=(Wall&&) noexcept = default;

    void Render(QOpenGLShaderProgram& program) override;
};

#endif // WALL_H
