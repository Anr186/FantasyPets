#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // MainWindow не показываем напрямую, он управляет другими окнами
    // w.show(); - убрано, так как MainWindow только управляет другими окнами

    return a.exec();
}
