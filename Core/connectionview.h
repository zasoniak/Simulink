#ifndef CONNECTIONVIEW_H
#define CONNECTIONVIEW_H

#include <QObject>
#include "connectioninterface.h"
#include "connection.h"
#include "view.h"
#include "blockview.h"
#include <QLine>

class ConnectionView : public View
{
public:
    ConnectionView();
    virtual ~ConnectionView(){}
    ConnectionView(BlockView* begin, BlockView* end, ConnectionInterface* connection);
    ConnectionInterface* getConnection();
    virtual void paint(QPainter *painter) Q_DECL_OVERRIDE;
    QPoint getBegin();
    QPoint getEnd();
private:
    ConnectionInterface* connection;
    BlockView* begin, *end;

};

#endif // CONNECTIONVIEW_H
