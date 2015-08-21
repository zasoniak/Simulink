#ifndef OBSERVER
#define OBSERVER

#include <QObject>

enum ValueType {
    VALUE_TYPE_RENDER_ACTION,
    VALUE_TYPE_CALCULATION_ACTION,
    VALUE_TYPE_BLOCK_NAME,
    VALUE_TYPE_NEW_CONNECTION,
    VALUE_TYPE_DELETE_CONNECTION,
    VALUE_TYPE_DELETE_BLOCK,
    VALUE_TYPE_ERROR
};

class Observer
{
public:
    virtual void valueChanged(ValueType type, QString value)=0;
};



#define Observer_iid "sony.simulink.Observer"

Q_DECLARE_INTERFACE(Observer, Observer_iid)


#endif // OBSERVER

