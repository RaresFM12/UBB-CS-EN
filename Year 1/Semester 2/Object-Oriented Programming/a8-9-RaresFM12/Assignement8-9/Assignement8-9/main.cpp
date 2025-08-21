#include "Assignement89.h"
#include <QtWidgets/QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Events programmer");
    w.show();
    return a.exec();
}
