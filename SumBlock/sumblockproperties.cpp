#include "sumblockproperties.h"

SumBlockProperties::SumBlockProperties()
{
    this->properties = new QMap<QString, double>();

    QString name = "Number of inputs";
    double value = 2;
    this->properties->insert(name, value);

}

QMap<QString, double>* SumBlockProperties::getProperties()
{
    return this->properties;
}

void SumBlockProperties::saveProperty(QString name, double value)
{
    if(this->properties->find(name)!=this->properties->end())
        this->properties->insert(name, value);
}

void SumBlockProperties::resetToDefaults()
{
    QString name = "Number of inputs";
    double value = 2;
    this->properties->insert(name, value);
}

