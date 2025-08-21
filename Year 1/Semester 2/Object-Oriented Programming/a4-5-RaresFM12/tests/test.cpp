#include "test.h"

void Test::run_all()
{
	TestDynamicVector();
	TestDate();
	TestEvent();
	TestAdminService();
	TestUserService();
	TestRepository();
}

void Test::TestDynamicVector()
{
	DynamicVector<int> v1;
	DynamicVector<int> v4 = DynamicVector<int>(2);

	v1 = v1;

	v1.addElement(1);
	v1.addElement(2);
	v1.addElement(3);
	v1.addElement(4);
	assert(v1.getSize() == 4);
	assert(v1.getElement(0) == 1);
	assert(v1.getElement(1) == 2);

	v1.removeElement(1);
	assert(v1.getSize() == 3);

	v1.updateElement(0, 5);
	assert(v1.getElement(0) == 5);

	v1.setSize(2);
	assert(v1.getSize() == 2);

	DynamicVector<int> v2 = v1;
	DynamicVector<int> v3 = DynamicVector<int>(v1);
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
	AdminService ad2;

	datetime d1(12, 12, 12, 1999);
	Event e1("t1", "d1", d1, 1, "w");
	bool ok = ad2.HandleAddEvent(e1);
	assert(ok);

	ok = ad2.HandleAddEvent(e1);
	assert(!ok);

	Event e2("t1", "d1", d1, 1, "w");
	ok = ad2.HandleUpdateEvent(e2);
	assert(ok);

	datetime d2(12, 12, 12, 1998);
	Event e3("t2", "sdfads", d2, 1, "2");
	ok = ad2.HandleUpdateEvent(e3);
	assert(!ok);

	ok = ad2.HandleDeleteEvent("fdaads");
	assert(!ok);

	ok = ad2.HandleDeleteEvent("t1");
	assert(ok);

	assert(ad2.handleGetAll().getSize() == 0);

	ad2.HandleAddEvent(e1);
	ad2.HandleAddEvent(e3);
	DynamicVector<Event> v = ad2.HandleGetEventsByMonth(12);
	assert(v.getSize() == 2);

	e2 = ad2.handleGetEventByName("t1");
	assert(e2.getTitle() == "t1");

	v = ad2.handleFilterEvents(0);
	assert(v.getSize() == 2);

	v = ad2.handleGetAllSorted();
	assert(v.getSize() == 2);

}

void Test::TestRepository()
{
	Repository r;
	datetime d1(12, 12, 12, 1999);
	Event e1("t1", "d1", d1, 1, "w");

	r.addEvent(e1);
	DynamicVector<Event> v = r.getAll();
	assert(v.getSize() == 1);

	Event e2("t2", "d1", d1, 1, "w2");
	r.updateEvent(0, e2);
	v = r.getAll();
	Event e3 = v.getElement(0);
	assert(e3.getTitle() == "t2"); 

	try {
		r.getEventByName("t1");
	}
	catch (std::exception e) {
		assert(true);
	}

	r.deleteEvent(0);
	v = r.getAll();
	assert(v.getSize() == 0);

	r.addEventToUserList(e1);
	r.addEventToUserList(e2);
	v = r.getAllUserEvents();
	assert(v.getSize() == 2);

	r.deleteEventUserList(1);
	v = r.getAllUserEvents();
	assert(v.getSize() == 1);

	r.clearUserList();
	v = r.getAllUserEvents();
	assert(v.getSize() == 0);
}

void Test::TestUserService()
{
	UserService us;
	datetime d1(12, 12, 12, 1999);
	Event e1("t1", "d1", d1, 1, "w");

	bool ok = us.HandleAddEventToUserList(e1);
	assert(ok);
	ok = us.HandleAddEventToUserList(e1);
	assert(!ok);

	Event e2("t2", "d1", d1, 1, "w");
	us.HandleAddEventToUserList(e2);

	ok = us.HandleDeleteEventUserList("t2");
	assert(ok);
	ok = us.HandleDeleteEventUserList("fefafs");
	assert(!ok);

	DynamicVector<Event> v = us.HandleGetAllUserEvents();
	assert(v.getSize() == 1);

	us.handleClearUserList();
	v = us.HandleGetAllUserEvents();
	assert(v.getSize() == 0);
}