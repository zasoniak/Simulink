#include "pluginmanager.h"

PluginManager::PluginManager()
{
    pluginsLoaded = std::vector<BlockFactoryInterface*>();
}

bool PluginManager::loadPlugin(QWidget* parent)
{
    QString filePath = QFileDialog::getOpenFileName(parent, QObject::trUtf8("Library file"));
    QPluginLoader loader(filePath);
    QObject *plugin = loader.instance();
    if (plugin)
    {
         BlockFactoryInterface* blockFactory = qobject_cast<BlockFactoryInterface *>(plugin);  //qobject_cast<BlockFactoryInterface*> (plugin);
         pluginsLoaded.push_back(blockFactory);
         return true;
    }
    else
        return false;
}

bool PluginManager::unloadPlugins()
{
    std::vector<BlockFactoryInterface*>::iterator it;
    for(it=this->pluginsLoaded.begin();it!=this->pluginsLoaded.end();it++)
    {
        (*it)->release();
        pluginsLoaded.erase(it);
    }
    return true;
}

std::vector<BlockFactoryInterface*> PluginManager::getPlugins()
{
    return this->pluginsLoaded;
}


