#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QtPlugin>
#include <QPluginLoader>
#include <QFileDialog>
#include <QMap>
#include <memory>


#include "blockfactoryinterface.h"

class PluginManager
{
public:
    PluginManager();
    bool loadPlugin(QWidget* parent);
    bool unloadPlugins();

    QMap<QString, BlockFactoryInterface*> getPlugins();
    //std::map<QString, BlockFactoryInterface*> getPlugins();
    BlockInterface *getBlock(QString name);

    virtual ~PluginManager() {}

private:
//    std::map<QString,BlockFactoryInterface*> pluginsLoaded;
//    std::map<QString,std::shared_ptr<BlockFactoryInterface>> pluginsLoaded;
    QMap<QString, BlockFactoryInterface*> pluginsLoaded;
};

#endif // PLUGINMANAGER_H
