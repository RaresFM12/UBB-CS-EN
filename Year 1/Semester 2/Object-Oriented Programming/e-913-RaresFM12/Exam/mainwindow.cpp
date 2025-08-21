#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sstream>
#include <QMessageBox>

MainWindow::MainWindow(Service& s, Department dep, QWidget *parent) :
    QMainWindow(parent), d {dep},
    serv {s}, ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("Description: " + QString::fromStdString(d.getDesc()));
    myModel = new MyModel(this);
    ui->tableViewVolunteers->setModel(myModel);
    myModelUn = new MyModel(this);
    ui->tableViewUn->setModel(myModelUn);
    populateTableVolunteers();
    populateWindowUn();

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::AddVol);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::AddToDep);
}

void MainWindow::AddToDep()
{
    QModelIndex ind = ui->tableViewUn->currentIndex();
    string name = myModelUn->data(ind, Qt::DisplayRole).toString().toStdString();

    vector<Volunteer> vec = serv.getAllVol();
    for (auto a : vec)
        if (a.getName() == name)
        {
            serv.modifyDepartmentService(name, d.getName());
            break;
        }

    populateTableVolunteers();
    populateWindowUn();
}

void MainWindow::AddVol()
{
    string name = ui->lineEdit->text().toStdString();
    string email = ui->lineEdit_2->text().toStdString();
    string list = ui->lineEdit_3->text().toStdString();

    if (name == "")
    {
        QMessageBox::critical(this, "Error", "The name is empty!");
        return;
    }

    if (email == "")
    {
        QMessageBox::critical(this, "Error", "The email is empty!");
        return;
    }

    vector<string> res = MainWindow::tokenize(list, ',');

    Volunteer v(name, email, res, "None");
    serv.addVolunteer(v);
    populateWindowUn();
}

vector<string> MainWindow::tokenize(string input, char sep)
{
    stringstream is{ input };
    string token;
    vector<string> res;

    while (getline(is, token, sep))
        res.push_back(token);

    return res;
}

void MainWindow::populateTableVolunteers()
{
    vector<Volunteer> vec = serv.getAllVolunteersService(d.getName());
    myModel->setVolunteers(vec);
}

void MainWindow::populateWindowUn()
{
    vector<Volunteer> vec = serv.getAllUnVol();
    myModelUn->setVolunteers(vec);
}

void MainWindow::update()
{
    populateWindowUn();
    populateTableVolunteers();
}

MainWindow::~MainWindow()
{
    delete ui;
}
