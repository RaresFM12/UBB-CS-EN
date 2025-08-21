#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H
#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include "event.h"
#include "service_admin.h"
#include "validator.h"
#include "TableView.h"

namespace CONSTANT
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

class AdminWidget : public QWidget {
	Q_OBJECT
private:
	AdminService& serv;

public:
	AdminWidget(AdminService& ad, QWidget* parent = nullptr);
	~AdminWidget();

	void createTableWidget();
	QHBoxLayout* createButtonsForManagingEvents();
	QHBoxLayout* createEventTitleLayout();
	QHBoxLayout* createEventDescLayout();
	QHBoxLayout* createEventNrPeopleLayout();
	QHBoxLayout* createEventDateLayout();
	QHBoxLayout* createEventLinkLayout();
	MyModel* myModel;

private:
	QTableView* tableWidget;
	QPushButton *addEvent, *deleteEvent, *updateEvent, *filterEvent;
	QLineEdit *leTitle, *leDesc, *leDate, *lePeople, *leLink;

public slots:
	void AddEvent();
	void populateTable();
	void FilteredTable(std::vector<Event> evs);
	void DeleteEvent();
	void UpdateEvent();
	void FilterEventByPeople();

public:
	void validDate(std::string date, int& hour, int& day, int& month, int& year);
	void validNrOfPeople(std::string nr, int& nr_people);
};


#endif // ADMINWIDGET_H
