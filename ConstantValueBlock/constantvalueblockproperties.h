#ifndef CONSTANTVALUEBLOCKPROPERTIES_H
#define CONSTANTVALUEBLOCKPROPERTIES_H


#include <QMap>
#include "blockpropertiesinterface.h"

class ConstantValueBlockProperties:
          public BlockPropertiesInterface
{
    Q_INTERFACES(BlockPropertiesInterface)
public:
    ConstantValueBlockProperties();
    virtual ~ConstantValueBlockProperties() {}

    virtual QMap<QString, double>* getProperties() Q_DECL_OVERRIDE;
    virtual void saveProperty(QString name, double value) Q_DECL_OVERRIDE;
    virtual void resetToDefaults() Q_DECL_OVERRIDE;

private:
    QMap<QString, double>* properties;

};

#endif // CONSTANTVALUEBLOCKPROPERTIES_H
