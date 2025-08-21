#include "file_repository.h"

FileRepository::FileRepository() :
	Repository(), filePath {""}
{}

FileRepository::FileRepository(std::string path) :
	Repository(), filePath {path}
{
	readFromFile();
}

FileRepository::FileRepository(std::string path, const std::string& userPath) :
	Repository(userPath), filePath {path}
{
	readFromFile();
}

FileRepository::~FileRepository()
{}

void FileRepository::readFromFile()
{
	std::ifstream fin(filePath);
	if (fin.is_open() == false)
		throw FileRepoException("File not open!");

	Event e;
	while (fin >> e)
		events.push_back(e);

	fin.close();
}

void FileRepository::writeToFile()
{
	std::ofstream fout(filePath);
	if (fout.is_open() == false)
		throw FileRepoException("File not open!");

	for (auto a : events)
		fout << a;

	fout.close();
}

bool FileRepository::addEvent(Event e)
{
	for (auto v : events)
		if (v.getTitle() == e.getTitle())
			throw InTheEventListException("This event is already in the list!!!");

	events.push_back(e);
	writeToFile();
	return true;
}

void FileRepository::deleteEvent(int pos)
{
	events.erase(events.begin() + pos);
	writeToFile();
}

void FileRepository::updateEvent(int pos, Event e)
{
	events[pos] = e;
	writeToFile();
}



