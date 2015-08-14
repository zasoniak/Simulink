#include "sumblock.h"
const QString SumBlock::blockName = "SumBlock";

SumBlock::SumBlock(QObject *parent) : QObject(parent)
{
    this->inputs = QVector<ConnectionInterface*>();
    this->outputs = QVector<ConnectionInterface*>();
    this->properties = new SumBlockProperties();
}

void SumBlock::initialize()
{

}

void SumBlock::run()
{

}

bool SumBlock::connectInput(ConnectionInterface *connection)
{

}

bool SumBlock::connectOutput(ConnectionInterface *connection)
{

}

void SumBlock::disconnect(ConnectionInterface *connection)
{

}

BlockPropertiesInterface* SumBlock::getProperties()
{
    return this->properties;
}

QString SumBlock::getBlockName()
{
    return this->blockName;
}


QImage* SumBlock::getView()
{
    QImage *image = new QImage();
    if(image->load(":/images/sum.png"))
        return image;
    else
        return NULL;
}
