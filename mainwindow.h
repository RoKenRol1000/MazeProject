#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QSet>
#include <memory>
#include <chrono>

#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QtMultimedia/QAudioDevice>>

#include "openglwindow.h"
#include "camera.h"
#include "plain.h"
#include "maze.h"



class MainWindow final: public OpenGLWindow
{
    QMediaPlayer _player;
    QAudioOutput _walkAudio;
    QAudioDevice _audioOutput;
    QOpenGLShaderProgram _program;
    GLint posAttr;
    GLint texCord;
    GLint normAttr;

    size_t _mazeWidth = 100;
    size_t _mazeHeight = 100;

    Camera _camera;//{QVector3D{-0.5f, 0.f, -0.5f}};
    std::vector<Vertex> _wallVertices;
    std::vector<Vertex> _floorVertices;
    std::vector<Vertex> _balkVertices;
    Maze _maze {_mazeWidth, _mazeHeight, 0, 0};

    std::chrono::time_point<std::chrono::system_clock> _timePoint = std::chrono::system_clock::now();

    std::shared_ptr<QOpenGLTexture> _wallTexture;
    std::shared_ptr<QOpenGLTexture> _wallNormTexture;
    std::shared_ptr<QOpenGLTexture> _balkTexture;
    std::shared_ptr<QOpenGLTexture> _balkNormTexture;
    std::shared_ptr<QOpenGLTexture> _floorTexture;
    std::shared_ptr<QOpenGLTexture> _floorNormTexture;

    QSet<uint32_t> _pressedKeys;
    QPoint _mousePos;

    void MoveCameraOnKey(float step) noexcept;
    void InitGame() noexcept;
public:
    MainWindow(QWidget* parent = nullptr);

    void initialize() override;
    void render() override;

    void keyPressEvent(QKeyEvent* key) override;
    void keyReleaseEvent(QKeyEvent* key) override;

    void mouseMoveEvent(QMouseEvent* mouse) override;
};
#endif // OPENGLWIDGET_H
