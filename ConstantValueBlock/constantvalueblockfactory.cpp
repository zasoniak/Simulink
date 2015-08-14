#include "constantvalueblockfactory.h"


ConstantValueBlockFactory::ConstantValueBlockFactory()
{

}

BlockInterface* ConstantValueBlockFactory::getNewBlock()
{
    return NULL;
}

QString ConstantValueBlockFactory::getBlockName()
{
   return "ConstantValue";
}

QString ConstantValueBlockFactory::getBlockDescription()
{
    return "Provides a constant value specified in properties";
}

void ConstantValueBlockFactory::init()
{

}

void ConstantValueBlockFactory::release()
{

}

