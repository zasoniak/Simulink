#include "propertiesmodel.h"

PropertiesModel::PropertiesModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    map = NULL;
}

int PropertiesModel::rowCount(const QModelIndex& parent) const
{
    if (map)
        return map->count();
    return 0;
}

int PropertiesModel::columnCount(const QModelIndex & parent) const
{
    return 2;
}

QVariant PropertiesModel::data(const QModelIndex& index, int role) const
{
    if (!map)
        return QVariant();
    if (index.row() < 0 ||
        index.row() >= map->count() ||
        role != Qt::DisplayRole) {
        return QVariant();
    }
    if (index.column() == 0)
        return map->keys().at(index.row());
    if (index.column() == 1)
        return map->values().at(index.row());
    return QVariant();
}

void PropertiesModel::setMap(QMap<QString, double>* newMap)
{
    this->map = newMap;
    QModelIndex topLeft = index(0,0);
    QModelIndex bottomRight = index(rowCount()-1, columnCount()-1);
    emit dataChanged(topLeft,bottomRight);
}


bool PropertiesModel::setData(const QModelIndex& index, const QVariant& value, int role)
{

}

Qt::ItemFlags PropertiesModel::flags(const QModelIndex & index) const
{

}
