#include "mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    pluginManager = new PluginManager();


  //  renderArea = new RenderArea;



//    QScrollArea *scrollArea = new QScrollArea;
//    scrollArea->setBackgroundRole(QPalette::Dark);
//    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//    scrollArea->setWidget(renderArea);

//    infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to invoke a context menu</i>"));
//    infoLabel->setFrameStyle(QFrame::StyledPanel|QFrame::Sunken);
//    infoLabel->setAlignment(Qt::AlignCenter);
//    infoLabel->setFixedHeight(25);

//    statusLabel = new QLabel(tr("status"));
//    statusLabel->setFrameStyle(QFrame::StyledPanel|QFrame::Sunken);
//    statusLabel->setAlignment(Qt::AlignCenter);
//    statusLabel->setFixedHeight(25);


//    toolbox = new Toolbox;
//    toolbox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//    toolbox->setFixedHeight(400);
//    toolbox->setFixedWidth(200);

//    propertiesWidget = new PropertiesWidget;
//    propertiesWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

//    propertiesWidget->setFixedWidth(200);


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnMinimumWidth(0,400);
    mainLayout->setColumnStretch(0,4);
    mainLayout->setColumnMinimumWidth(1,200);



//    mainLayout->addWidget(renderArea,0,0,2,1);
////    mainLayout->addWidget(infoLabel,2,0);
//    mainLayout->addWidget(toolbox,0,1);
//    mainLayout->addWidget(propertiesWidget,1,1);
//    mainLayout->addWidget(statusLabel,2,1);
    widget->setLayout(mainLayout);

    createActions();
    createMenus();
    createToolbars();

    QString message = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);

    setWindowTitle(tr("Menus"));
    setMinimumSize(160, 160);
    resize(480, 320);
}

MainWindow::~MainWindow()
{

}

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


    addBlockAction = new QAction(tr("&New block"), this);
    connect(addBlockAction, SIGNAL(triggered()),this, SLOT(addBlock()));

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
        fileMenu->addAction(newFileAction);
        fileMenu->addAction(openAction);
        fileMenu->addAction(saveAction);
        fileMenu->addAction(closeAction);
        fileMenu->addSeparator();
        fileMenu->addAction(exitAction);

        pluginMenu = menuBar()->addMenu(tr("&Plugins"));
        pluginMenu->addAction(loadPluginsAction);
        pluginMenu->addAction(unLoadPluginsAction);

        helpMenu = menuBar()->addMenu(tr("&Help"));
        helpMenu->addAction(aboutAction);
        helpMenu->addAction(helpAction);
}

void MainWindow::createToolbars()
{
//    QPixmap start("start.png");
//    QPixmap pause("pause.png");
//    QPixmap stop("stop.png");
    QPixmap block("block.png");
//    QPixmap con("con.png");
//    QPixmap delete_con("delete_con.png");
//    QPixmap delete_block("delete_block.png");


    QToolBar *mainToolbar = new QToolBar(tr("Main"), this);/*addToolBar("Main toolbar");*/
    mainToolbar->addAction(addBlockAction);
//    mainToolbar->addAction(QIcon(con),"New connector");
//    mainToolbar->addAction(QIcon(delete_con),"Delete block");
//    mainToolbar->addAction(QIcon(delete_block),"Delete connector");
//    mainToolbar->show();
    mainToolbar->show();

    addToolBar(Qt::TopToolBarArea, mainToolbar);




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

//plugin menu
void MainWindow::loadPlugins() {
    if(this->pluginManager->loadPlugin(this))
    {
        QString message;
        std::vector<BlockFactoryInterface*> plugins = pluginManager->getPlugins();
        BlockFactoryInterface *factory = plugins[0];
        message = factory->getBlockName();
        statusBar()->showMessage(message);
    }
    else
    {
         QString message = tr("dupa");
         statusBar()->showMessage(message);
    }
}

void MainWindow::unLoadPlugins() {
    this->pluginManager->unloadPlugins();
}
//help menu
void MainWindow::about() { }
void MainWindow::help() { }



void MainWindow::addBlock()
{
  //this->renderArea->setState(ADD_BLOCK);
}

