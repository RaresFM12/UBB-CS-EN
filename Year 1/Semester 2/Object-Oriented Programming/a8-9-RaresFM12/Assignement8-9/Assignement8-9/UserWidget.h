#ifndef USERWIDGET_H
#define USERWIDGET_H
#include <QWIDGET>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <vector>
#include "event.h"
#include "service_admin.h"
#include "validator.h"
#include "TableView.h"

namespace CONSTANTS
{
	const int TABLE_COLUMN_COUNT = 5;
	const int DEFAULT_SPACING = 20;
	const int TITLE_COLUMN = 0;
	const int DESCRIPTION_COLUMN = 1;
	const int DATE_COLUMN = 2;
	const int PEOPLE_COLUMN = 3;
	const int LINK_COLUMN = 4;
	const int TITLE_COLUMN_WIDTH = 300;
}

class UserWidget : public QWidget {
	Q_OBJECT

private:
	AdminService& serv;
	std::string format;

public:
	UserWidget(std::string type, AdminService& ad, QWidget* parent = nullptr);
	~UserWidget();

	void createTableWidget();
	void createTableWidgetAdd();


	QHBoxLayout* createButtonsForManagingAddEvents();
	QHBoxLayout* createDeleteEventLayout();
	QHBoxLayout* createShowEventLayout();

private:
	MyModel* myModel;
	QTableView* tableWidget;
	QTableWidget* tableWidgetAdd;
	QPushButton *showBtn, *passBtn, *addBtn, *stopBtn, *deleteBtn, *formatBtn;
	QLineEdit *leDate, *leTitle;
	int currPos;
	std::vector<Event> currEventVec;

public slots:
	void ShowByMonth();
	void ShowEventOnTable();
	void PassEvent();
	void StopEvent();
	void AddEvent();
	void populateTable();
	void ShowInFormat();
	void DeleteEvent();
};

#endif // USERWIDGET_H