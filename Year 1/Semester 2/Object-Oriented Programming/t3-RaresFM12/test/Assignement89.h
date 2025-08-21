#pragma once

#include <QtWidgets/QMainWindow>
#include <QListWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QColor>
#include <QFont>
#include "ui_Assignement89.h"
#include "service.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Service serv;

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void populateWidgetView();
    void populateFoundDocuments(vector<Engine> eng);
    void ShowSimilarity(Engine e, string text);
private:
    Ui::Assignement89Class ui;
    
public slots:
    void FindDocument();
};
