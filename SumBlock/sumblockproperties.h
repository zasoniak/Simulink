#ifndef SUMBLOCKPROPERTIES_H
#define SUMBLOCKPROPERTIES_H

#include <QMap>
#include "blockpropertiesinterface.h"

class SumBlockProperties :
        public BlockPropertiesInterface
{
    Q_INTERFACES(BlockPropertiesInterface)

public:
    SumBlockProperties();

    virtual ~SumBlockProperties() {}

    virtual QMap<QString, double>* getProperties() Q_DECL_OVERRIDE;
    virtual void saveProperty(QString name, double value) Q_DECL_OVERRIDE;
    virtual void resetToDefaults() Q_DECL_OVERRIDE;

private:
    QMap<QString, double>* properties;

};

#endif // SUMBLOCKPROPERTIES_H
