#include "file_type.h"

FileTypeCSV::FileTypeCSV(std::string path)
{
	fileName = path;
}

void FileTypeCSV::writeToFile(std::vector<Event> vec)
{
	std::ofstream fout(fileName);
	//if (fout.is_open() == false)
		//throw FileRepoException("File not open!");

	fout << "Title,Description,Date,Nr. of people,Link\n";
	for (auto a : vec)
		fout << a;

	fout.close();
}

FileTypeHTML::FileTypeHTML(std::string path)
{
	fileName = path;
}

void FileTypeHTML::writeToFile(std::vector<Event> vec)
{
	std::ofstream fout(fileName);
	//if (fout.is_open() == false)
		//throw FileRepoException("File not open!");

	fout << "<!DOCTYPE html>\n";
	fout << "<html>\n<head>\n<title>Your list of events</title>\n</head>\n<body>\n<table border = \"1\">\n";
	fout << "	<tr>\n";
	fout << "		<td>Title</td>\n";
	fout << "		<td>Description</td>\n";
	fout << "		<td>Date and time</td>\n";
	fout << "		<td>Nr. of people</td>\n";
	fout << "		<td>Link</td>\n";
	fout << "	</tr>\n";
	for (auto a : vec)
	{
		fout << "	<tr>\n";
		fout << "		<td>" << a.getTitle() << "</td>\n";
		fout << "		<td>" << a.getDescription() << "</td>\n";

		fout << "		<td>" << a.getDateTime().getDay() << '/' << a.getDateTime().getMonth() <<
			'/' << a.getDateTime().getYear() << ' ' << a.getDateTime().getHour() << "</td>\n";

		fout << "		<td>" << a.getNrOfPeople() << "</td>\n";
		fout << "		<td><a href=\"" << a.getLink() << "\">" << "Link" << "</a>" << "</td>\n";
		fout << "	</tr>\n";
	}
	
	fout << "</table>\n</body>\n</html>";

	fout.close();
}