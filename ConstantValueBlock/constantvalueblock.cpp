#include "constantvalueblock.h"

const QString ConstantValueBlock::blockName = "ConstantValue";
ConstantValueBlock::ConstantValueBlock(QObject *parent) : QObject(parent)
{
    this->outputs = QVector<ConnectionInterface*>();
    this->userInput = QVector<QLineEdit*>();

    this->outputData = new Data();

//    ///asdadasdasasdasdasd
//    QVector<int> size = QVector<int>();
//    size.push_back(5);

//    QVector<double> values = QVector<double>();
//    values.reserve(5);

//    for(int i=0; i<5;i++)
//    {
//        double a = 100*rand()/RAND_MAX;
//        values.push_back(a);
//    }
//    this->outputData = new Data(1,size,values);
//    //asdasdasdadasdasdasd

    this->properties = new ConstantValueBlockProperties();


    this->dialog = new QDialog();
    QGridLayout *mainLayout = new QGridLayout();

    QLabel *colLabel = new QLabel("Columns number:");
    columns = new QSpinBox();
    columns->setMinimum(1);
    columns->setValue(3);
    connect(columns, SIGNAL(valueChanged(int)),this, SLOT(columnsNumberChanged(int)));
    mainLayout->addWidget(colLabel,0,0);
    mainLayout->addWidget(columns,0,1);

    QLabel *rowLabel = new QLabel("Rows number:");
    rows = new QSpinBox();
    rows->setMinimum(1);
    rows->setValue(3);
    connect(rows, SIGNAL(valueChanged(int)),this, SLOT(rowsNumberChanged(int)));
    mainLayout->addWidget(rowLabel,1,0);
    mainLayout->addWidget(rows,1,1);

    this->changingLayout = new QGridLayout();
    mainLayout->addLayout(this->changingLayout,2,0,2,2);

    this->dialog->setLayout(mainLayout);

    this->dialog->setWindowTitle("Constant Value");
    this->dialog->resize(320,240);

    this->refreshDialog();

}

void ConstantValueBlock::initialize()
{

}

void ConstantValueBlock::run(Data* data, ConnectionInterface* source)
{
    this->getUserData();
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
    //save previous data
//    getUserData();
    //clean layout
    QVector<QLineEdit*>::iterator oldData;
    for(oldData=this->userInput.begin();oldData!=this->userInput.end();oldData++)
    {
        delete *oldData;
    }
    this->userInput.clear();
    int col =0;
    int row =0;


    for(int i=0; i<this->columns->value()*this->rows->value();i++)
    {
        QLineEdit* edit = new QLineEdit("0");
        this->userInput.append(edit);
        edit->setValidator(new QDoubleValidator());
        this->changingLayout->addWidget(edit,row,col);
        col++;
        if(!(col%this->columns->value()))
        {
            row++;
            col=0;
        }
    }

}

void ConstantValueBlock::openWindow()
{
    this->dialog->show();
}


void ConstantValueBlock::getUserData()
{
    this->outputData->size.clear();
    this->outputData->size.append(this->columns->value());
    if(this->rows->value()==1)
        this->outputData->dimensions=1;
    else
    {
        this->outputData->dimensions=2;
        this->outputData->size.append(this->rows->value());
    }

    this->outputData->dataArray.clear();

    for(int i=0; i<this->columns->value()*this->rows->value();i++)
    {
        this->outputData->dataArray.append(this->userInput.at(i)->text().toDouble());
    }

}

void ConstantValueBlock::columnsNumberChanged(int value)
{
    refreshDialog();
}

void ConstantValueBlock::rowsNumberChanged(int value)
{
    refreshDialog();
}

QVector<ConnectionInterface*> ConstantValueBlock::getConnections()
{
    return this->outputs;
}

