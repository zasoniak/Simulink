#ifndef CONNECTORINTERFACE
#define CONNECTORINTERFACE

#include <QObject>
class BlockInterface;

class ConnectorInterface
{
public:
    virtual ~ConnectorInterface() {}
    virtual void connect(BlockInterface*)=0;
    virtual void disconnect()=0;

};


#define ConnectorInterface_iid "sony.simulink.ConnectorInterface"

Q_DECLARE_INTERFACE(ConnectorInterface, ConnectorInterface_iid)

#endif // CONNECTORINTERFACE

