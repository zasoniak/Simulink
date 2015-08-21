#include "displayblock.h"
const QString DisplayBlock::blockName = "DisplayBlock";

DisplayBlock::DisplayBlock(QObject *parent) : QObject(parent)
{
    this->inputs = QVector<ConnectionInterface*>();
    this->inputData = QMap<ConnectionInterface*,Data*>();
    this->properties = new DisplayBlockProperties();

    this->dialog = new QDialog();
    this->dialog->setWindowTitle("Display");
    this->dialog->resize(320,240);
    changingLayout = new QVBoxLayout();
    this->dialog->setLayout(changingLayout);
}

void DisplayBlock::initialize()
{

}

void DisplayBlock::run(Data* data, ConnectionInterface* source)
{
    if(data)
    {
        this->inputData.insert(source,data);
        if(this->inputData.size()==this->inputs.size())
            this->refreshDialog();
    }
}

bool DisplayBlock::connectInput(ConnectionInterface *connection)
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

bool DisplayBlock::connectOutput(ConnectionInterface *connection)
{
    return false;
}

void DisplayBlock::disconnect(ConnectionInterface *connection)
{
    this->inputs.removeOne(connection);
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

void DisplayBlock::openWindow()
{
    dialog->show();
}

void DisplayBlock::refreshDialog()
{
        //clear dialog from previous settings
        QVector<QLabel*>::iterator channels;
        for(channels=this->displayedInputs.begin();channels!=this->displayedInputs.end();channels++)
        {
            delete *channels;
        }
        this->displayedInputs.clear();

        QVector<QTextEdit*>::iterator data;
        for(data=this->displayedData.begin();data!=this->displayedData.end();data++)
        {
            delete *data;
        }
        this->displayedData.clear();

        int i=1;
        QMap<ConnectionInterface*,Data*>::iterator it;
        for(it=this->inputData.begin();it!=this->inputData.end();it++)
        {
            QString name = "Channel number ";
            name.append(QString::number(i));
            name.append(":");
            QLabel* channelLabel = new QLabel(name);
            changingLayout->addWidget(channelLabel);
            this->displayedInputs.push_back(channelLabel);
            i++;

            QString value = dataToText(*it);
            QTextEdit* dataToDisplay = new QTextEdit();
            dataToDisplay->setPlainText(value);
            changingLayout->addWidget(dataToDisplay);
            this->displayedData.push_back(dataToDisplay);
        }
}


QString DisplayBlock::dataToText(Data* data)
{
    QString value = "";

    if(data->dimensions==1) //scalar or vector
    {
        QVector<double>::iterator it;
        for(it=data->dataArray.begin();it!=data->dataArray.end();it++)
        {
            value.append(QString::number(*it));
            value.append("\t");
        }
    }
    else if(data->dimensions==2)    //matrix
    {
        int columnCount = data->size.at(0);

        int columnCounter=0;
        QVector<double>::iterator it;
        for(it=data->dataArray.begin();it!=data->dataArray.end();it++)
        {
            if((!(columnCounter%columnCount))&&columnCounter)
            {
                value.append("\n");
            }
            value.append(QString::number(*it));
            value.append("\t");
            columnCounter++;
        }
    }
    else    // ? dunno how to display
    {
        value.append("Values cannot be displayed - to many dimensions");
    }
    return value;
}

QVector<ConnectionInterface*> DisplayBlock::getConnections()
{
    return this->inputs;
}
