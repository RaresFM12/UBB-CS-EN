#pragma once

class datetime {
private:
	int day;
	int month;
	int year;

public:

	datetime();
	datetime(int day, int month, int year);
	~datetime();
	int getDay();
	int getMonth();
	int getYear();

	/// <summary>
	/// Assignement operator
	/// </summary>
	/// <param name="d">the date and time we want to copy</param>
	void operator=(const datetime& d);
};