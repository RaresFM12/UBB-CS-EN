#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Repository r;
    Service s(r);
    for (auto a : r.getAllChefs())
    {
        MainWindow* w = new MainWindow(s, a);
        w->setWindowTitle(QString::fromStdString(a.getName()));
        s.addObserver(w);
        w->show();
    }

    return a.exec();
}
