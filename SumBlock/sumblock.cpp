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


    Data* result;
    int status =1;
    int scalarsCounter=0;
    int vectorsCounter=0;
    int matrixesCounter=0;
    QVector<int> resultSize = QVector<int>();
    resultSize.append(1);
    int resultDimentions=1;
    QMap<ConnectionInterface*,Data*>::iterator it;
    for(it=this->inputData.begin();it!=this->inputData.end();it++)
    {
        if(status)
        {
            if((*it)->dimensions==1 &&(*it)->size.at(0)==1) //scalar
                scalarsCounter++;
            else if((*it)->dimensions==1)   //vector
            {
                vectorsCounter++;
                if(matrixesCounter) //there cannot be a matrix
                    status=0;

                if(vectorsCounter==1)
                {
                    resultDimentions=1;
                    resultSize.replace(0,(*it)->size.at(0));
                }
                else if((*it)->size.at(0)!=resultSize.at(0))
                    status=0;
            }
            else    //matrix
            {
                matrixesCounter++;
                if(vectorsCounter)  //there cannot be a vector
                    status=0;

                if(matrixesCounter==1)
                {
                    resultDimentions = 2;
                    resultSize.resize((*it)->size.size());
                    for(int dimensionSize=0; dimensionSize<(*it)->size.size();dimensionSize++)  //check size of matrixes
                    {
                         resultSize.replace(dimensionSize,(*it)->size.at(dimensionSize));
                    }
                }
                else
                {
                    if(resultSize.size()==(*it)->size.size())
                    {
                        for(int dimensionSize=0; dimensionSize<(*it)->size.size();dimensionSize++)  //check size of matrixes
                        {
                            if(resultSize.at(dimensionSize)!=(*it)->size.at(dimensionSize))
                                status=0;
                        }
                    }
                    else
                        status=0;
                }
            }
        }
    }

    //error             0
    //scalars           1
    //scalar + matrix   2
    //scalar + vector   3
    //vectors           4
    //matrixes          5

    if(status)
    {
        if(matrixesCounter&&scalarsCounter)
        {
            result = new Data(resultDimentions,resultSize, QVector<double>(resultSize.at(0)*resultSize.at(1)));
            status = 2;
        }
        else if(vectorsCounter&&scalarsCounter)
        {
            result = new Data(resultDimentions,resultSize, QVector<double>(resultSize.at(0)));
            status=3;
        }
        else if(scalarsCounter)
        {
            result = new Data(resultDimentions,resultSize, QVector<double>(1));
            status=1;
        }
        else if(matrixesCounter)
        {
            result = new Data(resultDimentions,resultSize, QVector<double>(resultSize.at(0)*resultSize.at(1)));
            status=5;
        }
        else if(vectorsCounter)
        {
            result = new Data(resultDimentions,resultSize, QVector<double>(resultSize.at(0)));
            status=4;
        }
    }

    switch (status) {
    case 1:
    {
        double value=0;
        for(it=this->inputData.begin();it!=this->inputData.end();it++)
        {
            value+=(*it)->dataArray.at(0);
        }
        result->dataArray.replace(0,value);
        return result;
        break;
    }
    case 2:
    case 3:
    {
        for(it=this->inputData.begin();it!=this->inputData.end();it++)
        {
            if((*it)->dimensions==1&&(*it)->size.at(0)==1)
            for(int i =0; i<result->dataArray.size();i++)
            {
                result->dataArray.replace(i,result->dataArray.at(i)+(*it)->dataArray.at(0));
            }
            else
            for(int i =0; i<result->dataArray.size();i++)
            {
                result->dataArray.replace(i,result->dataArray.at(i)+(*it)->dataArray.at(i));
            }
        }
        return result;
        break;
    }
    case 4:
    case 5:
    {
        for(it=this->inputData.begin();it!=this->inputData.end();it++)
        {
            for(int i =0; i<result->dataArray.size();i++)
            {
                result->dataArray.replace(i,result->dataArray.at(i)+(*it)->dataArray.at(i));
            }
        }
        return result;
        break;
    }
    default:
        return new Data();
        break;
    }

//    for(it=this->inputData.begin();it!=this->inputData.end()-1;it++)
//    {
//        if((*it)->dimensions==(*(it+1))->dimensions)
//        {
//            if((*it)->dimensions==1)    //scalar or vector
//            {
//                result = new Data(1,(*it)->size,QVector<double>());
//                QVector<double>::iterator value;
//                QVector<double>::iterator value2;
//                for(value=(*it)->dataArray.begin(),value2=(*(it+1))->dataArray.begin() ;value!=(*it)->dataArray.end()||value2!=(*(it+1))->dataArray.end();value++, value2++)
//                {
//                    result->dataArray.push_back((*value)+(*value2));
//                }
//            }
//            else
//                return new Data();
//            //matrix
//            //TODO:: calc dimension of result and result
//        }
//        else if((*it)->dimensions==1 &&(*it)->size.at(0)==1)    //first is scalar
//        {
//            QVector<double>::iterator value2;
//            for(value2=(*(it+1))->dataArray.begin() ;value2!=(*(it+1))->dataArray.end(); value2++)
//            {
//                result->dataArray.push_back((*value2)+(*it)->dataArray.at(0));
//            }
//        }
//        else if((*(it+1))->dimensions==1 &&(*(it+1))->size.at(0)==1)    //second is scalar
//        {
//            QVector<double>::iterator value;
//            for(value=(*it)->dataArray.begin();value!=(*it)->dataArray.end();value++)
//            {
//                result->dataArray.push_back((*value)+(*(it+1))->dataArray.at(0));
//            }
//        }
//        else
//            return new Data();
//    }
//    return result;
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


QVector<ConnectionInterface*> SumBlock::getConnections()
{
    QVector<ConnectionInterface*> connections = QVector<ConnectionInterface*>(this->inputs);
    QVector<ConnectionInterface*>::iterator it;
    for(it=this->outputs.begin();it!=this->outputs.end();it++)
    {
        connections.append(*it);
    }
    return connections;
}
