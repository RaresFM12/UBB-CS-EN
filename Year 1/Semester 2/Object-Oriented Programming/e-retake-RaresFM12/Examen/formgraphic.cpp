#include "formgraphic.h"
#include "ui_formgraphic.h"
#include <QPainter>

FormGraphic::FormGraphic(Service& s, string cui, QWidget *parent)
    : QWidget(parent), serv {s}, cuisine {cui}
    , ui(new Ui::FormGraphic)
{
    ui->setupUi(this);
}

void FormGraphic::paintEvent(QPaintEvent* ev)
{
    QPainter p(this);

    int x = 50;
    for (auto a : serv.getAllRecipesService())
        if (a.getCuisine() == cuisine)
        {
            if (a.getTime() > 100)
                p.setPen(Qt::red);
            else
                p.setPen(Qt::black);

            p.drawText(x, 250 + a.getTime(), QString::fromStdString(a.getName()));
            p.drawEllipse(x, 200, a.getTime(), a.getTime());
            x += 150;
        }
}


void FormGraphic::update()
{
    repaint();
}

FormGraphic::~FormGraphic()
{
    delete ui;
}
