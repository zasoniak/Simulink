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
void SumBlock::run(Data* data, ConnectionInterface* source)
{
    if(data)
    {
        this->inputData.insert(source,data);
        if(this->inputData.size()==this->inputs.size())
        {
            //TODO: calc output here
            this->outputData = calculate();

            QVector<ConnectionInterface* >::iterator it;
            for(it=this->outputs.begin();it!=this->outputs.end();it++)
            {
                (*it)->run(this->outputData);
            }
        }
    }
}


Data* SumBlock::calculate()
{
    //only 1 input
    if(this->inputData.size()==1)
        return this->inputData.first();

    QMap<ConnectionInterface*,Data*>::iterator it;
    Data* result;

    //error             0
    //scalars           1
    //scalar + matrix   2
    //scalar + vector   3
    //vectors           4
    //matrixes          5


    int status =5;

    switch (status) {
    case 1:
    {
        double value=0;
        for(it=this->inputData.begin();it!=this->inputData.end();it++)
        {
            value+=(*it)->dataArray.at(0);
        }
        result = new Data();
        result->dataArray.replace(0,value);
        break;
    }
    case 2:
    case 3:
    {

        break;
    }
    case 4:
    case 5:
    {
        QVector<int> size = QVector<int>();
        size.insert(0,this->inputData.first()->size.at(0));
        size.insert(1,this->inputData.first()->size.at(1));
        QVector<double> values = QVector<double>(this->inputData.first()->dataArray.size(),0);

        for(it=this->inputData.begin();it!=this->inputData.end();it++)
        {
            for(int i =0; i<this->inputData.first()->dataArray.size();i++)
            {
                values.replace(i,values.at(i)+(*it)->dataArray.at(i));
            }
        }
        return new Data(2,size,values);
        break;
    }
    default:
        return new Data();
        break;
    }

    for(it=this->inputData.begin();it!=this->inputData.end()-1;it++)
    {
        if((*it)->dimensions==(*(it+1))->dimensions)
        {
            if((*it)->dimensions==1)    //scalar or vector
            {
                result = new Data(1,(*it)->size,QVector<double>());
                QVector<double>::iterator value;
                QVector<double>::iterator value2;
                for(value=(*it)->dataArray.begin(),value2=(*(it+1))->dataArray.begin() ;value!=(*it)->dataArray.end()||value2!=(*(it+1))->dataArray.end();value++, value2++)
                {
                    result->dataArray.push_back((*value)+(*value2));
                }
            }
            else
                return new Data();
            //matrix
            //TODO:: calc dimension of result and result
        }
        else if((*it)->dimensions==1 &&(*it)->size.at(0)==1)    //first is scalar
        {
            QVector<double>::iterator value2;
            for(value2=(*(it+1))->dataArray.begin() ;value2!=(*(it+1))->dataArray.end(); value2++)
            {
                result->dataArray.push_back((*value2)+(*it)->dataArray.at(0));
            }
        }
        else if((*(it+1))->dimensions==1 &&(*(it+1))->size.at(0)==1)    //second is scalar
        {
            QVector<double>::iterator value;
            for(value=(*it)->dataArray.begin();value!=(*it)->dataArray.end();value++)
            {
                result->dataArray.push_back((*value)+(*(it+1))->dataArray.at(0));
            }
        }
        else
            return new Data();
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
        connection->connectOutput(this);
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
        connection->connectInput(this);
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
