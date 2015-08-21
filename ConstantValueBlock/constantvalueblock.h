#ifndef CONSTANTVALUE_H
#define CONSTANTVALUE_H


#include <QObject>
#include <QVector>
#include <QtGui/QImage>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QGridLayout>
#include <QSpinBox>
#include <QLineEdit>


#include "blockinterface.h"
#include "blockview.h"

#include  "constantvalueblockproperties.h"


class ConstantValueBlock:
        public QObject,
        public BlockInterface
{
    Q_OBJECT
    Q_INTERFACES(BlockInterface)
public:
    explicit ConstantValueBlock(QObject *parent = 0);

    virtual void initialize() Q_DECL_OVERRIDE;
    virtual void run(Data* data=0, ConnectionInterface* source=0) Q_DECL_OVERRIDE;

    virtual bool connectInput(ConnectionInterface *) Q_DECL_OVERRIDE;
    virtual bool connectOutput(ConnectionInterface *) Q_DECL_OVERRIDE;
    virtual void disconnect(ConnectionInterface *) Q_DECL_OVERRIDE;


    virtual QVector<ConnectionInterface*> getConnections() Q_DECL_OVERRIDE;
    virtual BlockPropertiesInterface* getProperties() Q_DECL_OVERRIDE;
    virtual QString getBlockName() Q_DECL_OVERRIDE;

    virtual QImage* getView() Q_DECL_OVERRIDE;
    virtual void openWindow() Q_DECL_OVERRIDE;

private:
    BlockPropertiesInterface* properties;
    const static QString blockName;
    Data* outputData;
    QVector<ConnectionInterface*> outputs;

    //display variables
    QDialog* dialog;
    QGridLayout* changingLayout;
    QSpinBox *columns, *rows;
    QVector<QLineEdit*> userInput;

    void refreshDialog();
    void getUserData();
private slots:
    void columnsNumberChanged(int value);
    void rowsNumberChanged(int value);
};

#endif // CONSTANTVALUE_H
