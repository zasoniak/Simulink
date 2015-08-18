#include "connection.h"

Connection::Connection()
{
    this->input=NULL;
    this->output=NULL;
}



void Connection::connectInput(BlockInterface* input)
{
    if(input)
    {
        this->input=input;
    }
}

void Connection::connectOutput(BlockInterface* output)
{
    if(output)
    {
        this->output=output;
    }
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

