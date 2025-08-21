#include "validator.h"

EventExceptions::EventExceptions() :
	message {""}
{}

EventExceptions::EventExceptions(const std::string& mes) :
	message {mes}
{}

const char* EventExceptions::what()
{
	return message.c_str();
}

void EventValidator::validateEventTitle(const std::string& title)
{
	if (title.empty())
		throw EventExceptions("The title cannot be empty!!!");
}

void EventValidator::validateEventDesc(const std::string& desc)
{
	if (desc.empty())
		throw EventExceptions("The desc cannot be empty!!!");
}

void EventValidator::validateEventDate(const datetime& d)
{
	datetime d1 = d;
	if (d1.getDay() < 1 || d1.getDay() > 30)
		throw EventExceptions("The day is not correct!");

	if (d1.getMonth() < 1 || d1.getMonth() > 12)
		throw EventExceptions("The month is not correct!");

	if (d1.getYear() < 1900 || d1.getYear() > 2030)
		throw EventExceptions("The year is not correct!");

	if (d1.getHour() < 0 || d1.getHour() > 23)
		throw EventExceptions("The hour is not correct!");
}

void EventValidator::validateEventNrPeople(int p)
{
	if (p < 0)
		throw EventExceptions("The number of people can't be negative!!!");
}

void EventValidator::validateEventLink(const std::string& link)
{
	if (link.empty())
		throw EventExceptions("The link cannot be empty!!!");
}

