#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{

    blockViews = std::vector<BlockView>();
    BlockView block1 = BlockView(10,10,100,60);
    blockViews.push_back(block1);
    BlockView block2 = BlockView(220,100,100,60);
        blockViews.push_back(block2);
    BlockView block3 = BlockView(390,140,100,60);
        blockViews.push_back(block3);
    BlockView block4 = BlockView(100,290,100,60);
        blockViews.push_back(block4);
    BlockView block5 = BlockView(350,350,100,60);
        blockViews.push_back(block5);

    state = POINTER;


    this->setAutoFillBackground( true );
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Background, Qt::blue);
    this->setPalette(palette);
}



void RenderArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    std::vector<BlockView>::iterator it;
    for(it=blockViews.begin();it!=blockViews.end();it++)
    {
      painter.drawRect(*it);
    }
}


void RenderArea::mouseMoveEvent(QMouseEvent *event)
{
    switch(state)
    {
    case POINTER:
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
    case POINTER:
    {
        BlockView  *editedBlock = checkBlockByCoordinates(event->pos());
        if(editedBlock!=NULL)
        {

        }
        break;
    }
    case ADD_BLOCK:
    {
        BlockView  *editedBlock = checkBlockByCoordinates(event->pos());
        if(editedBlock==NULL)
        {
            this->state = POINTER;
            BlockView block = BlockView(-500,-500,100,60);
            block.moveCenter(event->pos());
            blockViews.push_back(block);
            repaint();
        }
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
    std::vector<BlockView>::iterator it;
    for(it=blockViews.begin();it!=blockViews.end();it++)
    {
      if(position.rx()>=it->left() && position.rx()<=it->right() &&position.ry()>=it->top() &&position.ry()<=it->bottom())
        return &(*it);
    }
    return NULL;
}

/**
 * @brief RenderArea::checkCollisions
 * Check if block doesnt collide with others and doesnt exceed widget size
 *
 * @param position - mouse cursor position
 * @param block - currently moving block
 * @return if new position is OK
 */
bool RenderArea::checkCollisions(QPoint position, BlockView *block)
{
    int a = this->width();
    int b = this->height();
    if((position.rx()-50)>=0 && (position.rx()+50)<=this->width() && (position.ry()-30)>=0 &&(position.ry()+30)<=this->height())
    {
        std::vector<BlockView>::iterator it;
        for(it=blockViews.begin();it!=blockViews.end();it++)
        {
            if(&(*it)!=block)
                if((position.rx()-50)<=it->right() && (position.rx()+50)>=it->left() && (position.ry()-30)<=it->bottom() &&(position.ry()+30)>=it->top())
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
