#include <QGuiApplication>
#include "mainwindow.h"
#include <QSurfaceFormat>

#pragma execution_character_set( "utf-8" )ssssd

int main(int argc, char *argv[])
{
    SetConsoleOutputCP( 65001 );
    QGuiApplication app(argc, argv);
    MainWindow window;

    //QSurfaceFormat format;
    //format.setSamples(16);
    //Вылетает exception...
    //window.setFormat(format);

    //window.resize(QWindow::FullScreen);
    window.showFullScreen();
    window.setAnimating(true);

    return app.exec();
}
