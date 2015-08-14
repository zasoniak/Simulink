#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <QObject>
#include <QVector>

#include "observer.h"

class Observable
{
public:
    Observable();
    void registerObserver(Observer *observer);
    void unregisterObserver(Observer *observer);
    void notifyObservers(ValueType type, QString value);

private:
    QVector<Observer*> observers;
};

#endif // OBSERVABLE_H
