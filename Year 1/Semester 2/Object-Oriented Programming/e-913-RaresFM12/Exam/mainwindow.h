#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "department.h"
#include "service.h"
#include "mymodel.h"
#include "observer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public Observer
{
    Q_OBJECT

private:
    Department d;
    Service& serv;
    MyModel* myModel;
    MyModel* myModelUn;

public:
    MainWindow(Service& se, Department dep, QWidget *parent = nullptr);
    ~MainWindow();

    void populateTableVolunteers();
    void populateWindowUn();
    vector<string> tokenize(string input, char sep);
    void update() override;

private:
    Ui::MainWindow *ui;

public slots:
    void AddVol();
    void AddToDep();
};
#endif // MAINWINDOW_H
