#include "sumblock.h"
const QString SumBlock::blockName = "SumBlock";

SumBlock::SumBlock(QObject *parent) : QObject(parent)
{
    this->inputs = QVector<ConnectionInterface*>();
    this->outputs = QVector<ConnectionInterface*>();
    this->properties = new SumBlockProperties();
    this->inputData = QMap<ConnectionInterface*,Data*>();
}

/**
 * @brief SumBlock::initialize
 * prepares block to next calculation
 */
void SumBlock::initialize()
{
    this->inputData.clear();
}

/**
 * @brief SumBlock::run
 * basic computation operation provided by block
 *
 * sums all input data into 1 output value
 *
 * @param data - data from previous step
 * @param source - source of data
 */
void SumBlock::run(Data* data=0, ConnectionInterface* source)
{
    if(data)
    {
        this->inputData.insert(source,data);
        if(this->inputData.size()==this->inputs.size())
        {
            //TODO: calc output here
            this->outputData = calculate();

            QVector<ConnectionInterface*>::iterator it;
            for(it=this->outputs.begin();it!=this->outputs.end();it++)
            {
                (*it)->run(this->outputData);
            }
        }
    }
}


Data* SumBlock::calculate()
{
    QMap<ConnectionInterface*,Data*>::iterator it;
    Data* result;
    for(it=this->inputData.begin();it!=this->inputData.end()-1;it++)
    {
        if((*it)->dimensions==(*(it+1))->dimensions)
        {
            //TODO:: calc dimension of result and result
        }
        else
            return NULL;
    }
    return result;
}

/**
 * @brief SumBlock::connectInput
 * connects new input
 * if connection exists nothing happens
 * @param connection - new input
 * @return
 */
bool SumBlock::connectInput(ConnectionInterface *connection)
{
    if(!this->inputs.contains(connection))
    {
        this->inputs.push_back(connection);
        return true;
    }
    else
        return false;
}

/**
 * @brief SumBlock::connectOutput
 * connects new output
 * if connection exists nothing happens
 * @param connection - new output
 * @return
 */
bool SumBlock::connectOutput(ConnectionInterface *connection)
{
    if(!this->outputs.contains(connection))
    {
        this->outputs.push_back(connection);
        return true;
    }
    else
        return false;
}

/**
 * @brief SumBlock::disconnect
 * disconnect block from connection
 * @param connection
 */
void SumBlock::disconnect(ConnectionInterface *connection)
{
    this->inputs.removeOne(connection);
    this->outputs.removeOne(connection);
}

/**
 * @brief SumBlock::getProperties
 * @return properties
 */
BlockPropertiesInterface* SumBlock::getProperties()
{
    return this->properties;
}

/**
 * @brief SumBlock::getBlockName
 * @return name of the block (SumBlock)
 */
QString SumBlock::getBlockName()
{
    return this->blockName;
}

/**
 * @brief SumBlock::getView
 * @return icon of the block
 */
QImage* SumBlock::getView()
{
    QImage *image = new QImage();
    if(image->load(":/images/sum.png"))
        return image;
    else
        return NULL;
}

/**
 * @brief SumBlock::openWindow
 * there is no window to open
 */
void SumBlock::openWindow()
{

}
