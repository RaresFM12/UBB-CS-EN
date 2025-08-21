#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "exceptions.h"
#include "event.h"

class FileType {
protected:
	std::string fileName;

public:

	virtual ~FileType() = default;
	virtual void writeToFile(std::vector<Event> vec) = 0;
};

class FileTypeCSV : public FileType {
public:
	FileTypeCSV(std::string path);
	void writeToFile(std::vector<Event> vec) override;
};

class FileTypeHTML : public FileType {
public:
	FileTypeHTML(std::string path);
	void writeToFile(std::vector<Event> vec) override;
};