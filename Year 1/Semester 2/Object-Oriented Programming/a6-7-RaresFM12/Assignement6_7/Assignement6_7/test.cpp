#include "test.h"
#include <iostream>
#include <fstream>
#include <cstring>

void Test::run_all()
{
	TestDate();
	TestEvent();
	TestAdminService();
	TestUserService();
	TestRepository();
	TestHtml();
	TestFile();
	TestExceptions();
}


void Test::TestDate()
{
	datetime d1;
	datetime d2(12, 23, 10, 1999);
	
	d1 = d2;
	assert(d1.getDay() == 23);
	assert(d1.getHour() == 12);
	assert(d1.getMonth() == 10);
	assert(d1.getYear() == 1999);

	std::string str = "23/10/1999 at 12:00\n";
	assert(str == d1.toString());
}

void Test::TestEvent()
{
	Event e1;
	datetime d1(12, 12, 12, 1999);
	Event e2("t1", "d1", d1, 1, "w");

	assert(e2.getTitle() == "t1");
	assert(e2.getDescription() == "d1");
	datetime day = e2.getDateTime();
	assert(day.getDay() == d1.getDay());
	assert(e2.getNrOfPeople() == 1);
	assert(e2.getLink() == "w");

	e1 = e2;
	e1.setTitle("t2");
	e1.setDescription("d2");
	datetime d2(11, 11, 11, 1999);
	e1.setDateTime(d2);
	e1.setNrOfPeople(12);
	e1.setLink("w2");

	assert(e1.getTitle() == "t2");
	assert(e1.getDescription() == "d2");
	day = e1.getDateTime();
	assert(day.getDay() == d2.getDay());
	assert(e1.getNrOfPeople() == 12);
	assert(e1.getLink() == "w2");

	std::string str = "TITLE: t2\nDESCRIPTION: d2\nDATE AND TIME: " + d2.toString() + "NUMBER OF PEOPLE: 12\n" +
		"LINK: w2\n";

	assert(str == e1.toString());

	datetime d3(11, 12, 12, 1999);
	e1.setDateTime(d3);
	assert(e1 < e2);

	datetime d4(11, 12, 12, 1998);
	e1.setDateTime(d4);
	assert(e1 < e2);
	

	datetime d5(11, 12, 12, 2000);
	e1.setDateTime(d5);
	bool ok = (e1 < e2);
	assert(!ok);

	datetime d6(11, 12, 11, 1999);
	e1.setDateTime(d6);
	assert(e1 < e2);

	datetime d8(11, 12, 10, 1999);
	datetime d7(11, 12, 11, 1999);
	e2.setDateTime(d8);
	e1.setDateTime(d7);
	ok = (e1 < e2);
	assert(!ok);

	datetime d9(11, 11, 10, 1999);
	e1.setDateTime(d9);
	assert(e1 < e2);

	datetime d10(11, 13, 10, 1999);
	e1.setDateTime(d10);
	ok = (e1 < e2);
	assert(!ok);

	datetime d11(12, 12, 10, 1999);
	e1.setDateTime(d11);
	ok = (e1 < e2);
	assert(!ok);

	datetime d12 = d8;
	e1.setDateTime(d12);
	ok = (e1 < e2);
	assert(!ok);
}

