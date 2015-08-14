#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{

    blockViews = QVector<BlockView*>();
//    BlockView* block1 = new BlockView(10,10,100,60);
//    blockViews.push_back(block1);
//    BlockView* block2 = new BlockView(220,100,100,60);
//        blockViews.push_back(block2);
//    BlockView* block3 = new BlockView(390,140,100,60);
//        blockViews.push_back(block3);
//    BlockView* block4 = new BlockView(100,290,100,60);
//        blockViews.push_back(block4);
//    BlockView* block5 = new BlockView(350,350,100,60);
//        blockViews.push_back(block5);

    this->state = EDITION_STATE_POINTER;
    this->blockToAdd=NULL;
    this->connectionBeginBlock=NULL;


    this->setAutoFillBackground( true );
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Background, Qt::blue);
    this->setPalette(palette);
}


RenderArea::RenderArea(QWidget *parent, SimulinkEngine *engine) : QWidget(parent)
{

    blockViews = QVector<BlockView*>();
//    BlockView* block1 = new BlockView(10,10,100,60);
//    blockViews.push_back(block1);
//    BlockView* block2 = new BlockView(220,100,100,60);
//        blockViews.push_back(block2);
//    BlockView* block3 = new BlockView(390,140,100,60);
//        blockViews.push_back(block3);
//    BlockView* block4 = new BlockView(100,290,100,60);
//        blockViews.push_back(block4);
//    BlockView* block5 = new BlockView(350,350,100,60);
//        blockViews.push_back(block5);

    this->state = EDITION_STATE_POINTER;
    this->blockToAdd=NULL;
    this->connectionBeginBlock=NULL;
    this->engine= engine;


    this->setAutoFillBackground( true );
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Background, Qt::blue);
    this->setPalette(palette);
}



void RenderArea::paintEvent(QPaintEvent *)
{
    QPainter *painter = new QPainter(this);

    QVector<BlockView*>::iterator blockIterator;
    for(blockIterator=blockViews.begin();blockIterator!=blockViews.end();blockIterator++)
    {
        (*blockIterator)->paint(painter);

      //painter.drawRect(*(*blockIterator));
      //painter->drawImage((*blockIterator)->topLeft(),*((*blockIterator)->getView()));
    }


    QVector<ConnectionView*>::iterator connectionIterator;
    for(connectionIterator=connectionViews.begin();connectionIterator!=connectionViews.end();connectionIterator++)
    {
        (*connectionIterator)->paint(painter);
    }
}


void RenderArea::mouseMoveEvent(QMouseEvent *event)
{
    switch(state)
    {
    case EDITION_STATE_POINTER:
    {
        BlockView  *editedBlock = checkBlockByCoordinates(event->pos());
        if(editedBlock!=NULL)
        {
            if(checkCollisions(event->pos(), editedBlock))
            {
                 editedBlock->moveCenter(event->pos());
                repaint();
            }
        }
        break;
    }
    default:
        break;
    }
}


void RenderArea::mousePressEvent(QMouseEvent *event)
{
    switch(this->state)
    {
    case EDITION_STATE_POINTER:
    {
        BlockView  *editedBlock = checkBlockByCoordinates(event->pos());
        if(editedBlock!=NULL)
        {

        }
        break;
    }
    case EDITION_STATE_ADD_BLOCK:
    {
        BlockView  *editedBlock = checkBlockByCoordinates(event->pos());
        if(editedBlock==NULL)
        {
            setState(EDITION_STATE_POINTER);
            BlockView* block = new BlockView(this->blockToAdd->getView(),this->blockToAdd);
//            BlockView block = BlockView(-500,-500,100,60);
            block->moveCenter(event->pos());
            blockViews.push_back(block);
            repaint();
            this->engine->addBlock(block->getBlock());
            this->blockToAdd=NULL;
        }
        break;
    }
    case EDITION_STATE_ADD_CONNECTION:
    {
        if(this->connectionBeginBlock==NULL)    //pierwszy klik
        {
            BlockView* blockSelected = checkBlockByCoordinates(event->pos());
            if(blockSelected)
            {
                this->connectionBeginBlock=blockSelected;
            }
            else
            {
                   this->setState(EDITION_STATE_POINTER);
            }
        }
        else    //drugi klik
        {
            BlockView* blockSelected = checkBlockByCoordinates(event->pos());
            if(blockSelected)
            {
                ConnectionView* connectionView = this->addConnection(this->connectionBeginBlock,blockSelected);
                this->engine->addConnection(connectionView->getConnection());
            //    this->connectionViews.push_back(connectionView);
                this->connectionBeginBlock=NULL;
                this->setState(EDITION_STATE_POINTER);
            }
            else
            {
                   this->setState(EDITION_STATE_POINTER);
            }
        }
        break;
    }
    default:
        break;
    }
}

/**
 * @brief RenderArea::checkBlockByCoordinates
 * @param position
 * @return
 */
BlockView* RenderArea::checkBlockByCoordinates(QPoint position)
{
    QVector<BlockView*>::iterator it;
    for(it=blockViews.begin();it!=blockViews.end();it++)
    {
      if(position.rx()>=(*it)->left() && position.rx()<=(*it)->right() &&position.ry()>=(*it)->top() &&position.ry()<=(*it)->bottom())
        return (*it);
    }
    return NULL;
}

/**
 * @brief RenderArea::checkCollisions
 * Check if block doesn't collide with others and doesn't exceed widget size
 *
 * @param position - mouse cursor position
 * @param block - currently moving block
 * @return if new position is OK
 */
bool RenderArea::checkCollisions(QPoint position, BlockView *block)
{
    if((position.rx()-60)>=0 && (position.rx()+60)<=this->width() && (position.ry()-30)>=0 &&(position.ry()+30)<=this->height())
    {
        QVector<BlockView*>::iterator it;
        for(it=blockViews.begin();it!=blockViews.end();it++)
        {
            if((*it)!=block)
                if((position.rx()-60)<=(*it)->right() && (position.rx()+60)>=(*it)->left() && (position.ry()-30)<=(*it)->bottom() &&(position.ry()+30)>=(*it)->top())
                    return false;
        }
        return true;
    }
    return false;
}

void RenderArea::setState(EditionState state)
{
    this->state =state;
}

void RenderArea::addBlock(BlockInterface* block)
{
    this->blockToAdd=block;
    this->setState(EDITION_STATE_ADD_BLOCK);
}


ConnectionView* RenderArea::addConnection(BlockView* begin, BlockView* end)
{
    ConnectionView* connection = new ConnectionView(begin, end);
    this->connectionViews.push_back(connection);
}
