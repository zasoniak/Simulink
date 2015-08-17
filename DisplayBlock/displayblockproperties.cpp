#include "displayblockproperties.h"

DisplayBlockProperties::DisplayBlockProperties()
{
    this->properties = new QMap<QString, double>();

    QString name = "Precision";
    double value = 3;
    this->properties->insert(name, value);
}

QMap<QString, double>* DisplayBlockProperties::getProperties()
{
    return this->properties;
}

void DisplayBlockProperties::saveProperty(QString name, double value)
{
    if(this->properties->find(name)!=this->properties->end())
        this->properties->insert(name, value);
}

void DisplayBlockProperties::resetToDefaults()
{
    QString name = "Precision";
    double value = 3;
    this->properties->insert(name, value);
}

