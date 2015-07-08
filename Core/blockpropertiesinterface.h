#ifndef BLOCKPROPERTIESINTERFACE
#define BLOCKPROPERTIESINTERFACE

#include <QObject>

class BlockPropertiesInterface
{
    virtual ~BlockPropertiesInterface() {}

};

#define BlockPropertiesInterface_iid "sony.simulink.BlockPropertiesInterface_iid"
Q_DECLARE_INTERFACE(BlockPropertiesInterface, BlockPropertiesInterface_iid)

#endif // BLOCKPROPERTIESINTERFACE

