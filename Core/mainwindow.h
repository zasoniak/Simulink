#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QObject>
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

//#include "renderarea.h"
//#include "toolbox.h"
//#include "propertieswidget.h"
#include "pluginmanager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
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

    void addBlock();

private:
    void createActions();
    void createMenus();
    void createToolbars();


    QMenu *fileMenu;
    QMenu *pluginMenu;
    QMenu *helpMenu;

    QAction *newFileAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *closeAction;
    QAction *exitAction;
    QAction *loadPluginsAction;
    QAction *unLoadPluginsAction;
    QAction *aboutAction;
    QAction *helpAction;

    QLabel *infoLabel;
    QLabel *statusLabel;


    QAction *addBlockAction;

//    RenderArea *renderArea;
//    Toolbox *toolbox;
//    PropertiesWidget *propertiesWidget;

    PluginManager *pluginManager;

};

#endif // MAINWINDOW_H
