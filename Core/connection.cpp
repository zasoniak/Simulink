#include "connection.h"

Connection::Connection()
{
    this->input=NULL;
    this->output=NULL;
}



bool Connection::connectInput(BlockInterface* input)
{
    if(input)
    {
        this->input=input;
        this->input->connectOutput(this);
        return true;
    }
    return false;
}

bool Connection::connectOutput(BlockInterface* output)
{
    if(output)
    {
        this->output=output;
        this->output->connectInput(this);
        return true;
    }
    return false;

}

void Connection::disconnect()
{
    this->input->disconnect(this);
    this->input=NULL;
    this->output->disconnect(this);
    this->output=NULL;
}

void Connection::run(Data* data)
{
    this->output->run(data, this);
}

