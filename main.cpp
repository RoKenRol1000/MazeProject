#include <QCoreApplication>
#include "mainwindow.h"
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    MainWindow window;

    QSurfaceFormat format;
    format.setSamples(16);

    window.setFormat(format);
    window.resize(640, 480);
    window.show();
    window.setAnimating(true);

    return app.exec();
}
