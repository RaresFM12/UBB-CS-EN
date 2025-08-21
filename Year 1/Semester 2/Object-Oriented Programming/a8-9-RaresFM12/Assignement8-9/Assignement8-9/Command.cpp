#include "Command.h"
#include <cstring>

using std::string;

AddCommand::AddCommand(Repository* evRepo, Event ev) {
	this->evRepo = evRepo;
	events.push_back(ev);
}

void AddCommand::undo() {
	Event movieToBeDeleted = events.back();
	string title = movieToBeDeleted.getTitle();
	std::vector<Event> vec = evRepo->getAll();

	int pos = -1;
	for (int i = 0; i < vec.size(); ++i)
		if (vec[i].getTitle() == title)
			pos = i;

	this->evRepo->deleteEvent(pos);
}

void AddCommand::redo() {
	Event movieToBeAdded = events.back();
	this->evRepo->addEvent(movieToBeAdded);
}

DeleteCommand::DeleteCommand(Repository* evRepo, Event movie) {
	this->evRepo = evRepo;
	events.push_back(movie);
}

void DeleteCommand::undo() {
	Event evToBeAdded = events.back();
	this->evRepo->addEvent(evToBeAdded);
}

void DeleteCommand::redo() {
	Event movieToBeDeleted = events.back();
	string title = movieToBeDeleted.getTitle();
	std::vector<Event> vec = evRepo->getAll();

	int pos = -1;
	for (int i = 0; i < vec.size(); ++i)
		if (vec[i].getTitle() == title)
			pos = i;

	this->evRepo->deleteEvent(pos);
}

UpdateCommand::UpdateCommand(Repository* movieRepo, Event oldMovie, Event newMovie) {
	this->evRepo = movieRepo;
	events.push_back(oldMovie);
	events.push_back(newMovie);
}

void UpdateCommand::undo() {
	Event oldEv = events[0];
	string title = oldEv.getTitle();
	std::vector<Event> vec = evRepo->getAll();

	int pos = -1;
	for (int i = 0; i < vec.size(); ++i)
		if (vec[i].getTitle() == title)
			pos = i;

	this->evRepo->updateEvent(pos, oldEv);
}

void UpdateCommand::redo() {
	Event newEv = events[1];
	string title = newEv.getTitle();
	std::vector<Event> vec = evRepo->getAll();

	int pos = -1;
	for (int i = 0; i < vec.size(); ++i)
		if (vec[i].getTitle() == title)
			pos = i;

	this->evRepo->updateEvent(pos, newEv);
}

UndoRedoService::UndoRedoService() {}

void UndoRedoService::addCommand(Command* lastCommand) {
	undoStack.push(lastCommand);
	while (!redoStack.empty()) {
		redoStack.pop();
	}
}

void UndoRedoService::undo() {
	if (undoStack.empty()) {
		throw std::exception("No commands to undo");
	}
	Command* lastCommand = undoStack.top();
	undoStack.pop();
	lastCommand->undo();
	redoStack.push(lastCommand);
}

void UndoRedoService::redo() {
	if (redoStack.empty()) {
		throw std::exception("No commands to redo");
	}
	Command* lastCommand = redoStack.top();
	redoStack.pop();
	lastCommand->redo();
	undoStack.push(lastCommand);
}