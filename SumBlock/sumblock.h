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
    virtual void run() Q_DECL_OVERRIDE;

    virtual bool connectInput(ConnectionInterface *) Q_DECL_OVERRIDE;
    virtual bool connectOutput(ConnectionInterface *) Q_DECL_OVERRIDE;
    virtual void disconnect(ConnectionInterface *) Q_DECL_OVERRIDE;

    virtual BlockPropertiesInterface* getProperties() Q_DECL_OVERRIDE;
    virtual QString getBlockName() Q_DECL_OVERRIDE;
    virtual QImage* getView() Q_DECL_OVERRIDE;

private:
    BlockPropertiesInterface* properties;
    const static QString blockName;
//    QVector<T1> inputData;
//    T1 outputData;
    QVector<ConnectionInterface*> inputs;
    QVector<ConnectionInterface*> outputs;

signals:

public slots:
};

#endif // SUMBLOCK_H
