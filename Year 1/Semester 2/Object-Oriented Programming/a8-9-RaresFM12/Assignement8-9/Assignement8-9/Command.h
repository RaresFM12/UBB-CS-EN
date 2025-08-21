#pragma once
//#include <Repository.h>
//#include <FileRepository.h>
//#include <CSVRepo.h>
//#include <HTMLRepo.h>
#include "event.h"
#include "repository.h"
#include "file_repository.h"
#include <vector>
#include <stack>

class Command {
protected:
	std::vector<Event> events;
	Repository* evRepo;
	Repository* attendRepo;

public:
	Command() {
		this->evRepo = nullptr;
		this->attendRepo = nullptr;
	}
	virtual void undo() = 0;
	virtual void redo() = 0;
	virtual ~Command() {};
};

class AddCommand : public Command {
public:
	AddCommand(Repository* movieRepo, Event ev);
	void undo() override;
	void redo() override;
	~AddCommand() {};
};

class DeleteCommand : public Command {
public:
	DeleteCommand(Repository* movieRepo, Event ev);
	void undo() override;
	void redo() override;
	~DeleteCommand() {};
};

class UpdateCommand : public Command {
public:
	UpdateCommand(Repository* movieRepo, Event oldEv, Event newEv);
	void undo() override;
	void redo() override;
	~UpdateCommand() {};
};

class UndoRedoService {
private:
	std::stack<Command*> undoStack;
	std::stack<Command*> redoStack;
public:
	UndoRedoService();
	void addCommand(Command* lastCommand);
	void undo();
	void redo();
	~UndoRedoService() {};
};


