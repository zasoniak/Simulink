#ifndef PROPERTIESWIDGET_H
#define PROPERTIESWIDGET_H

#include <QObject>
#include <QWidget>
#include <QTableView>
#include <QHBoxLayout>




#include "blockpropertiesinterface.h"

#include "propertiesmodel.h"

class PropertiesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PropertiesWidget(QWidget *parent = 0);
    void loadProperties(BlockPropertiesInterface* properties);
    void unloadProperties();
private:
    void saveProperties();

    BlockPropertiesInterface *properties;
    QTableView* propertiesTableView;
    PropertiesModel *propertiesModel;

signals:

public slots:
};

#endif // PROPERTIESWIDGET_H
