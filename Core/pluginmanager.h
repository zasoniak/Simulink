#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QtPlugin>
#include <QPluginLoader>
#include <QFileDialog>


#include "blockfactoryinterface.h"

class PluginManager
{
public:
    PluginManager();
    bool loadPlugin(QWidget* parent);
    bool unloadPlugins();

    std::vector<BlockFactoryInterface*> getPlugins();

    virtual ~PluginManager() {}

private:
    std::vector<BlockFactoryInterface*> pluginsLoaded;
};

#endif // PLUGINMANAGER_H
