#include "mainwindow.h"



/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{


    //===== plugin system ======================
    pluginManager = new PluginManager();

    //===== simulink engine initialization =====
    this->engine = new SimulinkEngine();


    //==========================================
    //===== UI initialization ==================
    //==========================================

    //===== central widget =====================
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    this->statusBar()->show();
    QString message = tr("Hello everybody!");
    this->statusBar()->showMessage(message);


    //===== properties ==========================
    propertiesWidget = new PropertiesWidget(this);
    propertiesWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    propertiesWidget->setFixedWidth(200);


    //===== render area ========================
    renderArea = new RenderArea(this, this->engine, this->propertiesWidget);



    //===== toolbox ============================
    toolbox = new Toolbox(this);
    toolbox->registerObserver(this);
    toolbox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    toolbox->setFixedHeight(400);
    toolbox->setFixedWidth(200);





    //===== main window layout =================
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnMinimumWidth(0,400);
    mainLayout->setColumnStretch(0,4);
    mainLayout->setColumnMinimumWidth(1,200);



    mainLayout->addWidget(renderArea,0,0,2,1);
    mainLayout->addWidget(toolbox,0,1);
    mainLayout->addWidget(propertiesWidget,1,1);
    widget->setLayout(mainLayout);


    //===== other parts of main window ========
    createActions();
    createMenus();
    //createToolbars();

    //====== title and size policy ============
    setWindowTitle(tr("Simulink"));
    setMinimumSize(800, 600);
    resize(800,600);
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    this->toolbox->unregisterObserver(this);
}


/**
 * @brief MainWindow::createActions
 */
void MainWindow::createActions()
{
    newFileAction = new QAction(tr("&New"),this);
    newFileAction->setShortcuts(QKeySequence::New);
    newFileAction->setStatusTip(tr("Create a new file"));
    connect(newFileAction, SIGNAL(triggered()), this, SLOT(newFile()));

    openAction = new QAction(tr("&Open"),this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(tr("&Save"),this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save file"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    closeAction = new QAction(tr("&Close"),this);
    closeAction->setShortcuts(QKeySequence::Close);
    closeAction->setStatusTip(tr("Close file"));
    connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

    exitAction = new QAction(tr("&Exit"),this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Exit Simulink program"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(exit()));

    loadPluginsAction = new QAction(tr("&Load plugins"),this);
    loadPluginsAction->setStatusTip(tr("Load selected plugins into simulink program"));
    connect(loadPluginsAction, SIGNAL(triggered()), this, SLOT(loadPlugins()));

    unLoadPluginsAction = new QAction(tr("&Unload plugins"),this);
    unLoadPluginsAction->setStatusTip(tr("Unload all plugins"));
    connect(unLoadPluginsAction, SIGNAL(triggered()), this, SLOT(unLoadPlugins()));

    helpAction = new QAction(tr("&Help"),this);
    helpAction->setShortcuts(QKeySequence::HelpContents);
    helpAction->setStatusTip(tr("Help"));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(help()));

    aboutAction = new QAction(tr("&About"),this);
    aboutAction->setStatusTip(tr("About simulink program"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    runAction = new QAction(tr("&Run"),this);
    runAction->setStatusTip(tr("Run computation"));
    connect(runAction,SIGNAL(triggered()),this,SLOT(run()));
}


/**
 * @brief MainWindow::createMenus
 */
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(closeAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    computeMenu = menuBar()->addMenu(tr("&Compute"));
    computeMenu->addAction(runAction);


    pluginMenu = menuBar()->addMenu(tr("&Plugins"));
    pluginMenu->addAction(loadPluginsAction);
    pluginMenu->addAction(unLoadPluginsAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(helpAction);
}

/**
 * @brief MainWindow::createToolbars
 */
void MainWindow::createToolbars()
{
//    QPixmap start("start.png");
//    QPixmap pause("pause.png");
//    QPixmap stop("stop.png");
    QPixmap block("block.png");
//    QPixmap con("con.png");
//    QPixmap delete_con("delete_con.png");
//    QPixmap delete_block("delete_block.png");


  //  QToolBar *mainToolbar = new QToolBar(tr("Main"), this);/*addToolBar("Main toolbar");*/
    //mainToolbar->addAction(addBlockAction);
//    mainToolbar->addAction(QIcon(con),"New connector");
//    mainToolbar->addAction(QIcon(delete_con),"Delete block");
//    mainToolbar->addAction(QIcon(delete_block),"Delete connector");
//    mainToolbar->show();
 //   mainToolbar->show();

 //   addToolBar(Qt::TopToolBarArea, mainToolbar);




}



//file menu
void MainWindow::newFile() { }
void MainWindow::open() { }
void MainWindow::save() { }
void MainWindow::close()
{

}
void MainWindow::exit()
{
    close();
    qApp->quit();
}

void MainWindow::run()
{
    this->engine->run();
}

//plugin menu
void MainWindow::loadPlugins() {
    if(this->pluginManager->loadPlugin(this))
    {

        QMap<QString, BlockFactoryInterface*> plugins = pluginManager->getPlugins();
        QStringList pluginList = QStringList();
        QMap<QString, BlockFactoryInterface*>::iterator it;
        for(it=plugins.begin();it!=plugins.end();it++)
        {
            pluginList.push_back(it.key());
        }
        this->toolbox->reloadBlockList(pluginList);


        QString message = tr("New block: ");
        BlockFactoryInterface *factory = (plugins.end()-1).value();
        message.append(factory->getBlockName());
        message.append(tr(" added"));
        statusBar()->showMessage(message);
    }
    else
    {
         QString message = tr("I dupa blada! Nie wyszlo cos");
         statusBar()->showMessage(message);
    }
}

void MainWindow::unLoadPlugins() {
    this->pluginManager->unloadPlugins();
}
//help menu
void MainWindow::about() { }
void MainWindow::help() { }


void MainWindow::valueChanged(ValueType type, QString value)
{
    switch (type) {
    case VALUE_TYPE_RENDER_ACTION:
        if(value.compare("BlockAdded"))
        {
            this->engine->addBlock(this->temporaryBlock);
            this->temporaryBlock=nullptr;
        }
        else if(value.compare("NoBlockAdded"))
        {
            this->temporaryBlock=nullptr;
        }
        break;
    case VALUE_TYPE_BLOCK_NAME:
        temporaryBlock = this->pluginManager->getBlock(value);
        if(temporaryBlock!=NULL)
            this->renderArea->addBlock(temporaryBlock);
        break;
    case VALUE_TYPE_NEW_CONNECTION:
        this->renderArea->setState(EDITION_STATE_ADD_CONNECTION);
        break;
    default:
        break;
    }
}
