#include "displayblock.h"
const QString DisplayBlock::blockName = "DisplayBlock";

DisplayBlock::DisplayBlock(QObject *parent) : QObject(parent)
{
    this->inputs = QVector<ConnectionInterface*>();
    this->outputs = QVector<ConnectionInterface*>();
    //this->properties = new ();
}

void DisplayBlock::initialize()
{

}

void DisplayBlock::run()
{

}

bool DisplayBlock::connectInput(ConnectionInterface *connection)
{

}

bool DisplayBlock::connectOutput(ConnectionInterface *connection)
{

}

void DisplayBlock::disconnect(ConnectionInterface *connection)
{

}

BlockPropertiesInterface* DisplayBlock::getProperties()
{
    return this->properties;
}

QString DisplayBlock::getBlockName()
{
    return DisplayBlock::blockName;
}


QImage* DisplayBlock::getView()
{
    QImage *image = new QImage();
    if(image->load(":/images/display.png"))
        return image;
    else
        return NULL;
}
