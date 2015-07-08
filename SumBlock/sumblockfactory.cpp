#include "sumblockfactory.h"


SumBlockFactory::SumBlockFactory()
{
    a=7;
}

BlockInterface* SumBlockFactory::getNewBlock()
{
    return NULL;
}

QString SumBlockFactory::getBlockName()
{
   return "SumBlock";
}

QString SumBlockFactory::getBlockDescription()
{
    return "Block sums 2 input parameters (numbers, vectors or matrixs)";
}

void SumBlockFactory::init()
{

}

void SumBlockFactory::release()
{

}
