#ifndef FORMGRAPHIC_H
#define FORMGRAPHIC_H

#include <QWidget>
#include "service.h"
#include "observer.h"

namespace Ui {
class FormGraphic;
}

class FormGraphic : public QWidget, public Observer
{
    Q_OBJECT

private:
    Service& serv;
    string cuisine;

    void update() override;
    void paintEvent(QPaintEvent* ev) override;

public:
    explicit FormGraphic(Service& s, string cui, QWidget *parent = nullptr);
    ~FormGraphic();

private:
    Ui::FormGraphic *ui;
};

#endif // FORMGRAPHIC_H
