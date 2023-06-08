#ifndef GLOBJECT_H
#define GLOBJECT_H

class QOpenGLShaderProgram;

class GLObject
{
public:
    virtual ~GLObject() noexcept = default;
    GLObject() noexcept = default;
    GLObject(const GLObject&) noexcept = default;
    GLObject(GLObject&&) noexcept = default;

    GLObject& operator=(const GLObject&) noexcept = default;
    GLObject& operator=(GLObject&&) noexcept = default;

    virtual void Render(const QOpenGLShaderProgram&) = 0;
};

#endif // GLOBJECT_H
