#include "propertieswidget.h"

PropertiesWidget::PropertiesWidget(QWidget *parent) : QWidget(parent)
{
    this->properties = NULL;
    this->propertiesTableView = new QTableView();
    this->propertiesModel = new PropertiesModel();



    //====== layout =============================
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(this->propertiesTableView);
//    this->propertiesTableView->setModel(this->propertiesModel);
}


void PropertiesWidget::loadProperties(BlockPropertiesInterface *properties)
{
    this->properties = properties;
    this->propertiesModel->setMap(this->properties->getProperties());
    this->propertiesTableView->setModel(this->propertiesModel);
    repaint();

}

void PropertiesWidget::unloadProperties()
{
    this->properties=NULL;
    this->propertiesModel->clearMap();
}


void saveProperties()
{

}





