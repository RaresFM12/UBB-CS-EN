#include "Assignement89.h"

using namespace CONSTANTS;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), fileType { "" }
{
    ui.setupUi(this);
    
    QHBoxLayout* fileType = chooseTypeFile();
    QWidget* window1 = new QWidget();
    window1->setLayout(fileType);

    setCentralWidget(window1);
}

MainWindow::~MainWindow()
{}

QHBoxLayout* MainWindow::chooseTypeFile()
{
    QLabel* typeFile = new QLabel("The type of file:", this);
    QPushButton* csvButt = new QPushButton("CSV", this);
    QPushButton* htmlButt = new QPushButton("HTML", this);

    connect(csvButt, &QPushButton::clicked, this, [&]() {
        this->fileType = "csv";
        serv = AdminService(fileType);
        changeWindow();
        });

    connect(htmlButt, &QPushButton::clicked, this, [&]() {
        this->fileType = "html";
        serv = AdminService(fileType);
        changeWindow();
        });

    QHBoxLayout* buttons = new QHBoxLayout;
    buttons->addWidget(typeFile);
    buttons->addWidget(csvButt);
    buttons->addWidget(htmlButt);

    return buttons; 
}

void MainWindow::changeWindow()
{
    QHBoxLayout* newLay = new QHBoxLayout();
    QWidget* window2 = new QWidget();
    window2->setLayout(newLay);
    setCentralWidget(window2);

    QToolBar* tb = new QToolBar(this);
    addToolBar(tb);

    QAction* actionAdmin = new QAction("Admin mode", this);
    QAction* actionUser = new QAction("User mode", this);
    QAction* actionBarChart = new QAction("Bar chart", this);

    tb->addAction(actionAdmin);
    tb->addAction(actionUser);
    tb->addAction(actionBarChart);

    connect(actionAdmin, &QAction::triggered, this, [this]()
        {
            changeToAdminMode();
        });

    connect(actionUser, &QAction::triggered, this, [this]()
        { 
            serv.handleClearUserList();
            changeToUserMode();
        });

    connect(actionBarChart, &QAction::triggered, this, [this]()
        {
            changeToBarChart();
        });
    
}

void MainWindow::changeToBarChart()
{
    resize(ADMIN_WIDTH, ADMIN_HEIGHT);
    QWidget* barChartWidget = new BarChartWidget(serv, this);
    setCentralWidget(barChartWidget);
}

void MainWindow::changeToAdminMode()
{
    resize(ADMIN_WIDTH, ADMIN_HEIGHT);
    QWidget* adminWidget = new AdminWidget(serv, this);
    setCentralWidget(adminWidget);
}

void MainWindow::changeToUserMode()
{
    resize(ADMIN_WIDTH, ADMIN_HEIGHT);
    QWidget* userWidget = new UserWidget(fileType, serv, this);
    setCentralWidget(userWidget);
}

