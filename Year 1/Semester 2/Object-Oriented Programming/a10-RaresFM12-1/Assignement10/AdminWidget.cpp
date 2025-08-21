#include "AdminWidget.h"

using namespace CONSTANT;

AdminWidget::AdminWidget(AdminService& ad, QWidget* parent) :
	QWidget(parent), serv {ad}
{
	myModel = new MyModel(this);
	QHBoxLayout* adminLayout = new QHBoxLayout;
	QVBoxLayout* eventInfo = new QVBoxLayout;

	QHBoxLayout* eventTitle = createEventTitleLayout();
	QHBoxLayout* eventDesc = createEventDescLayout();
	QHBoxLayout* eventDate = createEventDateLayout();
	QHBoxLayout* eventPeople = createEventNrPeopleLayout();
	QHBoxLayout* eventLink = createEventLinkLayout();
	QHBoxLayout* buttons = createButtonsForManagingEvents();

	eventInfo->setSpacing(DEFAULT_SPACING);
	eventInfo->addLayout(eventTitle);
	eventInfo->addLayout(eventDesc);
	eventInfo->addLayout(eventDate);
	eventInfo->addLayout(eventPeople);
	eventInfo->addLayout(eventLink);
	eventInfo->addLayout(buttons);

	adminLayout->addLayout(eventInfo);
	createTableWidget();
	adminLayout->addWidget(tableWidget);
	this->setLayout(adminLayout);

	connect(addEvent, &QPushButton::clicked, this, &AdminWidget::AddEvent);
	connect(deleteEvent, &QPushButton::clicked, this, &AdminWidget::DeleteEvent);
	connect(updateEvent, &QPushButton::clicked, this, &AdminWidget::UpdateEvent);
	connect(filterEvent, &QPushButton::clicked, this, &AdminWidget::FilterEventByPeople);

}

void AdminWidget::populateTable() 
{
	std::vector<Event> vec = serv.handleGetAll();
	myModel->setEvents(vec);
	/*int rowCount = tableWidget->rowCount();
	tableWidget->insertRow(rowCount);
	tableWidget->setItem(rowCount, TITLE_COLUMN, new QTableWidgetItem(QString::fromStdString(ev.getTitle())));
	tableWidget->setItem(rowCount, DESCRIPTION_COLUMN, new QTableWidgetItem(QString::fromStdString(ev.getDescription())));
	tableWidget->setItem(rowCount, DATE_COLUMN, new QTableWidgetItem(QString::fromStdString(ev.getDateTime().toString())));
	tableWidget->setItem(rowCount, PEOPLE_COLUMN, new QTableWidgetItem(QString::fromStdString(std::to_string(ev.getNrOfPeople()))));
	tableWidget->setItem(rowCount, LINK_COLUMN, new QTableWidgetItem(QString::fromStdString(ev.getLink())));*/
}

