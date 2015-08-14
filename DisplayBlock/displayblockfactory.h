#ifndef DISPLAYBLOCKFACTORY_H
#define DISPLAYBLOCKFACTORY_H

#include "displayblock_global.h"
#include "blockfactoryinterface.h"

#include "displayblock.h"

class DISPLAYBLOCKSHARED_EXPORT DisplayBlockFactory:
        public QObject,
        public BlockFactoryInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "sony.simulink.BlockFactoryInterface" FILE "displayblock.json")
    Q_INTERFACES(BlockFactoryInterface)


public:
    DisplayBlockFactory();
    virtual BlockInterface* getNewBlock() Q_DECL_OVERRIDE;
    virtual QString getBlockName() Q_DECL_OVERRIDE;
    virtual QString getBlockDescription() Q_DECL_OVERRIDE;

    virtual void init() Q_DECL_OVERRIDE;
    virtual void release() Q_DECL_OVERRIDE;
};

#endif // DISPLAYBLOCKFACTORY_H
