#pragma once

#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QToolBar>
#include <QAction>
#include "ui_Assignement89.h"
#include "service_admin.h"
#include "AdminWidget.h"
#include "UserWidget.h"
#include "file_repository.h"
#include "BarChartWidget.h"

namespace CONSTANTS
{
    const std::string FILENAME = "events.txt";
    const int INITIAL_WIDTH = 300;
    const int INITIAL_HEIGHT = 300;
    const int ADMIN_WIDTH = 1200;
    const int ADMIN_HEIGHT = 400;
    const int USER_WIDTH = 1200;
    const int USER_HEIGHT = 400;
    const int ADMIN_LAYOUT_INDEX = 1;
    const int USER_LAYOUT_INDEX = 2;
}

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
    std::string fileType;
    AdminService serv;

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    QHBoxLayout* chooseTypeFile();
    void changeWindow();
    void changeToAdminMode();
    void changeToUserMode();
    void changeToBarChart();
   
private:
    Ui::Assignement89Class ui;
};
