#ifndef BLOCKVIEW_H
#define BLOCKVIEW_H


#include <QObject>
#include <QRect>
#include "blockview.h"

class BlockView :public QRect
{
public:
    BlockView();
    BlockView(int x, int y, int width, int heigh);
};



#endif // BLOCKVIEW_H

