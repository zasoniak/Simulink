#include "simulinkengine.h"

SimulinkEngine::SimulinkEngine()
{
    this->processedBlocks = std::vector<BlockInterface*>();
    this->connections = std::vector<ConnectionInterface*>();
}

SimulinkEngine::~SimulinkEngine()
{
    this->connections.clear();
    this->processedBlocks.clear();
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
        begin->connectOutput(connection);
        end->connectInput(connection);
        return connection;
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

}

void SimulinkEngine::pause()
{

}

void SimulinkEngine::stop()
{

}
