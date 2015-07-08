#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

#include "blockview.h"


//enumerations
enum EditionState {
    POINTER,
    ADD_BLOCK,
    DELETE_BLOCK,
    ADD_CONNECTION,
    DELETE_CONNECTION
};

class RenderArea : public QWidget
{
    Q_OBJECT
    Q_ENUMS(EditionState);
public:
    explicit RenderArea(QWidget *parent = 0);


    //block manipulation
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE;




    void setState(EditionState state);

signals:

public slots:
    //void setBlock(BlockInterface block);

protected:
    void paintEvent(QPaintEvent *event)Q_DECL_OVERRIDE;


private:
    EditionState state;
    //BlockInterface block;
    std::vector<BlockView> blockViews;
    BlockView* checkBlockByCoordinates(QPoint position);
    bool checkCollisions(QPoint position, BlockView *block);

};

#endif // RENDERAREA_H
