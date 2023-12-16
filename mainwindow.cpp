#include "mainwindow.h"
#include <iostream>
#include <QDir>
#include <stack>
#include "parallelepiped.h"


MainWindow::MainWindow(QWidget* parent)
{}

void MainWindow::initialize()
{
    _maze.generete();
    _wallVertices = Plain(2.f, 2.f, -1, -1).Generate();
    _floorVertices = Plain(2.2f, 2.2f, -1.1, -1.1f, 0).Generate();
    _balkVertices = Parallelepiped(0.2, 2, -0.1, -1, -0.1).Generate();
    initializeOpenGLFunctions();
    _program.addShaderFromSourceFile(QOpenGLShader::Vertex, QDir::currentPath() + "/Shaders/vertex.vsh");
    _program.addShaderFromSourceFile(QOpenGLShader::Fragment, QDir::currentPath() + "/Shaders/fragment.fsh");
    _program.link();
    _wallTexture = std::make_shared<QOpenGLTexture>(QImage{QDir::currentPath() + "/Resources/brick.jpg"});
    _wallNormTexture = std::make_shared<QOpenGLTexture>(QImage{QDir::currentPath() + "/Resources/brick-normal.jpg"});
    _balkTexture = std::make_shared<QOpenGLTexture>(QImage{QDir::currentPath() + "/Resources/wood.jpg"});
    _balkNormTexture = std::make_shared<QOpenGLTexture>(QImage{QDir::currentPath() + "/Resources/wood-normal.jpg"});
    _floorTexture = std::make_shared<QOpenGLTexture>(QImage{QDir::currentPath() + "/Resources/planks.jpg"});
    _floorNormTexture = std::make_shared<QOpenGLTexture>(QImage{QDir::currentPath() + "/Resources/planks-normal.jpg"});

    _timePoint = std::chrono::system_clock::now();
    posAttr = _program.attributeLocation("posAttr");
    texCord = _program.attributeLocation("texCord");
    normAttr = _program.attributeLocation("norm");

    glActiveTexture(GL_TEXTURE0 + 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    _wallTexture->bind();

    glActiveTexture(GL_TEXTURE0 + 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    _wallNormTexture->bind();

    glActiveTexture(GL_TEXTURE0 + 2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    _balkTexture->bind();

    glActiveTexture(GL_TEXTURE0 + 3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    _balkNormTexture->bind();

    glActiveTexture(GL_TEXTURE0 + 4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    _floorTexture->bind();

    glActiveTexture(GL_TEXTURE0 + 5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    _floorNormTexture->bind();
}

void MainWindow::render()
{
    auto currentFrame = std::chrono::system_clock::now();
    auto diffTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentFrame - _timePoint);
    _timePoint = currentFrame;

    MoveCameraOnKey(static_cast<float>(diffTime.count())/1000);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    _program.bind();

    auto view = _camera.GetViewMatrix();
    QMatrix4x4 projection;
    projection.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);

    _program.setUniformValue("projection", projection);
    _program.setUniformValue("view", view);
    _program.setUniformValue("camPos", _camera.GetPos());

    _program.setUniformValue("pointLightAtt", QVector3D(1.0f, .7f, 0.3f));
    _program.setUniformValue("pointLightPos", _camera.GetPos() + _camera.GetFrontVector() * 0.2 + _camera.GetRightVector() * 0.2);
    _program.setUniformValue("pointLightDiffColor", QVector4D(.62f,0.5f,0.36f,1.f));
    _program.setUniformValue("pointLightSpecColor", QVector4D(0.3f,0.3f,0.3f,1.f));
    _program.setUniformValue("globalAmbient", QVector4D(1.f,1.f,1.f,1.f));
    _program.setUniformValue("ambientIntesity", 0.01f);

    //WALL generation

    _program.setUniformValue("texture",0);
    _program.setUniformValue("textureNormalMap", 1);
    _program.setUniformValue("specularReflection", 1000.f);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*_wallVertices.size(), _wallVertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(posAttr, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, posAttr));
    glVertexAttribPointer(texCord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uvMap));
    glVertexAttribPointer(normAttr, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, norm));

    glEnableVertexAttribArray(posAttr);
    glEnableVertexAttribArray(texCord);
    glEnableVertexAttribArray(normAttr);



    for (auto item = _maze.MazeBegin(); item!= _maze.MazeEnd(); ++item)
    {
        auto node = *item;
        if (_camera.GetPos().distanceToPoint({static_cast<float>(2.2f * node->GetX()), 0, static_cast<float>(2.2f* node->GetY())}) > 15)
        {
            continue;
        }
        std::vector<std::pair<int, int>> neighbours = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        size_t size = 0;
        for (auto i = node->NeighboursBegin(); i != node->NeighboursEnd(); ++i)
        {
            int dx = static_cast<int>((*i)->GetX()) - node->GetX();
            int dy = static_cast<int>((*i)->GetY()) - node->GetY();
            std::remove(neighbours.begin(), neighbours.end(), std::pair<int, int>{dx, dy});
            ++size;
        }
        neighbours.erase(neighbours.begin() + neighbours.size() - size, neighbours.end());
        for (auto& i: neighbours)
        {
            QMatrix4x4 translation;
            //translation.translate(static_cast<float>(2.2f * node->GetX()) - i.first * 1.05, 0, static_cast<float>(2.2f * node->GetY()) + i.second * 1.05f);
            translation.translate(static_cast<float>(2.2f * node->GetX()) + i.first * 1.05f, 0, static_cast<float>(2.2f * node->GetY()) + i.second * 1.05f);

            QMatrix4x4 rotateMatrix;
            //rotateMatrix.translate(0, 0, -1);
            if (i.first != 0)
            {
                rotateMatrix.rotate(90 * i.first, 0, 1, 0);
            }
            if (i.second !=0)
            {
                rotateMatrix.rotate(180 - 90 * (1 + i.second), 0, 1, 0);
            }

            _program.setUniformValue("rotateMatrix", rotateMatrix);
            _program.setUniformValue("translation", translation);

            glDrawElements(GL_TRIANGLES, (unsigned int)Plain::GetIndices().size(), GL_UNSIGNED_INT, Plain::GetIndices().data());
        }
    }
    glDisableVertexAttribArray(posAttr);
    glDisableVertexAttribArray(texCord);
    //std::cout<<std::endl;
    //Balk Generation
    _program.setUniformValue("texture", 2);
    _program.setUniformValue("textureNormalMap", 3);

    _program.setUniformValue("specularReflection", 1000.f);
    _program.setUniformValue("rotateMatrix", QMatrix4x4{});

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*_balkVertices.size(), _balkVertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(posAttr, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, posAttr));
    glVertexAttribPointer(texCord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uvMap));
    glVertexAttribPointer(normAttr, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, norm));

    glEnableVertexAttribArray(posAttr);
    glEnableVertexAttribArray(texCord);
    glEnableVertexAttribArray(normAttr);
    for (size_t x = 0; x <= _mazeWidth; ++x)
    {
        for (size_t y = 0; y <= _mazeHeight; ++y)
        {
            if (_camera.GetPos().distanceToPoint({static_cast<float>(2.2f* x), 0, static_cast<float>(2.2f * y)}) > 15)
            {
                continue;
            }
            QMatrix4x4 translation;
            translation.translate(2.2f * x -1.1f, 0, 2.2f * y - 1.1f);
            _program.setUniformValue("translation", translation);

            glDrawArrays(GL_TRIANGLES, 0, _balkVertices.size());
        }
    }
    glDisableVertexAttribArray(posAttr);
    glDisableVertexAttribArray(texCord);
    //FLOOR Generation
    _program.setUniformValue("texture", 4);
    _program.setUniformValue("textureNormalMap", 5);
    _program.setUniformValue("specularReflection", 1000.f);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*_floorVertices.size(), _floorVertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(posAttr, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, posAttr));
    glVertexAttribPointer(texCord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uvMap));
    glVertexAttribPointer(normAttr, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, norm));

    glEnableVertexAttribArray(posAttr);
    glEnableVertexAttribArray(texCord);
    glEnableVertexAttribArray(normAttr);

    for (size_t x = 0; x <= _mazeWidth; ++x)
    {
        for (size_t y = 0; y <= _mazeHeight; ++y)
        {
            if (_camera.GetPos().distanceToPoint({static_cast<float>(2.2f* x), 0, static_cast<float>(2.2f * y)}) > 15)
            {
                continue;
            }
            QMatrix4x4 translation;
            translation.translate(2.2f * x, -1, 2.2f * y);
            QMatrix4x4 rotateMatrix;
            rotateMatrix.rotate(90, 1, 0, 0);
            _program.setUniformValue("rotateMatrix", rotateMatrix);
            _program.setUniformValue("translation", translation);

            glDrawElements(GL_TRIANGLES, (unsigned int)Plain::GetIndices().size(), GL_UNSIGNED_INT, Plain::GetIndices().data());
        }
    }
    glDisableVertexAttribArray(posAttr);
    glDisableVertexAttribArray(texCord);

    _program.release();
}

