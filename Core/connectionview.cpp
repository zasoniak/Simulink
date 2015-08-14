#include "connectionview.h"

ConnectionView::ConnectionView()
{

}


ConnectionView::ConnectionView(BlockView* begin, BlockView* end)
{
    this->begin=begin;
    this->end=end;
}

void ConnectionView::paint(QPainter *painter)
{
    painter->drawLine(this->begin->center(),this->end->center());
}


ConnectionInterface* ConnectionView::getConnection()
{
    return this->connection;
}
