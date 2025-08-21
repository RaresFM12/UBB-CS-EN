#include "UserWidget.h"

using namespace CONSTANTS;

UserWidget::UserWidget(std::string type, AdminService& ad, QWidget* parent) :
	QWidget(parent), serv {ad}, currEventVec {std::vector<Event>()}, 
	currPos {-1}, format {type}
{
	myModel = new MyModel(this);
	QHBoxLayout* userLayout = new QHBoxLayout;
	QVBoxLayout* userInfo = new QVBoxLayout;

	QHBoxLayout* buttons = createButtonsForManagingAddEvents();
	QHBoxLayout* showLayout = createShowEventLayout();
	QHBoxLayout* deleteLayout = createDeleteEventLayout();

	userInfo->setSpacing(DEFAULT_SPACING);
	userInfo->addLayout(showLayout);
	userInfo->addLayout(buttons);
	userInfo->addLayout(deleteLayout);
	formatBtn = new QPushButton("Show in Format", this);
	userInfo->addWidget(formatBtn);

	createTableWidgetAdd();
	userLayout->addWidget(tableWidgetAdd);
	userLayout->addLayout(userInfo);
	createTableWidget();
	userLayout->addWidget(tableWidget);

	this->setLayout(userLayout);

	connect(showBtn, &QPushButton::clicked, this, &UserWidget::ShowByMonth);
	connect(passBtn, &QPushButton::clicked, this, &UserWidget::PassEvent);
	connect(stopBtn, &QPushButton::clicked, this, &UserWidget::StopEvent);
	connect(addBtn, &QPushButton::clicked, this, &UserWidget::AddEvent);
	connect(formatBtn, &QPushButton::clicked, this, &UserWidget::ShowInFormat);
	connect(deleteBtn, &QPushButton::clicked, this, &UserWidget::DeleteEvent);
}

void UserWidget::ShowByMonth()
{
	int month;
	if (leDate->text().isEmpty())
		month = 0;
	else
		month = leDate->text().toInt();

	leDate->clear();
	if (month == 0)
	{
		currEventVec = serv.handleGetAllSorted();
		currPos = 0;
	}
	else
	{
		currEventVec = serv.HandleGetEventsByMonth(month);
		if (currEventVec.size() == 0)
		{
			QMessageBox::critical(this, "Error", "There is no such event in this month!");
			return;
		}

		currPos = 0;
	}

	ShowEventOnTable();
}

void UserWidget::DeleteEvent()
{
	std::string title = leTitle->text().toStdString();
	EventValidator v;

	try {
		v.validateEventTitle(title);
		int row = serv.HandleDeleteEventUserList(title);

		Event e = serv.handleGetEventByName(title);
		int nr = e.getNrOfPeople();
		e.setNrOfPeople(nr - 1);

		serv.HandleUpdateEvent(e);
		leTitle->clear();
		//tableWidget->remove(row);
		populateTable();
	}
	catch (EventExceptions& ne) {
		QMessageBox::critical(this, "Error", ne.what());
	}
	catch (NotInAdminListException& ae) {
		QMessageBox::critical(this, "Error", ae.what());
	}
	catch (FileRepoException& ee) {
		QMessageBox::critical(this, "Error", ee.what());
	}
}

void UserWidget::AddEvent()
{
	if (currPos == -1)
		return;

	bool ok;
	try {
		Event e = currEventVec[currPos];
		int nr = e.getNrOfPeople();
		e.setNrOfPeople(nr + 1);

		ok = serv.HandleAddEventToUserList(e);
		currEventVec[currPos].setNrOfPeople(nr + 1);
		serv.HandleUpdateEvent(currEventVec[currPos]);
		populateTable();
	}
	catch (InTheUserListException& ex) {
		QMessageBox::critical(this, "Error", ex.what());
	}

	++currPos;
	if (currPos >= currEventVec.size())
		currPos = 0;

	ShowEventOnTable();
}

void UserWidget::populateTable()
{
	std::vector<Event> vec = serv.HandleGetAllUserEvents();
	myModel->setEvents(vec);
	/*int rowCount = tableWidget->rowCount();
	tableWidget->insertRow(rowCount);
	tableWidget->setItem(rowCount, TITLE_COLUMN, new QTableWidgetItem(QString::fromStdString(currEventVec[currPos].getTitle())));
	tableWidget->setItem(rowCount, DESCRIPTION_COLUMN, new QTableWidgetItem(QString::fromStdString(currEventVec[currPos].getDescription())));
	tableWidget->setItem(rowCount, DATE_COLUMN, new QTableWidgetItem(QString::fromStdString(currEventVec[currPos].getDateTime().toString())));
	tableWidget->setItem(rowCount, PEOPLE_COLUMN, new QTableWidgetItem(QString::fromStdString(std::to_string(currEventVec[currPos].getNrOfPeople()))));
	tableWidget->setItem(rowCount, LINK_COLUMN, new QTableWidgetItem(QString::fromStdString(currEventVec[currPos].getLink())));*/
}

