#include "mainwindow.h"
#include "circlecreation.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Фигуры");
    w.show();
    return a.exec();
}