void AdminWidget::AddEvent()
{
	std::string title = leTitle->text().toStdString();
	std::string desc = leDesc->text().toStdString();
	std::string dateStr = leDate->text().toStdString();
	std::string people = lePeople->text().toStdString();
	std::string link = leLink->text().toStdString();
	int hour = 0, month = 0, year = 0, day = 0;
	EventValidator v;

	try {
		v.validateEventTitle(title);
		v.validateEventDesc(desc);
		v.validateEventLink(link);

		validDate(dateStr, hour, day, month, year);
		datetime date = datetime(hour, day, month, year);

		int nr = 0;
		validNrOfPeople(people, nr);
		v.validateEventNrPeople(nr);

		Event ev = Event(title, desc, date, nr, link);
		serv.HandleAddEvent(ev);
		populateTable();
		leTitle->clear();
		leDesc->clear();
		leDate->clear();
		lePeople->clear();
		leLink->clear();
	}
	catch (EventExceptions& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
	catch (NrPeopleException& ne) {
		QMessageBox::critical(this, "Error", ne.what());
	}
	catch (InTheEventListException& ee) {
		QMessageBox::critical(this, "Error", ee.what());
	}
	catch (FileRepoException& ee) {
		QMessageBox::critical(this, "Error", ee.what());
	}
	
}

void AdminWidget::DeleteEvent()
{
	std::string title = leTitle->text().toStdString();
	EventValidator v;

	try {
		v.validateEventTitle(title);
		int row = serv.HandleDeleteEvent(title);
		leTitle->clear();
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

void AdminWidget::UpdateEvent()
{
	std::string title = leTitle->text().toStdString();
	std::string desc = leDesc->text().toStdString();
	std::string dateStr = leDate->text().toStdString();
	std::string people = lePeople->text().toStdString();
	std::string link = leLink->text().toStdString();
	int hour = 0, month = 0, year = 0, day = 0;
	EventValidator v;

	try {
		v.validateEventTitle(title);
		v.validateEventDesc(desc);
		v.validateEventLink(link);

		validDate(dateStr, hour, day, month, year);
		datetime date = datetime(hour, day, month, year);

		int nr = 0;
		validNrOfPeople(people, nr);
		v.validateEventNrPeople(nr);

		Event ev = Event(title, desc, date, nr, link);
		int row = serv.HandleUpdateEvent(ev);
		leTitle->clear();
		leDesc->clear();
		leDate->clear();
		lePeople->clear();
		leLink->clear();

		/*tableWidget->setItem(row, TITLE_COLUMN, new QTableWidgetItem(QString::fromStdString(ev.getTitle())));
		tableWidget->setItem(row, DESCRIPTION_COLUMN, new QTableWidgetItem(QString::fromStdString(ev.getDescription())));
		tableWidget->setItem(row, DATE_COLUMN, new QTableWidgetItem(QString::fromStdString(ev.getDateTime().toString())));
		tableWidget->setItem(row, PEOPLE_COLUMN, new QTableWidgetItem(QString::fromStdString(std::to_string(ev.getNrOfPeople()))));
		tableWidget->setItem(row, LINK_COLUMN, new QTableWidgetItem(QString::fromStdString(ev.getLink())));*/
		populateTable();
	}
	catch (EventExceptions& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
	catch (NrPeopleException& ne) {
		QMessageBox::critical(this, "Error", ne.what());
	}
	catch (NotInAdminListException& ae) {
		QMessageBox::critical(this, "Error", ae.what());
	}
	catch (FileRepoException& ee) {
		QMessageBox::critical(this, "Error", ee.what());
	}
	
}

void AdminWidget::FilterEventByPeople()
{
	std::string people = lePeople->text().toStdString();

	try {
		int nr = 0;
		validNrOfPeople(people, nr);
		EventValidator v;
		v.validateEventNrPeople(nr);
		lePeople->clear();
		std::vector<Event> evs = serv.handleFilterEvents(nr);
		FilteredTable(evs);
	}
	catch (EventExceptions& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
	catch (NrPeopleException& ne) {
		QMessageBox::critical(this, "Error", ne.what());
	}
}

void AdminWidget::FilteredTable(std::vector<Event> evs)
{
	myModel->setEvents(evs);

	//tableWidget->clear();
	//tableWidget->setRowCount(0);
	//QStringList header = { "Title", "Description", "Date", "Nr. of people", "Link" };
	//tableWidget->setColumnCount(TABLE_COLUMN_COUNT);
	////tableWidget->setColumnWidth(TITLE_COLUMN, TITLE_COLUMN_WIDTH);
	//tableWidget->setHorizontalHeaderLabels(header);
	//
	//int rowCount = 0;
	//for (auto e : evs)
	//{
	//	tableWidget->insertRow(rowCount);
	//	tableWidget->setItem(rowCount, TITLE_COLUMN, new QTableWidgetItem(QString::fromStdString(e.getTitle())));
	//	tableWidget->setItem(rowCount, DESCRIPTION_COLUMN, new QTableWidgetItem(QString::fromStdString(e.getDescription())));
	//	tableWidget->setItem(rowCount, DATE_COLUMN, new QTableWidgetItem(QString::fromStdString(e.getDateTime().toString())));
	//	tableWidget->setItem(rowCount, PEOPLE_COLUMN, new QTableWidgetItem(QString::fromStdString(std::to_string(e.getNrOfPeople()))));
	//	tableWidget->setItem(rowCount, LINK_COLUMN, new QTableWidgetItem(QString::fromStdString(e.getLink())));
	//	++rowCount;
	//}
}

AdminWidget::~AdminWidget()
{}

void AdminWidget::createTableWidget()
{
	tableWidget = new QTableView();
	tableWidget->setModel(myModel);
	populateTable();
	//QStringList header = { "Title", "Description", "Date", "Nr. of people", "Link" };
	//tableWidget->setColumnCount(TABLE_COLUMN_COUNT);
	////tableWidget->setColumnWidth(TITLE_COLUMN, TITLE_COLUMN_WIDTH);
	//tableWidget->setHorizontalHeaderLabels(header);

	//for (auto e : serv.handleGetAll())
	//{
	//	int rowCount = tableWidget->rowCount();
	//	tableWidget->insertRow(rowCount);
	//	tableWidget->setItem(rowCount, TITLE_COLUMN, new QTableWidgetItem(QString::fromStdString(e.getTitle())));
	//	tableWidget->setItem(rowCount, DESCRIPTION_COLUMN, new QTableWidgetItem(QString::fromStdString(e.getDescription())));
	//	tableWidget->setItem(rowCount, DATE_COLUMN, new QTableWidgetItem(QString::fromStdString(e.getDateTime().toString())));
	//	tableWidget->setItem(rowCount, PEOPLE_COLUMN, new QTableWidgetItem(QString::fromStdString(std::to_string(e.getNrOfPeople()))));
	//	tableWidget->setItem(rowCount, LINK_COLUMN, new QTableWidgetItem(QString::fromStdString(e.getLink())));
	//}
}

QHBoxLayout* AdminWidget::createButtonsForManagingEvents()
{
	QHBoxLayout* buttons = new QHBoxLayout();
	addEvent = new QPushButton("Add event", this);
	deleteEvent = new QPushButton("Delete event", this);
	updateEvent = new QPushButton("Update event", this);
	filterEvent = new QPushButton("Filter by nr. people", this);

	buttons->addWidget(addEvent);
	buttons->addWidget(deleteEvent);
	buttons->addWidget(updateEvent);
	buttons->addWidget(filterEvent);

	return buttons;
}

QHBoxLayout* AdminWidget::createEventTitleLayout()
{
	QLabel* eventTitle = new QLabel("Title of Event:", this);
	leTitle = new QLineEdit(this);
	QHBoxLayout* eventTitleGroup = new QHBoxLayout();
	eventTitleGroup->addWidget(eventTitle);
	eventTitleGroup->addWidget(leTitle);

	return eventTitleGroup;
}

QHBoxLayout* AdminWidget::createEventDescLayout()
{
	QLabel* eventDesc = new QLabel("Desc of Event:", this);
	leDesc = new QLineEdit(this);
	QHBoxLayout* eventDescGroup = new QHBoxLayout();
	eventDescGroup->addWidget(eventDesc);
	eventDescGroup->addWidget(leDesc);

	return eventDescGroup;
}

QHBoxLayout* AdminWidget::createEventDateLayout()
{
	QLabel* eventDate = new QLabel("Date of Event:", this);
	leDate = new QLineEdit(this);
	QHBoxLayout* eventDateGroup = new QHBoxLayout();
	eventDateGroup->addWidget(eventDate);
	eventDateGroup->addWidget(leDate);

	return eventDateGroup;
}

QHBoxLayout* AdminWidget::createEventNrPeopleLayout()
{
	QLabel* eventPeople = new QLabel("Nr. of people:", this);
	lePeople = new QLineEdit(this);
	QHBoxLayout* eventPeopleGroup = new QHBoxLayout();
	eventPeopleGroup->addWidget(eventPeople);
	eventPeopleGroup->addWidget(lePeople);

	return eventPeopleGroup;
}

QHBoxLayout* AdminWidget::createEventLinkLayout()
{
	QLabel* eventLink = new QLabel("Link of Event:", this);
	leLink = new QLineEdit(this);
	QHBoxLayout* eventLinkGroup = new QHBoxLayout();
	eventLinkGroup->addWidget(eventLink);
	eventLinkGroup->addWidget(leLink);

	return eventLinkGroup;
}

void AdminWidget::validDate(std::string date, int& hour, int& day, int& month, int& year)
{
	if (date.size() != 13)
		throw EventExceptions("The values for date and time are not correct!");

	day = (date[0] - '0') * 10 + (date[1] - '0');
	month = (date[3] - '0') * 10 + (date[4] - '0');
	year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 +
		+(date[8] - '0') * 10 + (date[9] - '0');
	hour = (date[11] - '0') * 10 + (date[12] - '0');

	EventValidator v;
	v.validateEventDate(datetime(hour, day, month, year));
}

void AdminWidget::validNrOfPeople(std::string nr, int& nr_people)
{
	for (int i = 0; i < nr.size(); ++i)
		if (!isdigit(nr[i]))
			throw NrPeopleException("The number of people must be an integer!");
		else
		{
			nr_people *= 10;
			nr_people += nr[i] - '0';
		}

	EventValidator v;
	v.validateEventNrPeople(nr_people);
}