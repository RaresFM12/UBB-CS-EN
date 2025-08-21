#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(Service& s, Chef c, QWidget *parent)
    : QMainWindow(parent), serv {s}, chef {c}
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    populateTable();

    connect(ui->checkBox, &QCheckBox::clicked, this, &MainWindow::SeeSpecialities);
    connect(ui->pushButtonAdd, &QPushButton::clicked, this, &MainWindow::AddRecipe);
    connect(ui->pushButtonSearch, &QPushButton::clicked, this, &MainWindow::SearchByIngredients);
    connect(ui->pushButtonView, &QPushButton::clicked, this, &MainWindow::ViewGraphic);
}

void MainWindow::ViewGraphic()
{
    FormGraphic* fm = new FormGraphic(serv, chef.getSpeciality());
    fm->show();
    serv.addObserver(fm);
}

void MainWindow::SearchByIngredients()
{
    vector<Recipe> recip;
    if (ui->checkBox->isChecked())
    {
        for (auto a : serv.getAllRecipesService())
            if (a.getCuisine() == chef.getSpeciality())
                recip.push_back(a);
    }
    else
        recip = serv.getAllRecipesService();

    vector<string> ing = Recipe::tokenize(ui->lineEditSearch->text().toStdString(), ',');
    vector<Recipe> recipies;

    for (auto a : recip)
    {
        bool not_add = true;
        for (auto b : ing)
        {
            bool found = false;
            for (auto c : a.getIngredients())
                if (b == c)
                    found = true;

            if (found == false)
            {
                not_add = false;
                break;
            }
        }

        if (not_add)
            recipies.push_back(a);
    }

    populateByIngredients(recipies);
}

void MainWindow::AddRecipe()
{
    string na = ui->lineEditName->text().toStdString();
    if (na == "")
    {
        QMessageBox::critical(this, "Error", "The name is empty!");
        return;
    }

    for (auto a : serv.getAllRecipesService())
        if (a.getName() == na)
        {
            QMessageBox::critical(this, "Error", "The name is already in the list!");
            return;
        }

    int t = stoi(ui->lineEditTime->text().toStdString());
    vector<string> ing = Recipe::tokenize(ui->lineEditIng->text().toStdString(), ',');

    Recipe r(na, chef.getSpeciality(), t, ing);
    serv.addRecipeService(r);
}

void MainWindow::SeeSpecialities()
{
    if (ui->checkBox->isChecked())
        populateWithSpecialities();
    else
        populateTable();
}

void MainWindow::populateByIngredients(vector<Recipe> recip)
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    QStringList header = {"Name", "Cuisine", "Time", "Ingredients"};
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(header);

    int rowCount = 0;
    for (auto e : recip)
    {
        ui->tableWidget->insertRow(rowCount);
        ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::fromStdString(e.getName())));
        ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString::fromStdString(e.getCuisine())));
        ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString::number(e.getTime())));

        string str = "";
        for (int i = 0; i < e.getIngredients().size() - 1; ++i)
        {
            str += e.getIngredients()[i];
            str += ',';
        }

        str += e.getIngredients()[e.getIngredients().size() - 1];
        ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString::fromStdString(str)));

        rowCount++;
    }
}

void MainWindow::populateWithSpecialities()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    QStringList header = {"Name", "Cuisine", "Time", "Ingredients"};
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(header);

    int rowCount = 0;
    for (auto e : serv.getAllRecipesService())
        if (e.getCuisine() == chef.getSpeciality())
        {
            ui->tableWidget->insertRow(rowCount);
            ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::fromStdString(e.getName())));
            ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString::fromStdString(e.getCuisine())));
            ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString::number(e.getTime())));

            string str = "";
            for (int i = 0; i < e.getIngredients().size() - 1; ++i)
            {
                str += e.getIngredients()[i];
                str += ',';
            }

            str += e.getIngredients()[e.getIngredients().size() - 1];
            ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString::fromStdString(str)));

            rowCount++;
        }
}

void MainWindow::populateTable()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    QStringList header = {"Name", "Cuisine", "Time", "Ingredients"};
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(header);

    int rowCount = 0;

    vector<Recipe> vec = serv.getAllRecipesService();
    for (int i = 0; i < vec.size() - 1; ++i)
        for (int j = i + 1; j < vec.size(); ++j)
            if (vec[i].getCuisine() > vec[j].getCuisine())
            {
                Recipe aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;
            }

    for (auto e : vec)
    {
        ui->tableWidget->insertRow(rowCount);
        ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::fromStdString(e.getName())));
        ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString::fromStdString(e.getCuisine())));
        ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString::number(e.getTime())));

        string str = "";
        for (int i = 0; i < e.getIngredients().size() - 1; ++i)
        {
            str += e.getIngredients()[i];
            str += ',';
        }

        str += e.getIngredients()[e.getIngredients().size() - 1];
        ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString::fromStdString(str)));

        rowCount++;
    }
}

void MainWindow::update()
{
    if (!ui->checkBox->isChecked())
        populateTable();
    else
        populateWithSpecialities();
}

MainWindow::~MainWindow()
{
    delete ui;
}
