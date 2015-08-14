#ifndef SUMBLOCKPROPERTIES_H
#define SUMBLOCKPROPERTIES_H

#include <QMap>
#include "blockpropertiesinterface.h"

class SumBlockProperties : public BlockPropertiesInterface
{
public:
    SumBlockProperties();


    virtual QMap<QString, double> getProperties() Q_DECL_OVERRIDE;
    virtual void saveProperty(QString name, double value) Q_DECL_OVERRIDE;
    virtual void resetToDefaults() Q_DECL_OVERRIDE;


};

#endif // SUMBLOCKPROPERTIES_H
