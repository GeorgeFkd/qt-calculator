#include "mainwindow.h"

#include <QApplication>

#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    std::cout << "Hello World";
    std::cout << "Hello World 2";
    w.show();
    return a.exec();
}
