#include "pluginmanager.h"

PluginManager::PluginManager()
{
//    pluginsLoaded = std::map<QString,std::shared_ptr<BlockFactoryInterface>>();
    pluginsLoaded = QMap<QString, BlockFactoryInterface*>();
}

bool PluginManager::loadPlugin(QWidget* parent)
{
    QString filePath = QFileDialog::getOpenFileName(parent, QObject::trUtf8("Library file"));
    QPluginLoader loader(filePath);
    QObject *plugin = loader.instance();
    if (plugin)
    {
         BlockFactoryInterface* blockFactory = qobject_cast<BlockFactoryInterface *>(plugin);  //qobject_cast<BlockFactoryInterface*> (plugin);
         if(this->pluginsLoaded.find(blockFactory->getBlockName())==this->pluginsLoaded.end())
         {
            this->pluginsLoaded.insert(blockFactory->getBlockName(),blockFactory);
            return true;
         }
         else
         {
             blockFactory->release();
             delete blockFactory;
             return false;
         }
    }
    else
        return false;
}

bool PluginManager::unloadPlugins()
{
    QMap<QString, BlockFactoryInterface*>::iterator it;
    for(it=this->pluginsLoaded.begin();it!=this->pluginsLoaded.end();it++)
    {
        it.value()->release();
    }
    this->pluginsLoaded.clear();

    return true;
}

QMap<QString, BlockFactoryInterface*> PluginManager::getPlugins()
{
    return this->pluginsLoaded;
}


BlockInterface* PluginManager::getBlock(QString name)
{
    if(this->pluginsLoaded.find(name)!=this->pluginsLoaded.end())
        return this->pluginsLoaded.find(name).value()->getNewBlock();
    else return nullptr;
}

