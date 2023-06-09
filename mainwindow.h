#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QSet>
#include <memory>

#include "openglwindow.h"
#include "camera.h"
#include "wall.h"


class MainWindow final: public OpenGLWindow
{
    QOpenGLShaderProgram _program;
    Camera _camera;
    Wall _wall;

    std::shared_ptr<QOpenGLTexture> _texture;
    std::shared_ptr<QOpenGLTexture> _normTexture;

    QSet<int> _pressedKeys;
    QPoint _mousePos;

    void MoveCameraOnKey() noexcept;
public:
    MainWindow(QWidget* parent = nullptr);

    void initialize() override;
    void render() override;

    void keyPressEvent(QKeyEvent* key) override;
    void keyReleaseEvent(QKeyEvent* key) override;

    void mouseMoveEvent(QMouseEvent* mouse) override;
};
#endif // OPENGLWIDGET_H
