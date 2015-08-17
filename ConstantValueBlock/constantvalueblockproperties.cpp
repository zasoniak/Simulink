#include "constantvalueblockproperties.h"

ConstantValueBlockProperties::ConstantValueBlockProperties()
{
    this->properties = new QMap<QString, double>();

    QString name = "Value";
    double value = 7;
    this->properties->insert(name, value);
}

QMap<QString, double>* ConstantValueBlockProperties::getProperties()
{
    return this->properties;
}

void ConstantValueBlockProperties::saveProperty(QString name, double value)
{
    if(this->properties->find(name)!=this->properties->end())
        this->properties->insert(name, value);
}

void ConstantValueBlockProperties::resetToDefaults()
{
    QString name = "Value";
    double value = 7;
    this->properties->insert(name, value);
}

