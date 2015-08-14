#include "blockview.h"

BlockView::BlockView()
{
    this->image=nullptr;
    this->block=nullptr;
}

BlockView::BlockView(int x, int y, int width, int heigh) : QRect(x,y,width,heigh)
{
    this->image=nullptr;
    this->block=nullptr;
}

BlockView::BlockView(QImage *image, BlockInterface *block): QRect(0,0,100,60)
{
    this->image=image;
    this->block=block;
}



QImage* BlockView::getView()
{
    return this->image;
}

BlockInterface* BlockView::getBlock()
{
    return this->block;
}



void BlockView::paint(QPainter *painter)
{
    painter->drawImage(topLeft(),*image);
}
