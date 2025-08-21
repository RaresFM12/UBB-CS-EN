#pragma once
#include "repository.h"
#include <fstream>

class FileRepository : public Repository {
private:
	std::string filePath;

public:
	FileRepository();
	FileRepository(std::string path);
	FileRepository(std::string path, const std::string& userPath);
	~FileRepository();

	bool addEvent(Event e) override;
	void deleteEvent(int pos) override;
	void updateEvent(int pos, Event e) override;

private:
	/// <summary>
	/// This function reads the input from file
	/// </summary>
	void readFromFile();

	/// <summary>
	/// This fuction writes in file
	/// </summary>
	void writeToFile();
};