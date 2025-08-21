#pragma once
#include <iostream>
#include "date.h"

class EventExceptions : public std::exception {
private:
	std::string message;

public:
	EventExceptions();
	EventExceptions(const std::string& mes);
	const char* what();
};

class EventValidator {
public:
	static void validateEventTitle(const std::string& title);
	static void validateEventDesc(const std::string& desc);
	static void validateEventDate(const datetime& d);
	static void validateEventNrPeople(int p);
	static void validateEventLink(const std::string& link);
};