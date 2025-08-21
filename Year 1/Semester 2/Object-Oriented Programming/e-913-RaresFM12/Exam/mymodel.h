#ifndef MYMODEL_H
#define MYMODEL_H
#include <QAbstractTableModel>
#include <QColor>
#include "volunteer.h"

class MyModel : public QAbstractTableModel {

private:
    std::vector<Volunteer> volunteers;

public:
    explicit MyModel(QObject* parent = nullptr);
    void setVolunteers(const std::vector<Volunteer>& vol);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

#endif // MYMODEL_H

