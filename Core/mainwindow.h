#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QObject>
#include <QMap>
#include <QMainWindow>
#include <QApplication>
#include <QAction>
#include <QLabel>
#include <QStatusBar>
#include <QMenu>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QToolBar>
#include <QScrollArea>
#include <QPluginLoader>
#include <QFileDialog>

#include "renderarea.h"
#include "toolbox.h"
#include "propertieswidget.h"
#include "pluginmanager.h"

#include "simulinkengine.h"

class MainWindow :
        public QMainWindow,
        public Observer
{
    Q_OBJECT
    Q_INTERFACES(Observer)

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual void valueChanged(ValueType type, QString value) Q_DECL_OVERRIDE;
protected:
   // void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

private slots:
    //file menu
    void newFile();
    void open();
    void save();
    void close();
    void exit();
    //plugin menu
    void loadPlugins();
    void unLoadPlugins();
    //help menu
    void about();
    void help();

    void run();


private:
    void createActions();
    void createMenus();
    void createToolbars();


    QMenu *fileMenu;
    QMenu *pluginMenu;
    QMenu *helpMenu;
    QMenu *computeMenu;

    QAction *newFileAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *closeAction;
    QAction *exitAction;
    QAction *loadPluginsAction;
    QAction *unLoadPluginsAction;
    QAction *runAction;
    QAction *aboutAction;
    QAction *helpAction;

    QLabel *infoLabel;
    QLabel *statusLabel;


//    QAction *addBlockAction;

    RenderArea *renderArea;
    Toolbox *toolbox;
    PropertiesWidget *propertiesWidget;

    PluginManager *pluginManager;


    SimulinkEngine *engine;
    BlockInterface *temporaryBlock;

};

#endif // MAINWINDOW_H
