#include "displayblockfactory.h"


DisplayBlockFactory::DisplayBlockFactory()
{
}
BlockInterface* DisplayBlockFactory::getNewBlock()
{
    return new DisplayBlock();
}

QString DisplayBlockFactory::getBlockName()
{
   return "DisplayBlock";
}

QString DisplayBlockFactory::getBlockDescription()
{
    return "Block displays provided input values";
}

void DisplayBlockFactory::init()
{

}

void DisplayBlockFactory::release()
{

}
