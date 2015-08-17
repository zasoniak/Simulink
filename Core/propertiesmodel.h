#ifndef PROPERTIESMODEL_H
#define PROPERTIESMODEL_H


#include <QAbstractTableModel>
#include <QMap>
#include <Qt>


class PropertiesModel:
        public QAbstractTableModel
{
    Q_OBJECT
public:

    enum MapRoles {
            KeyRole = Qt::UserRole + 1,
            ValueRole
        };

    explicit PropertiesModel(QObject *parent = 0);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    void setMap(QMap<QString, double>* newMap);
    inline void clearMap() {this->map = NULL;}

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const;


private:
    QMap<QString, double>* map;
};

#endif // PROPERTIESMODEL_H
