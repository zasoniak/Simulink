#ifndef BLOCKINTERFACE
#define BLOCKINTERFACE

#include "connectorinterface.h"
#include "blockpropertiesinterface.h"

class BlockInterface
{
public:
    virtual ~BlockInterface() {}

    virtual void initialize()=0;
    virtual void run()=0;

    virtual void connect(ConnectorInterface *)=0;
    virtual void disconnect()=0;

    virtual BlockPropertiesInterface* getProperties()=0;
    virtual QString getBlockName()=0;
};


#define BlockInterface_iid "sony.simulink.BlockInterface"

Q_DECLARE_INTERFACE(BlockInterface, BlockInterface_iid)

#endif // BLOCKINTERFACE
