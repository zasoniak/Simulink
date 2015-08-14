#ifndef CONNECTIONINTERFACE
#define CONNECTIONINTERFACE

#include <QObject>
class BlockInterface;

class ConnectionInterface
{
public:
    virtual ~ConnectionInterface() {}
    virtual void connect(BlockInterface*)=0;
    virtual void disconnect()=0;
    virtual void run(int)=0;  //numbers
    virtual void run(double)=0;   //vectors
    virtual void run(char)=0; //matrixes

};


#define ConnectionInterface_iid "sony.simulink.ConnectionInterface"

Q_DECLARE_INTERFACE(ConnectionInterface, ConnectionInterface_iid)

#endif // ConnectionInterface