void UserWidget::StopEvent()
{
	tableWidgetAdd->clearContents();
	tableWidgetAdd->setRowCount(1);
	currEventVec.clear();
	currPos = -1;
}

void UserWidget::PassEvent()
{
	if (currPos == -1)
		return;

	++currPos;
	if (currPos >= currEventVec.size())
		currPos = 0;

	ShowEventOnTable();
}

void UserWidget::ShowEventOnTable()
{
	std::string url = currEventVec[currPos].getLink();
	std::string com = "start " + url;
	system(com.c_str());
	tableWidgetAdd->setItem(0, TITLE_COLUMN, new QTableWidgetItem(QString::fromStdString(currEventVec[currPos].getTitle())));
	tableWidgetAdd->setItem(0, DESCRIPTION_COLUMN, new QTableWidgetItem(QString::fromStdString(currEventVec[currPos].getDescription())));
	tableWidgetAdd->setItem(0, DATE_COLUMN, new QTableWidgetItem(QString::fromStdString(currEventVec[currPos].getDateTime().toString())));
	tableWidgetAdd->setItem(0, PEOPLE_COLUMN, new QTableWidgetItem(QString::fromStdString(std::to_string(currEventVec[currPos].getNrOfPeople()))));
	tableWidgetAdd->setItem(0, LINK_COLUMN, new QTableWidgetItem(QString::fromStdString(currEventVec[currPos].getLink())));
}

void UserWidget::ShowInFormat()
{
	std::string path;
	if (format == "csv")
		path = "date.csv";
	else
		path = "date.html";

	std::string com = "start " + path;
	system(com.c_str());
}

UserWidget::~UserWidget()
{}

void UserWidget::createTableWidget()
{
	tableWidget = new QTableView(this);
	tableWidget->setModel(myModel);
	/*QStringList header = {"Title", "Description", "Date", "Nr. of people", "Link"};
	//tableWidget->setColumnCount(TABLE_COLUMN_COUNT);
	//tableWidget->setColumnWidth(TITLE_COLUMN, TITLE_COLUMN_WIDTH);
	//tableWidget->setHorizontalHeaderLabels(header);

	for (auto e : serv.HandleGetAllUserEvents())
	{
		/*int rowCount = tableWidget->rowCount();
		tableWidget->insertRow(rowCount);
		tableWidget->setItem(rowCount, TITLE_COLUMN, new QTableWidgetItem(QString::fromStdString(e.getTitle())));
		tableWidget->setItem(rowCount, DESCRIPTION_COLUMN, new QTableWidgetItem(QString::fromStdString(e.getDescription())));
		tableWidget->setItem(rowCount, DATE_COLUMN, new QTableWidgetItem(QString::fromStdString(e.getDateTime().toString())));
		tableWidget->setItem(rowCount, PEOPLE_COLUMN, new QTableWidgetItem(QString::fromStdString(std::to_string(e.getNrOfPeople()))));
		tableWidget->setItem(rowCount, LINK_COLUMN, new QTableWidgetItem(QString::fromStdString(e.getLink())));
	}*/

}

void UserWidget::createTableWidgetAdd()
{
	tableWidgetAdd = new QTableWidget(this);
	
	QStringList header = { "Title", "Description", "Date", "Nr. of people", "Link" };
	tableWidgetAdd->setColumnCount(TABLE_COLUMN_COUNT);
	tableWidgetAdd->setHorizontalHeaderLabels(header);
	tableWidgetAdd->setRowCount(1);
}

QHBoxLayout* UserWidget::createButtonsForManagingAddEvents()
{
	QHBoxLayout* buttons = new QHBoxLayout();
	addBtn = new QPushButton("Add", this);
	passBtn = new QPushButton("Pass", this);
	stopBtn = new QPushButton("Stop", this);

	buttons->addWidget(addBtn);
	buttons->addWidget(passBtn);
	buttons->addWidget(stopBtn);

	return buttons;
}

QHBoxLayout* UserWidget::createDeleteEventLayout()
{
	QLabel* eventTitle = new QLabel("Title of Event:", this);
	leTitle = new QLineEdit(this);
	deleteBtn = new QPushButton("Delete", this);
	QHBoxLayout* eventTitleGroup = new QHBoxLayout();

	eventTitleGroup->addWidget(eventTitle);
	eventTitleGroup->addWidget(leTitle);
	eventTitleGroup->addWidget(deleteBtn);

	return eventTitleGroup;
}

QHBoxLayout* UserWidget::createShowEventLayout()
{
	QLabel* showLabel = new QLabel("The month:", this);
	leDate = new QLineEdit(this);
	showBtn = new QPushButton("Show", this);
	QHBoxLayout* eventShowGroup = new QHBoxLayout();

	eventShowGroup->addWidget(showLabel);
	eventShowGroup->addWidget(leDate);
	eventShowGroup->addWidget(showBtn);

	return eventShowGroup;
}