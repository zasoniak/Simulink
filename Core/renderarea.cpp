#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{

    blockViews = QVector<BlockView*>();

    this->state = EDITION_STATE_POINTER;
    this->blockToAdd=NULL;
    this->connectionBeginBlock=NULL;


    this->setAutoFillBackground( true );
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Background, Qt::lightGray);
    this->setPalette(palette);
}


RenderArea::RenderArea(QWidget *parent, SimulinkEngine *engine, PropertiesWidget * propertiesWidget) : QWidget(parent)
{

    blockViews = QVector<BlockView*>();

    //default values
    this->state = EDITION_STATE_POINTER;
    this->blockToAdd=NULL;
    this->connectionBeginBlock=NULL;
    this->engine= engine;

    this->propertiesWidget = propertiesWidget;

    //configuration
    this->setAutoFillBackground( true );
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Background, Qt::lightGray);
    this->setPalette(palette);
}



void RenderArea::paintEvent(QPaintEvent *)
{
    QPainter *painter = new QPainter(this);

    QVector<BlockView*>::iterator blockIterator;
    for(blockIterator=blockViews.begin();blockIterator!=blockViews.end();blockIterator++)
    {
        (*blockIterator)->paint(painter);
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
            this->propertiesWidget->loadProperties(editedBlock->getBlock()->getProperties());
        }
        break;
    }
    case EDITION_STATE_ADD_BLOCK:
    {
        this->propertiesWidget->unloadProperties();
        BlockView  *editedBlock = checkBlockByCoordinates(event->pos());
        if(editedBlock==NULL)
        {
            setState(EDITION_STATE_POINTER);
            BlockView* block = new BlockView(this->blockToAdd->getView(),this->blockToAdd);
            block->moveCenter(event->pos());
            blockViews.push_back(block);
            this->engine->addBlock(block->getBlock());
            this->blockToAdd=NULL;
        }
        break;
    }
    case EDITION_STATE_ADD_CONNECTION:
    {
        this->propertiesWidget->unloadProperties();
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
            if(blockSelected && (blockSelected!=this->connectionBeginBlock))
            {
                ConnectionInterface* newConnection = this->engine->addConnection(this->connectionBeginBlock->getBlock(),blockSelected->getBlock());

                if(newConnection)
                {
                    this->addConnection(this->connectionBeginBlock,blockSelected, newConnection);
                    this->connectionBeginBlock=NULL;
                    this->setState(EDITION_STATE_POINTER);
                }
                else
                {
                    notifyObservers(VALUE_TYPE_ERROR, "Cannot create connection, please try again");
                    this->connectionBeginBlock=NULL;
                    this->setState(EDITION_STATE_POINTER);
                }
            }
            else
            {
                notifyObservers(VALUE_TYPE_ERROR, "Cannot create connection, please try again");
                this->connectionBeginBlock=NULL;
                this->setState(EDITION_STATE_POINTER);
            }
        }
        break;
    }
    case EDITION_STATE_DELETE_BLOCK:
    {
        BlockView  *editedBlock = checkBlockByCoordinates(event->pos());
        if(editedBlock!=NULL)
        {
            QVector<ConnectionInterface*> connectionsToDelete = editedBlock->getBlock()->getConnections();
            QVector<ConnectionInterface*>::iterator it;

            for(it=connectionsToDelete.begin();it!=connectionsToDelete.end();it++)
            {
                //odszukac connection view
                QVector<ConnectionView*>::iterator views;
                for(views=this->connectionViews.begin();views!=this->connectionViews.end();views++)
                {
                    if((*views)->getConnection() == (*it))
                    {
                        this->engine->deleteConnection((*it));
                        this->connectionViews.removeOne(*views);
                        break;
                    }
                }
            }
            this->engine->deleteBlock(editedBlock->getBlock());
            this->blockViews.removeOne(editedBlock);
            delete editedBlock;
        }
        this->setState(EDITION_STATE_POINTER);
        break;
    }
    case EDITION_STATE_DELETE_CONNECTION:
    {
        ConnectionView* connectionSelected = checkConnectionByCoordinates(event->pos());
        if(connectionSelected)
        {
            this->engine->deleteConnection(connectionSelected->getConnection());
            this->connectionViews.removeOne(connectionSelected);
            delete connectionSelected;
        }
        this->setState(EDITION_STATE_POINTER);
        break;
    }
    default:
        break;
    }
    repaint();
}



void RenderArea::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(this->state == EDITION_STATE_POINTER)
    {
        BlockView  *editedBlock = checkBlockByCoordinates(event->pos());
        if(editedBlock!=NULL)
        {
            editedBlock->getBlock()->openWindow();
        }
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
    return nullptr;
}

ConnectionView* RenderArea::checkConnectionByCoordinates(QPoint position)
{
    QVector<ConnectionView*>::iterator it;
    for(it=connectionViews.begin();it!=connectionViews.end();it++)
    {
        QPoint begin = (*it)->getBegin();
        QPoint end = (*it)->getEnd();


        double A,B,C, distance;
        if(end.ry()==begin.ry())
        {
            A=0;
            B=1;
            C=end.ry();
        }
        if(end.rx()==begin.rx())
        {
            B=0;
            A=1;
            C=end.rx();
        }
        A=1;
        B= (double)(begin.rx()-end.rx())/(double)(end.ry()-begin.ry());
        C= -(begin.rx()) - B*begin.ry();

        distance = abs(A*position.rx()+B*position.ry()+C) / sqrt(A*A +B*B);

        if(distance<5)
        {
            return *it;
        }
    }
    return nullptr;
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


void RenderArea::addConnection(BlockView* begin, BlockView* end, ConnectionInterface* connection)
{
    ConnectionView* connectionView = new ConnectionView(begin,end,connection);
    this->connectionViews.push_back(connectionView);
    this->repaint();
}
