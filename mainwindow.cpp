#include "mainwindow.h"
#include <iostream>
#include <QDir>

MainWindow::MainWindow(QWidget* parent)
{}

void MainWindow::initialize()
{
    initializeOpenGLFunctions();
    _program.addShaderFromSourceFile(QOpenGLShader::Vertex, QDir::currentPath() + "/Shaders/vertex.vsh");
    _program.addShaderFromSourceFile(QOpenGLShader::Fragment, QDir::currentPath() + "/Shaders/fragment.fsh");
    _program.link();
    _texture = std::make_shared<QOpenGLTexture>(QImage{QDir::currentPath() + "/Resources/brick.jpg"});
    _normTexture = std::make_shared<QOpenGLTexture>(QImage{QDir::currentPath() + "/Resources/brick-normal.jpg"});

    //
}

void MainWindow::render()
{
    MoveCameraOnKey();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LESS);
    //glDepthRangef(GLfloat(0.0), GLfloat(50.0));

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    _program.bind();

    auto view = _camera.GetViewMatrix();
    _program.setUniformValue("view", view);
    _program.setUniformValue("camPos", _camera.GetPos());
    _program.setUniformValue("rotateMatrix", QMatrix4x4{});
    _program.setUniformValue("translation", QMatrix4x4{});

    const float vertex[] {-1.f, 1.f, -3.f,
                    -1.f, -1.f, -3.f,
                    1.f, 1.f, -3.f,

                    1.f, 1.f, -3.f,
                    -1.f, -1.f, -3.f,
                   1.f, -1.f, -3.f};
    const float uvMap[] {0.f, 2.f,
                   0.f, 0.f,
                   2.f, 2.f,

                   2.f, 2.f,
                   0.f, 0.f,
                   2.f, 0.f};
    const float norm[] {0.f, 0.f, 1.f,
                        0.f, 0.f, 1.f,
                        0.f, 0.f, 1.f,

                        0.f, 0.f, 1.f,
                        0.f, 0.f, 1.f,
                        0.f, 0.f, 1.f};

    GLint posAttr = _program.attributeLocation("posAttr");
    GLint texCord = _program.attributeLocation("texCord");
    //GLint normAttr = program.attributeLocation("norm");

    glActiveTexture(GL_TEXTURE0 + 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    _texture->bind();

    //glActiveTexture(GL_TEXTURE0 + 1);
    //_normTexture->bind();

    _program.setUniformValue("texture",0);
    //_program.setUniformValue("textureNormalMap", 1);


    glVertexAttribPointer(posAttr, 3, GL_FLOAT, GL_FALSE, 0, vertex);
    glVertexAttribPointer(texCord, 2, GL_FLOAT, GL_FALSE, 0, uvMap);
    //glVertexAttribPointer(normAttr, 3, GL_FLOAT, GL_FALSE, 0, norm);

    glEnableVertexAttribArray(posAttr);
    glEnableVertexAttribArray(texCord);
    //glEnableVertexAttribArray(normAttr);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(posAttr);
    glDisableVertexAttribArray(texCord);
    //glDisableVertexAttribArray(normAttr);

    _program.release();
}

void MainWindow::MoveCameraOnKey() noexcept
{
    if (_pressedKeys.contains(Qt::Key_W))
    {
        _camera.MoveForward(1);
    }
    if (_pressedKeys.contains(Qt::Key_S))
    {
        _camera.MoveForward(-1);
    }
    if (_pressedKeys.contains(Qt::Key_A))
    {
        _camera.MoveSideway(-1);
    }
    if (_pressedKeys.contains(Qt::Key_D))
    {
        _camera.MoveSideway(1);
    }
}

void MainWindow::keyPressEvent(QKeyEvent* key)
{
    _pressedKeys += key->key();
}

void MainWindow::keyReleaseEvent(QKeyEvent* key)
{
    _pressedKeys -= key->key();
}

void MainWindow::mouseMoveEvent(QMouseEvent* mouse)
{
    if (_mousePos != QPoint())
    {
        _camera.SetYawAngle(_camera.GetYawAngle() + 0.5f * (mouse->pos().x() - _mousePos.x()));
        _camera.SetPitchAngle(_camera.GetPitchAngle() + 0.5f  * (-mouse->pos().y() + _mousePos.y()));
    }
    QPoint glob = mapToGlobal(QPoint(width()/2,height()/2));
    QCursor::setPos(glob);
    this->setCursor(QCursor{Qt::BlankCursor});
    _mousePos = QPoint(width()/2,height()/2);
}
