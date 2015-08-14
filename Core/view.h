#ifndef VIEW
#define VIEW

#include <QtGui/QPainter>

class View
{
public:
    virtual void paint(QPainter* painter)=0;
};


#endif // VIEW

