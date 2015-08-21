#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <QListView>
#include <QStringListModel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QAction>

#include "observable.h"

class Toolbox :
        public QWidget,
        public Observable
{
    Q_OBJECT
public:
    explicit Toolbox(QWidget *parent = 0);
    void addNewBlock(QString blockName);
    void reloadBlockList(QStringList blockNames);
private:

    QListView *blockList;
    QStringListModel *blockListModel;

    QPushButton* newConnectionButton;
    QPushButton* deleteConnectionButton;
    QPushButton* deleteBlockButton;

signals:

public slots:
    void blockSelected(QModelIndex);
    void addNewConnection();
    void deleteConnection();
    void deleteBlock();
};

#endif // TOOLBOX_H
