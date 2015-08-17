#include "constantvalueblock.h"

const QString ConstantValueBlock::blockName = "ConstantValue";
ConstantValueBlock::ConstantValueBlock(QObject *parent) : QObject(parent)
{
    this->outputs = QVector<ConnectionInterface*>();
    this->properties = new ConstantValueBlockProperties();
}

void ConstantValueBlock::initialize()
{

}

void ConstantValueBlock::run(Data* data, ConnectionInterface* source)
{
    QVector<ConnectionInterface*>::iterator it;
    for(it=this->outputs.begin();it!=this->outputs.end();it++)
    {
        (*it)->run(data);
    }
}

bool ConstantValueBlock::connectInput(ConnectionInterface *)
{
    return false;
}

bool ConstantValueBlock::connectOutput(ConnectionInterface *output)
{
    if(output)
    {
        this->outputs.push_back(output);
        return true;
    }
    else
        return false;
}

void ConstantValueBlock::disconnect(ConnectionInterface *)
{
    this->outputs.clear();
}

BlockPropertiesInterface* ConstantValueBlock::getProperties()
{
    return this->properties;
}

QString ConstantValueBlock::getBlockName()
{
    return this->blockName;
}


QImage* ConstantValueBlock::getView()
{
    QImage *image = new QImage();
    if(image->load(":/images/constant.png"))
        return image;
    else
        return NULL;
}


void ConstantValueBlock::openWindow()
{

}

