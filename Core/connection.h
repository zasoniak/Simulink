#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include "connectioninterface.h"
#include "blockinterface.h"

class Connection : public ConnectionInterface
{
public:
    Connection();
    virtual ~Connection(){}
    virtual void connectInput(BlockInterface*) Q_DECL_OVERRIDE;
    virtual void connectOutput(BlockInterface *) Q_DECL_OVERRIDE;
    virtual void disconnect() Q_DECL_OVERRIDE;
    virtual void run(Data* data) Q_DECL_OVERRIDE;

private:
    BlockInterface *input, *output;


signals:

public slots:
};

#endif // CONNECTION_H
