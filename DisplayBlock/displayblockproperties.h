#ifndef DISPLAYBLOCKPROPERTIES_H
#define DISPLAYBLOCKPROPERTIES_H


#include <QMap>
#include "blockpropertiesinterface.h"


class DisplayBlockProperties:
        public BlockPropertiesInterface
{
    Q_INTERFACES(BlockPropertiesInterface)

public:
    DisplayBlockProperties();

    virtual ~DisplayBlockProperties() {}

    virtual QMap<QString, double>* getProperties() Q_DECL_OVERRIDE;
    virtual void saveProperty(QString name, double value) Q_DECL_OVERRIDE;
    virtual void resetToDefaults() Q_DECL_OVERRIDE;

private:
    QMap<QString, double>* properties;

};

#endif // DISPLAYBLOCKPROPERTIES_H

