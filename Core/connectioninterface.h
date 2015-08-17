#ifndef CONNECTIONINTERFACE
#define CONNECTIONINTERFACE

#include <QObject>
#include "data.h"
class BlockInterface;

class ConnectionInterface
{
public:
    virtual ~ConnectionInterface() {}
    virtual bool connectInput(BlockInterface*)=0;
    virtual bool connectOutput(BlockInterface*)=0;


    virtual void disconnect()=0;

    virtual void run(Data* data)=0;

};


#define ConnectionInterface_iid "sony.simulink.ConnectionInterface"

Q_DECLARE_INTERFACE(ConnectionInterface, ConnectionInterface_iid)

#endif // ConnectionInterface
