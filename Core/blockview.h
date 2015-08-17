#ifndef BLOCKVIEW_H
#define BLOCKVIEW_H


#include <QObject>
#include <QRect>
#include <QtGui/QImage>
#include "view.h"

class BlockInterface;

class BlockView : public QRect, public View
{
public:
    BlockView();
    BlockView(int x, int y, int width, int heigh);
    BlockView(QImage *image, BlockInterface* block);

    QImage* getView();
    BlockInterface* getBlock();

    virtual void paint(QPainter *painter) Q_DECL_OVERRIDE;

private:
    BlockInterface* block;
    QImage *image;

};



#endif // BLOCKVIEW_H

