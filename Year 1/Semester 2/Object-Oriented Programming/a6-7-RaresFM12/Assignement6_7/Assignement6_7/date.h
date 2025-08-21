#pragma once

class datetime {
private:
	int hour;
	int day;
	int month;
	int year;

public:

	datetime();
	datetime(int hour, int day, int month, int year);
	~datetime();
	int getHour();
	int getDay();
	int getMonth();
	int getYear();
	std::string toString();

	/// <summary>
	/// Assignement operator
	/// </summary>
	/// <param name="d">the date and time we want to copy</param>
	void operator=(const datetime& d);
};