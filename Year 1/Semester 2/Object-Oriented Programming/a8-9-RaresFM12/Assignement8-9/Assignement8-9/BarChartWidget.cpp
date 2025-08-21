#include "BarChartWidget.h"

BarChartWidget::BarChartWidget(AdminService& ad, QWidget* parent) :
	QWidget(parent), serv{ ad }
{}

BarChartWidget::~BarChartWidget()
{}