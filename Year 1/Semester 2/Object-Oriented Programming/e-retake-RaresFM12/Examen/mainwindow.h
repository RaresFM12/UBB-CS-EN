#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "observer.h"
#include "service.h"
#include "formgraphic.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public Observer
{
    Q_OBJECT

private:
    Service& serv;
    Chef chef;

public:
    MainWindow(Service& s, Chef c, QWidget *parent = nullptr);
    ~MainWindow();

    void update() override;
    void populateTable();
    void populateWithSpecialities();
    void populateByIngredients(vector<Recipe> recip);

private:
    Ui::MainWindow *ui;

public slots:
    void SeeSpecialities();
    void AddRecipe();
    void SearchByIngredients();
    void ViewGraphic();
};
#endif // MAINWINDOW_H
