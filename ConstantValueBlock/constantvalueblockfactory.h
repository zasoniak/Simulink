#ifndef CONSTANTVALUEBLOCKFACTORY_H
#define CONSTANTVALUEBLOCKFACTORY_H

#include <QObject>
#include "constantvalueblock_global.h"
#include "blockfactoryinterface.h"

class CONSTANTVALUEBLOCKSHARED_EXPORT ConstantValueBlockFactory:
        public QObject,
        public BlockFactoryInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "sony.simulink.ConstantValueBlockFactory" FILE "constantvalue.json")
    Q_INTERFACES(BlockFactoryInterface)

public:
    ConstantValueBlockFactory();

    virtual BlockInterface* getNewBlock() Q_DECL_OVERRIDE;
    virtual QString getBlockName() Q_DECL_OVERRIDE;
    virtual QString getBlockDescription() Q_DECL_OVERRIDE;

    virtual void init() Q_DECL_OVERRIDE;
    virtual void release() Q_DECL_OVERRIDE;
};

#endif // CONSTANTVALUEBLOCKFACTORY_H
