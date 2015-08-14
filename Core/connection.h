#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include "connectioninterface.h"

class Connection : public ConnectionInterface
{
public:
    Connection();
    virtual void connect(BlockInterface*) Q_DECL_OVERRIDE;
    virtual void disconnect() Q_DECL_OVERRIDE;
    virtual void run(int) Q_DECL_OVERRIDE;  //numbers
    virtual void run(double) Q_DECL_OVERRIDE;   //vectors
    virtual void run(char) Q_DECL_OVERRIDE; //matrixes
private:
    BlockInterface* connectedBlock();


signals:

public slots:
};

#endif // CONNECTION_H
