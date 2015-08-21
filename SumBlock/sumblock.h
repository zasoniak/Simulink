#ifndef SUMBLOCK_H
#define SUMBLOCK_H

#include <QObject>
#include <QVector>
#include <QtGui/QImage>

#include "blockinterface.h"
#include "blockfactoryinterface.h"
#include "blockview.h"
#include "sumblockproperties.h"


class SumBlock :
        public QObject,
        public BlockInterface
{
    Q_OBJECT
    Q_INTERFACES(BlockInterface)
public:
    explicit SumBlock(QObject *parent = 0);

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
//    QVector<Data*> inputData;
    Data* outputData;
    QVector<ConnectionInterface*> inputs;
    QVector<ConnectionInterface*> outputs;
    QMap<ConnectionInterface*,Data*> inputData;


    Data* calculate();

signals:

public slots:
};

#endif // SUMBLOCK_H
