#include "connectionview.h"

ConnectionView::ConnectionView()
{
    this->begin=NULL;
    this->end=NULL;
    this->connection = NULL;
}

ConnectionView::ConnectionView(BlockView *begin, BlockView *end, ConnectionInterface *connection)
{
    this->begin=begin;
    this->end=end;
    this->connection=connection;
}

void ConnectionView::paint(QPainter *painter)
{
    QPoint beginPoint = this->begin->center();
    beginPoint.rx()=beginPoint.rx()+60;

    QPoint endPoint = this->end->center();
    endPoint.rx() = endPoint.rx()-50;

    painter->drawLine(beginPoint,endPoint);
}


ConnectionInterface* ConnectionView::getConnection()
{
    return this->connection;
}
