#include "constantvalueblock.h"

const QString ConstantValueBlock::blockName = "ConstantValue";
ConstantValueBlock::ConstantValueBlock(QObject *parent) : QObject(parent)
{

}

void ConstantValueBlock::initialize()
{

}

void ConstantValueBlock::run()
{

}

bool ConstantValueBlock::connectInput(ConnectionInterface *)
{

}

bool ConstantValueBlock::connectOutput(ConnectionInterface *)
{

}

void ConstantValueBlock::disconnect(ConnectionInterface *)
{

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