void MainWindow::MoveCameraOnKey(float step) noexcept
{
    _player.setSource(QUrl::fromLocalFile("./Resources/walk.wav"));
    _player.setLoops(1);
    bool play = false;
    if (_pressedKeys.contains(42))
    {
        //_player.setPlaybackRate(2);
        _camera.SetMoveCoff(2);
    }else
    {
        //_player.setPlaybackRate(1);
        _camera.SetMoveCoff(1);
    }
    if (_pressedKeys.contains(17))
    {
        play = true;
        _camera.MoveForward(step);
    }
    if (_pressedKeys.contains(31))
    {
        play = true;
        _camera.MoveForward(-step);
    }
    if (_pressedKeys.contains(30))
    {
        play = true;
        _camera.MoveSideway(-step);
    }
    if (_pressedKeys.contains(32))
    {
        play = true;
        _camera.MoveSideway(step);
    }
    if (play)
    {
        _player.play();
    }
}

void MainWindow::keyPressEvent(QKeyEvent* key)
{
    _pressedKeys += key->nativeScanCode();
}

void MainWindow::keyReleaseEvent(QKeyEvent* key)
{
    _pressedKeys -= key->nativeScanCode();
}

void MainWindow::mouseMoveEvent(QMouseEvent* mouse)
{
    if (_mousePos != QPoint())
    {
        _camera.SetYawAngle(_camera.GetYawAngle() + 0.3f * (mouse->pos().x() - _mousePos.x()));
        _camera.SetPitchAngle(_camera.GetPitchAngle() + 0.3f  * (-mouse->pos().y() + _mousePos.y()));
    }
    QPoint glob = mapToGlobal(QPoint(width()/2,height()/2));
    QCursor::setPos(glob);
    this->setCursor(QCursor{Qt::BlankCursor});
    _mousePos = QPoint(width()/2,height()/2);
}