void Test::TestAdminService()
{
	Repository r;
	AdminService ad1(r);
	AdminService ad2(r);

	datetime d1(12, 12, 12, 1999);
	Event e1("t1", "d1", d1, 1, "w");
	bool ok = ad2.HandleAddEvent(e1);
	assert(ok);

	try {
		ok = ad2.HandleAddEvent(e1);
	}
	catch (InTheEventListException& ee) {
		assert(true);
	}

	Event e2("t1", "d1", d1, 1, "w");
	ok = ad2.HandleUpdateEvent(e2);
	assert(ok);

	datetime d2(12, 12, 12, 1998);
	Event e3("t2", "sdfads", d2, 1, "2");

	try {
		ok = ad2.HandleUpdateEvent(e3);
	}
	catch (NotInAdminListException& ae){
		assert(true);
	}

	try {
		ok = ad2.HandleDeleteEvent("fdaads");
	}
	catch (NotInAdminListException& ae) {
		assert(true);
	}
	
	ok = ad2.HandleDeleteEvent("t1");
	assert(ok);

	assert(ad2.handleGetAll().size() == 0);

	ad2.HandleAddEvent(e1);
	ad2.HandleAddEvent(e3);
	std::vector<Event> v = ad2.HandleGetEventsByMonth(12);
	assert(v.size() == 2);

	e2 = ad2.handleGetEventByName("t1");
	assert(e2.getTitle() == "t1");

	v = ad2.handleFilterEvents(0);
	assert(v.size() == 2);

	v = ad2.handleGetAllSorted();
	assert(v.size() == 2);

}

void Test::TestRepository()
{
	Repository r("csv");
	datetime d1(12, 12, 12, 1999);
	Event e1("t1", "d1", d1, 1, "w");

	r.addEvent(e1);
	std::vector<Event> v = r.getAll();
	assert(v.size() == 1);

	Event e2("t2", "d1", d1, 1, "w2");
	r.updateEvent(0, e2);
	v = r.getAll();
	Event e3 = v[0];
	assert(e3.getTitle() == "t2"); 

	try {
		r.getEventByName("t1");
	}
	catch (std::exception e) {
		assert(true);
	}

	r.deleteEvent(0);
	v = r.getAll();
	assert(v.size() == 0);

	r.addEventToUserList(e1);
	r.addEventToUserList(e2);
	v = r.getAllUserEvents();
	assert(v.size() == 2);

	r.deleteEventUserList(1);
	v = r.getAllUserEvents();
	assert(v.size() == 1);

	r.clearUserList();
	v = r.getAllUserEvents();
	assert(v.size() == 0);

	
}

void Test::TestUserService()
{
	Repository r("csv");
	UserService us(r);
	datetime d1(12, 12, 12, 1999);
	Event e1("t1", "d1", d1, 1, "w");

	bool ok = us.HandleAddEventToUserList(e1);
	assert(ok);

	try {
		ok = us.HandleAddEventToUserList(e1);
	}
	catch (InTheUserListException& ue) {
		assert(true);
	}

	Event e2("t2", "d1", d1, 1, "w");
	us.HandleAddEventToUserList(e2);

	ok = us.HandleDeleteEventUserList("t2");
	assert(ok);

	try {
		ok = us.HandleDeleteEventUserList("fefafs");
	}
	catch (NotInAdminListException& ue) {
		assert(true);
	}

	std::vector<Event> v = us.HandleGetAllUserEvents();
	assert(v.size() == 1);

	us.handleClearUserList();
	v = us.HandleGetAllUserEvents();
	assert(v.size() == 0);  
}

void Test::TestHtml()
{
	Repository r("html");
	UserService us(r);
	datetime d1(12, 12, 12, 1999);
	Event e1("t1", "d1", d1, 1, "w");

	bool ok = us.HandleAddEventToUserList(e1);
	assert(ok);

	try {
		ok = us.HandleAddEventToUserList(e1);
	}
	catch (InTheUserListException& ue) {
		assert(true);
	}

	Event e2("t2", "d1", d1, 1, "w");
	us.HandleAddEventToUserList(e2);

	ok = us.HandleDeleteEventUserList("t2");
	assert(ok);

	try {
		ok = us.HandleDeleteEventUserList("fefafs");
	}
	catch (NotInAdminListException& ue) {
		assert(true);
	}

	std::vector<Event> v = us.HandleGetAllUserEvents();
	assert(v.size() == 1);

	us.handleClearUserList();
	v = us.HandleGetAllUserEvents();
	assert(v.size() == 0);
}

