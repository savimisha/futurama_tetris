#include <QtWidgets>
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Futurama Tetris");
    a.setApplicationDisplayName("Futurama Tetris");
    a.setApplicationVersion("1.0.0.0");
    MainWindow w;
    w.setWindowTitle("Futurama Tetris");
    w.setWindowIcon(QIcon(":/nibbler.ico"));
    w.show();
    return a.exec();
}


