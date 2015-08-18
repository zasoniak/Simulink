#include "simulinkengine.h"

SimulinkEngine::SimulinkEngine()
{
    this->processedBlocks = QVector<BlockInterface*>();
    this->connections = QVector<ConnectionInterface*>();
}

SimulinkEngine::~SimulinkEngine()
{
    QVector<BlockInterface*>::iterator blocks;
    for(blocks=this->processedBlocks.begin();blocks!=this->processedBlocks.end();blocks++)
    {
        delete *blocks;
    }
    this->processedBlocks.clear();

    QVector<ConnectionInterface*>::Iterator conns;
    for(conns=this->connections.begin();conns!=this->connections.end();conns++)
    {
        delete *conns;
    }
    this->connections.clear();
}

void SimulinkEngine::addBlock(BlockInterface* block)
{
    if(block)
        this->processedBlocks.push_back(block);
}

ConnectionInterface* SimulinkEngine::addConnection(BlockInterface* begin, BlockInterface* end)
{
    if(begin&&end)
    {
        ConnectionInterface* connection = new Connection();
        if(begin->connectOutput(connection)&& end->connectInput(connection))
        {
            this->connections.push_back(connection);
            return connection;
        }
    }
    return nullptr;
}

ConnectionInterface* SimulinkEngine::addConnection(ConnectionInterface* interface)
{
//    if(begin&&end)
//    {
//        ConnectionInterface* connection = new Connection();
//        begin->connectOutput(connection);
//        end->connectInput(connection);
//        return connection;
//    }
    return nullptr;
}

void SimulinkEngine::deleteBlock(BlockInterface* block)
{

}

void SimulinkEngine::deleteConnection(ConnectionInterface* connection)
{

}

void SimulinkEngine::run()
{
    QVector<BlockInterface*>::iterator it;
    for(it=this->processedBlocks.begin();it!=this->processedBlocks.end();it++)
    {
        (*it)->run();
    }
}

void SimulinkEngine::pause()
{

}

void SimulinkEngine::stop()
{

}
