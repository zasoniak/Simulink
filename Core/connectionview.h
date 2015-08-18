#ifndef CONNECTIONVIEW_H
#define CONNECTIONVIEW_H

#include <QObject>
#include "connectioninterface.h"
#include "connection.h"
#include "view.h"
#include "blockview.h"

class ConnectionView : public View
{
public:
    ConnectionView();
    ConnectionView(BlockView* begin, BlockView* end, ConnectionInterface* connection);
    ConnectionInterface* getConnection();
    virtual void paint(QPainter *painter) Q_DECL_OVERRIDE;
private:
    ConnectionInterface* connection;
    BlockView* begin, *end;

};

#endif // CONNECTIONVIEW_H
