#ifndef BLOCKPROPERTIESINTERFACE
#define BLOCKPROPERTIESINTERFACE

#include <QObject>

class BlockPropertiesInterface
{
public:
    virtual ~BlockPropertiesInterface() {}

    virtual QMap<QString, double>* getProperties()=0;
    virtual void saveProperty(QString name, double value)=0;
    virtual void resetToDefaults()=0;

};

#define BlockPropertiesInterface_iid "sony.simulink.BlockPropertiesInterface_iid"
Q_DECLARE_INTERFACE(BlockPropertiesInterface, BlockPropertiesInterface_iid)

#endif // BLOCKPROPERTIESINTERFACE

