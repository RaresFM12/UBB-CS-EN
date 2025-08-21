#include "mymodel.h"
#include <QVector>

MyModel::MyModel(QObject* parent):
    QAbstractTableModel(parent)
{}

void MyModel::setVolunteers(const std::vector<Volunteer>& vol) {
    beginResetModel();
    this->volunteers = vol;
    endResetModel();
}

int MyModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return static_cast<int>(volunteers.size());
}

int MyModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return 2;
}

QVariant MyModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= static_cast<int>(volunteers.size())) {
        return QVariant();
    }
    if (role == Qt::DisplayRole) {
        Volunteer vol = volunteers[index.row()];
        switch (index.column()) {
        case 0: return QString::fromStdString(vol.getName());
        case 1: return QString::fromStdString(vol.getEmail());
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
        case 0: return QString("Name");
        case 1: return QString("Email");
        case 2: return QString("Interests");
        default: return QVariant();
        }
    }
    return QVariant();
}
