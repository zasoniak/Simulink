#ifndef DISPLAYBLOCK_H
#define DISPLAYBLOCK_H

#include <QObject>
#include <QVector>
#include <QtGui/QImage>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>

#include "blockinterface.h"
#include "blockview.h"
#include "blockfactoryinterface.h"
#include "displayblockproperties.h"


class DisplayBlock:
        public QObject,
        public BlockInterface
{
    Q_OBJECT
    Q_INTERFACES(BlockInterface)

public:
    explicit DisplayBlock(QObject *parent= 0);

    virtual void initialize() Q_DECL_OVERRIDE;
    virtual void run(Data* data=0, ConnectionInterface* source=0) Q_DECL_OVERRIDE;


    virtual bool connectInput(ConnectionInterface *) Q_DECL_OVERRIDE;
    virtual bool connectOutput(ConnectionInterface *) Q_DECL_OVERRIDE;
    virtual void disconnect(ConnectionInterface *) Q_DECL_OVERRIDE;

    virtual BlockPropertiesInterface* getProperties() Q_DECL_OVERRIDE;
    virtual QString getBlockName() Q_DECL_OVERRIDE;
    virtual QImage* getView() Q_DECL_OVERRIDE;

    virtual void openWindow() Q_DECL_OVERRIDE;

private:
    BlockPropertiesInterface* properties;
    const static QString blockName;
    QMap<ConnectionInterface*,Data*>inputData;
    QVector<ConnectionInterface*> inputs;

    //display data
    QDialog* dialog;
    QVBoxLayout* changingLayout;
    QVector<QTextEdit*> displayedData;
    QVector<QLabel*> displayedInputs;

    void refreshDialog();
    QString dataToText(Data* data);
};

#endif // DISPLAYBLOCK_H
