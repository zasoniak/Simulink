#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QVector>

#include "blockview.h"
#include "connectionview.h"
#include "blockinterface.h"
#include "simulinkengine.h"
#include "propertieswidget.h"


//enumerations
enum EditionState {
    EDITION_STATE_POINTER,
    EDITION_STATE_ADD_BLOCK,
    EDITION_STATE_DELETE_BLOCK,
    EDITION_STATE_ADD_CONNECTION,
    EDITION_STATE_DELETE_CONNECTION
};

class RenderArea : public QWidget
{
    Q_OBJECT
    Q_ENUMS(EditionState)
public:
    explicit RenderArea(QWidget *parent = 0);
    explicit RenderArea(QWidget *parent = 0, SimulinkEngine* engine=0, PropertiesWidget* propertiesWidget=0);


    //block manipulation
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE;

    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void addBlock(BlockInterface* block);


    void setState(EditionState state);

signals:

public slots:
    //void setBlock(BlockInterface block);

protected:
    void paintEvent(QPaintEvent *event)Q_DECL_OVERRIDE;


private:
    SimulinkEngine* engine;
    PropertiesWidget* propertiesWidget;
    EditionState state;
    BlockInterface* blockToAdd;
    BlockView* connectionBeginBlock;
    QVector<BlockView*> blockViews;
    QVector<ConnectionView*> connectionViews;


    ConnectionView* addConnection(BlockView* begin, BlockView* end);
    BlockView* checkBlockByCoordinates(QPoint position);
    bool checkCollisions(QPoint position, BlockView *block);

};

#endif // RENDERAREA_H
