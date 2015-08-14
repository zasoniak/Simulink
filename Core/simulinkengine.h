#ifndef SIMULINKENGINE_H
#define SIMULINKENGINE_H

#include <QObject>
#include "blockfactoryinterface.h"
#include "connection.h"

class SimulinkEngine
{
public:
    SimulinkEngine();
    virtual ~SimulinkEngine();


    void addBlock(BlockInterface* );
    ConnectionInterface* addConnection(BlockInterface*, BlockInterface*);
    ConnectionInterface* addConnection(ConnectionInterface* interface);
    void deleteBlock(BlockInterface*);
    void deleteConnection(ConnectionInterface*);

    void run();
    void pause();
    void stop();


private:



    std::vector<BlockInterface*> processedBlocks;
    std::vector<ConnectionInterface*> connections;

};

#endif // SIMULINKENGINE_H
