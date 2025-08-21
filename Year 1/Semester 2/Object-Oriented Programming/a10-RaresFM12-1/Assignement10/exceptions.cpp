#include "exceptions.h"

NrPeopleException::NrPeopleException() :
	message{ "" }
{}

NrPeopleException::NrPeopleException(const std::string& mes) :
	message{ mes }
{}

const char* NrPeopleException::what()
{
	return message.c_str();
}

NotInAdminListException::NotInAdminListException() :
	message {""}
{}

NotInAdminListException::NotInAdminListException(const std::string& mes) :
	message {mes}
{}

const char* NotInAdminListException::what()
{
	return message.c_str();
}

InTheUserListException::InTheUserListException() :
	message{ "" }
{}

InTheUserListException::InTheUserListException(const std::string& mes) :
	message {mes}
{}

const char* InTheUserListException::what()
{
	return message.c_str();
}

InTheEventListException::InTheEventListException() :
	message {""}
{}

InTheEventListException::InTheEventListException(const std::string& mes) :
	message {mes}
{}

const char* InTheEventListException::what()
{
	return message.c_str();
}

FileRepoException::FileRepoException() :
	message {""}
{}

FileRepoException::FileRepoException(const std::string& mes) :
	message{ mes }
{}

const char* FileRepoException::what()
{
	return message.c_str();
}
