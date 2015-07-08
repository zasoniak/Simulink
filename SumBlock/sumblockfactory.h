#ifndef SUMBLOCKFACTORY_H
#define SUMBLOCKFACTORY_H

#include <QObject>
#include "sumblock_global.h"
#include "blockfactoryinterface.h"

class SUMBLOCKSHARED_EXPORT SumBlockFactory:
        public QObject,
        public BlockFactoryInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "sony.simulink.BlockFactoryInterface" FILE "sumblock.json")
    Q_INTERFACES(BlockFactoryInterface)

public:
    SumBlockFactory();
    virtual BlockInterface* getNewBlock() Q_DECL_OVERRIDE;
    virtual QString getBlockName() Q_DECL_OVERRIDE;
    virtual QString getBlockDescription() Q_DECL_OVERRIDE;

    virtual void init() Q_DECL_OVERRIDE;
    virtual void release() Q_DECL_OVERRIDE;
private:
    int a;
};

#endif // SUMBLOCKFACTORY_H
