#include "wall.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

Wall::Wall() noexcept
{
    //TO DO: Use shared_ptr
    //_texture = new QOpenGLTexture(QImage{QDir::currentPath() + "Resources/wall.jpg"});
    //_normTexture = new QOpenGLTexture(QImage{QDir::currentPath() + "Resources/wall-norm.jpg"});
}

Wall::~Wall() noexcept
{
    //delete _texture;
    //delete _normTexture;
}

void Wall::Render(QOpenGLShaderProgram& program)
{

}
