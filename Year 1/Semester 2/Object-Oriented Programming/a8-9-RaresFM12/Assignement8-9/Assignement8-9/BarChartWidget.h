#ifndef BARCHARTWIDGET_H
#define BARCHARTWIDGET_H
#include <QWidget>

#include "service_admin.h"

class BarChartWidget : public QWidget {
	Q_OBJECT 

private:
	AdminService& serv;

public:
	BarChartWidget(AdminService& serv, QWidget* parent = nullptr);
	~BarChartWidget();


};

#endif // BARCHARTWIDGET_H