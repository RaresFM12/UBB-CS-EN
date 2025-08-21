#include "mainwindow.h"
#include "service.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    Repository repo;
    Service serv(repo);
    vector<Department> dep = repo.getAllDepartments();

    for (auto a : dep)
    {
        MainWindow* w = new MainWindow(serv, a);
        w->setWindowTitle(QString::fromStdString(a.getName()));
        repo.addObserver(w);
        w->show();
    }

    return a.exec();
}
