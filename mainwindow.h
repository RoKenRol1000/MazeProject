#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include "openglwindow.h"

class MainWindow final: public OpenGLWindow
{
    QOpenGLShaderProgram m_program;

public:
    MainWindow(QWidget* parent = nullptr);

    void initialize() override;
    void render() override;
};
#endif // OPENGLWIDGET_H
