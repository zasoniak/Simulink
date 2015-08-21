#include "toolbox.h"


Toolbox::Toolbox(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    this->newConnectionButton = new QPushButton(tr("&New connection"),this);
    connect(newConnectionButton, SIGNAL(clicked()), this, SLOT(addNewConnection()));


    this->deleteConnectionButton = new QPushButton(tr("&Delete connection"),this);
    connect(deleteConnectionButton, SIGNAL(clicked()),this, SLOT(deleteConnection()));

    this->deleteBlockButton = new QPushButton(tr("&Delete block"), this);
    connect(deleteBlockButton, SIGNAL(clicked()),this,SLOT(deleteBlock()));


    this->blockList = new QListView();
    connect(blockList,SIGNAL(clicked(const QModelIndex)),this,SLOT(blockSelected(QModelIndex)));

    this->blockListModel = new QStringListModel(this);
    blockList->setModel(blockListModel);


    layout->addWidget(newConnectionButton);
    layout->addWidget(deleteConnectionButton);
    layout->addWidget(deleteBlockButton);
    layout->addWidget(blockList);


    this->setAutoFillBackground( true );
    QPalette palette = this->palette();
    palette.setColor(QPalette::Background, Qt::gray);
    this->setPalette(palette);
}

void Toolbox::addNewBlock(QString blockName)
{
    this->blockListModel->insertRow(this->blockListModel->rowCount());
    QModelIndex index = this->blockListModel->index(this->blockListModel->rowCount()-1);
    this->blockListModel->setData(index,blockName);
}

void Toolbox::reloadBlockList(QStringList blockNames)
{
    this->blockListModel->setStringList(blockNames);
}


void Toolbox::blockSelected(QModelIndex index)
{
    notifyObservers(VALUE_TYPE_BLOCK_NAME,index.data().toString());
    this->blockList->clearSelection();
}


void Toolbox::addNewConnection()
{
    notifyObservers(VALUE_TYPE_NEW_CONNECTION,"");
}

void Toolbox::deleteConnection()
{
    notifyObservers(VALUE_TYPE_DELETE_CONNECTION, "");
}

void Toolbox::deleteBlock()
{
    notifyObservers(VALUE_TYPE_DELETE_BLOCK, "");
}