void Test::TestFile()
{
	std::ifstream fin("test.txt");
	Event e;
	fin >> e;
	assert(e.getTitle() == "t1");
	fin.close();

	FileRepository rr1;
	try {
		rr1.addEvent(e);
	}
	catch (FileRepoException& ex) {
		assert(true);
	}

	try {
		FileRepository rr2("test.tx", "csv");
	}
	catch (FileRepoException& ex) {
		assert(true);
	}
	FileRepository rr2("test.txt", "csv");
	
	FileRepository r1("test.txt");
	Event e1("t2", "d2", datetime(1, 1, 1, 1999), 1, "l2");
	r1.addEvent(e1);
	assert(r1.getAll().size() == 2);
	r1.updateEvent(1, e);
	assert(e.getTitle() == r1.getAll()[1].getTitle());
	r1.deleteEvent(1);
	assert(r1.getAll().size() == 1);

	try {
		r1.addEvent(e);
	}
	catch (InTheEventListException& ex) {
		assert(true);
	}
}

void Test::TestExceptions()
{
	NrPeopleException e1;
	NotInAdminListException e2;
	InTheUserListException e3;
	InTheEventListException e4;
	FileRepoException e5;
	EventExceptions e6;

	char a[100];
	try {
		throw NrPeopleException("A");
	}
	catch (NrPeopleException& e) {
		strcpy_s(a, e.what());
		assert(true);
	}

	try {
		throw NotInAdminListException("A");
	}
	catch (NotInAdminListException& e) {
		strcpy_s(a, e.what());
		assert(true);
	}

	try {
		throw InTheUserListException("A");
	}
	catch (InTheUserListException& e) {
		strcpy_s(a, e.what());
		assert(true);
	}

	try {
		throw InTheEventListException("A");
	}
	catch (InTheEventListException& e) {
		strcpy_s(a, e.what());
		assert(true);
	}

	try {
		throw FileRepoException("A");
	}
	catch (FileRepoException& e) {
		strcpy_s(a, e.what());
		assert(true);
	}

	try {
		throw EventExceptions("A");
	}
	catch (EventExceptions& e) {
		strcpy_s(a, e.what());
		assert(true);
	}

	Event ee1("", "", datetime(-1, -1, -1, -1), -1, "");
	EventValidator v;
	try {
		v.validateEventTitle(ee1.getTitle());
	}
	catch (EventExceptions& e) {
		assert(true);
	}

	ee1.setTitle("t1");
	try {
		v.validateEventDesc(ee1.getDescription());
	}
	catch (EventExceptions& e) {
		assert(true);
	}

	ee1.setDescription("d1");
	try {
		v.validateEventDate(ee1.getDateTime());
	}
	catch (EventExceptions& e) {
		assert(true);
	}

	ee1.setDateTime(datetime(-1, 1, -1, -1));
	try {
		v.validateEventDate(ee1.getDateTime());
	}
	catch (EventExceptions& e) {
		assert(true);
	}

	ee1.setDateTime(datetime(-1, 1, 1, -1));
	try {
		v.validateEventDate(ee1.getDateTime());
	}
	catch (EventExceptions& e) {
		assert(true);
	}

	ee1.setDateTime(datetime(-1, 1, 1, 1999));
	try {
		v.validateEventDate(ee1.getDateTime());
	}
	catch (EventExceptions& e) {
		assert(true);
	}

	ee1.setDateTime(datetime(1, 1, 1, 1999));
	try {
		v.validateEventNrPeople(ee1.getNrOfPeople());
	}
	catch (EventExceptions& e) {
		assert(true);
	}

	ee1.setNrOfPeople(1);
	try {
		v.validateEventLink(ee1.getLink());
	}
	catch (EventExceptions& e) {
		assert(true);
	}

	ee1.setLink("l1");

	v.validateEventLink(ee1.getLink());
	v.validateEventNrPeople(ee1.getNrOfPeople());
	v.validateEventDate(ee1.getDateTime());
	v.validateEventDesc(ee1.getDescription());
	v.validateEventTitle(ee1.getTitle());
	
}