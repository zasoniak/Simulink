#include "constantvalueblock.h"

const QString ConstantValueBlock::blockName = "ConstantValue";
ConstantValueBlock::ConstantValueBlock(QObject *parent) : QObject(parent)
{
    this->outputs = QVector<ConnectionInterface*>();

    QVector<int> size = QVector<int>();
    size.push_back(5);

    QVector<double> values = QVector<double>();
    values.reserve(5);

    for(int i=0; i<5;i++)
    {
        double a = 100*rand()/RAND_MAX;
        values.push_back(a);
    }
    this->outputData = new Data(1,size,values);

    this->properties = new ConstantValueBlockProperties();


    this->dialog = new QDialog();
    QVBoxLayout *mainLayout = new QVBoxLayout();

    QLabel *colLabel = new QLabel("Columns number:");
    QSpinBox *columns = new QSpinBox();
    mainLayout->addWidget(colLabel);
    mainLayout->addWidget(columns);

    QLabel *rowLabel = new QLabel("Rows number:");
    QSpinBox *rows = new QSpinBox();
    mainLayout->addWidget(rowLabel);
    mainLayout->addWidget(rows);

    this->changingLayout = new QGridLayout();
    mainLayout->addLayout(this->changingLayout);

    this->dialog->setLayout(mainLayout);

    this->dialog->setWindowTitle("Constant Value");
    this->dialog->resize(320,240);


}

void ConstantValueBlock::initialize()
{

}

void ConstantValueBlock::run(Data* data, ConnectionInterface* source)
{
    QVector<ConnectionInterface*>::iterator it;
    for(it=this->outputs.begin();it!=this->outputs.end();it++)
    {
        (*it)->run(this->outputData);
    }
}

bool ConstantValueBlock::connectInput(ConnectionInterface *)
{
    return false;
}

bool ConstantValueBlock::connectOutput(ConnectionInterface *connection)
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

void ConstantValueBlock::disconnect(ConnectionInterface *)
{
    this->outputs.clear();
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

void ConstantValueBlock::refreshDialog()
{
    QVector<double>::iterator it;
    int column=0;
    for(it=this->outputData->dataArray.begin();it!=this->outputData->dataArray.end();it++ )
    {
        QLabel *label = new QLabel(QString::number(*it));
        this->changingLayout->addWidget(label,0,column);
        column++;
    }
}

void ConstantValueBlock::openWindow()
{
    refreshDialog();
    this->dialog->show();

}

