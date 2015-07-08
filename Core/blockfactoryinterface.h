#ifndef BLOCKFACTORYINTERFACE
#define BLOCKFACTORYINTERFACE


#include <QObject>

#include "blockinterface.h"

class BlockFactoryInterface
{
public:
    virtual ~BlockFactoryInterface() {}

    virtual BlockInterface* getNewBlock() = 0;
    virtual QString getBlockName() = 0;
    virtual QString getBlockDescription() = 0;

    virtual void init() =0;
    virtual void release()=0;


};


#define BlockFactoryInterface_iid "sony.simulink.BlockFactoryInterface"
Q_DECLARE_INTERFACE(BlockFactoryInterface, BlockFactoryInterface_iid)

#endif // BLOCKFACTORYINTERFACE

