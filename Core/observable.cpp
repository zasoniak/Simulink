#include "observable.h"

Observable::Observable()
{
    this->observers = QVector<Observer*>();
}

void Observable::registerObserver(Observer *observer)
{
    if(observer)
    this->observers.append(observer);
}

void Observable::unregisterObserver(Observer *observer)
{
    if(observer)
    {
        int position = this->observers.indexOf(observer);
        this->observers.remove(position);
    }
}

void Observable::notifyObservers(ValueType type, QString value)
{
    QVector<Observer*>::iterator it;
    for(it=this->observers.begin();it!=this->observers.end();it++)
    {
        (*it)->valueChanged(type, value);
    }
}
