#ifndef BLOCKINTERFACE
#define BLOCKINTERFACE

#include "connectioninterface.h"
#include "blockpropertiesinterface.h"
#include <QtGui/QImage>

class BlockView;

class BlockInterface
{
public:
    virtual ~BlockInterface() {}

    virtual void initialize()=0;
    virtual void run()=0;

    virtual bool connectInput(ConnectionInterface *) =0;
    virtual bool connectOutput(ConnectionInterface *) =0;
    virtual void disconnect(ConnectionInterface *) =0;

    virtual BlockPropertiesInterface* getProperties()=0;
    virtual QString getBlockName()=0;
    virtual QImage* getView()=0;
};


#define BlockInterface_iid "sony.simulink.BlockInterface"

Q_DECLARE_INTERFACE(BlockInterface, BlockInterface_iid)

#endif // BLOCKINTERFACE
