#include "Assignement89.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), serv {Service()}
{
    ui.setupUi(this);
      
    populateWidgetView();

    connect(ui.lineEdit, &QLineEdit::textChanged, this, &MainWindow::FindDocument);
}

//currentItem
void MainWindow::FindDocument()
{
    string text = ui.lineEdit->text().toStdString();
    vector<Engine> vec = serv.getAllService();
    vector<Engine> eng;

    for (auto a : vec)
        if (a.getName().find(text) != string::npos ||
            a.getKeyWords().find(text) != string::npos ||
            a.getContent().find(text) != string::npos)
            eng.push_back(a);

    string cur = ui.listWidget->currentItem()->text().toStdString();
    Engine e;
    for (auto a : vec)
        if (cur.find(a.getName()) != string::npos)
        {
            e = a;
            break;
        }
            
    ShowSimilarity(e, text);
    populateFoundDocuments(eng);
}

void MainWindow::ShowSimilarity(Engine e, string text)
{
    double f = 0;
    string c = "";
    double len = e.getKeyWords().length();
    for (int i = 0; i < text.length(); ++i)
    {
        c += text[i];
        if (e.getKeyWords().find(c) == string::npos)
            break;

        f = c.length() / len;
    }

    ui.lineEdit_2->setText(QString::number(f));
}

void MainWindow::populateFoundDocuments(vector<Engine> eng)
{
    ui.listWidget_2->clear();
    for (auto a : eng)
    {
        QListWidgetItem* it = new QListWidgetItem(QString::fromStdString(a.getName())
            + " | " + QString::fromStdString(a.getKeyWords()));

        ui.listWidget_2->addItem(it);
    }
}

void MainWindow::populateWidgetView()
{
    ui.listWidget->clear();
    vector<Engine> vec = serv.getAllService();
    for (auto a : vec)
    {
        QListWidgetItem* it = new QListWidgetItem(QString::fromStdString(a.getName()) 
            + " | " + QString::fromStdString(a.getKeyWords()));

        ui.listWidget->addItem(it);
    }
}

MainWindow::~MainWindow()
{}

