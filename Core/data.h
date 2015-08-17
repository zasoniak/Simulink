#ifndef DATA_H
#define DATA_H

#include <QVector>

class Data
{
public:
    inline Data()
    {
        this->dimensions = 1;
        this->size = QVector<int>(1);
        this->dataArray = QVector<double>(1);
    }

    inline Data(int dimensions,QVector<int> size, QVector<double>dataArray)
    {
        this->dimensions=dimensions;
        this->size=size;
        this->dataArray=dataArray;
    }

    virtual ~Data(){}

    int dimensions;
    QVector<int> size;
    QVector<double> dataArray;
};

#endif // DATA_H
