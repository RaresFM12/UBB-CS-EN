#include "tableView.h"
#include <QColor>

MyModel::MyModel(QObject* parent)
	: QAbstractTableModel(parent) {
}

void MyModel::setEvents(const std::vector<Event>& movies) {
	beginResetModel();
	this->events = movies;
	endResetModel();
}

int MyModel::rowCount(const QModelIndex& parent) const {
	if (parent.isValid()) {
		return 0;
	}
	return static_cast<int>(events.size());
}

int MyModel::columnCount(const QModelIndex& parent) const {
	if (parent.isValid()) {
		return 0;
	}
	return 5;
}

QVariant MyModel::data(const QModelIndex& index, int role) const {
	if (!index.isValid() || index.row() < 0 || index.row() >= static_cast<int>(events.size())) {
		return QVariant();
	}
	if (role == Qt::DisplayRole) {
		Event ev = events[index.row()];
		switch (index.column()) {
		case 0: return QString::fromStdString(ev.getTitle());
		case 1: return QString::fromStdString(ev.getDescription());
		case 2: return QString::fromStdString(ev.getDateTime().toString());
		case 3: return ev.getNrOfPeople();
		case 4: return QString::fromStdString(ev.getLink());
		default: return QVariant();
		}
	}
    else if (role == Qt::BackgroundRole) {
		if (index.row() % 2 == 0) {
			return QColor(240, 240, 240); // Light gray for even rows
		}
		else {
			return QColor(255, 255, 255); // White for odd rows
		}
	}
	return QVariant();
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role != Qt::DisplayRole) {
		return QVariant();
	}
	else if (role == Qt::BackgroundRole) {
		return QColor(250, 250, 152);
	}

	if (orientation == Qt::Horizontal) {
		switch (section) {
		case 0: return QString("Title");
		case 1: return QString("Description");
		case 2: return QString("Date and time");
		case 3: return QString("Nr. of people");
		case 4: return QString("Link");
		default: return QVariant();
		}
	}
	return QVariant();
}