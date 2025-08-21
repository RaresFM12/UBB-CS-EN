#pragma once
#include <iostream>

class NrPeopleException : public std::exception {
private:
	std::string message;

public:
	NrPeopleException();
	NrPeopleException(const std::string& mes);
	const char* what();
};

class NotInAdminListException : public std::exception {
private:
	std::string message;

public:
	NotInAdminListException();
	NotInAdminListException(const std::string& mes);
	const char* what();
};

class InTheUserListException : public std::exception {
private:
	std::string message;

public:
	InTheUserListException();
	InTheUserListException(const std::string& mes);
	const char* what();
};

class InTheEventListException : public std::exception {
private:
	std::string message;

public:
	InTheEventListException();
	InTheEventListException(const std::string& mes);
	const char* what();
};

class FileRepoException : public std::exception {
private:
	std::string message;

public:
	FileRepoException();
	FileRepoException(const std::string& mes);
	const char* what();
};