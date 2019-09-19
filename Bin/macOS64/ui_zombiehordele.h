/********************************************************************************
** Form generated from reading UI file 'zombiehordele.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZOMBIEHORDELE_H
#define UI_ZOMBIEHORDELE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QUndoView>
#include <QtWidgets/QWidget>
#include "graphicsview.h"
#include "spritesetlist.h"

QT_BEGIN_NAMESPACE

class Ui_ZombieHordeLE
{
public:
    QAction *actionSet_Asset_Path;
    QAction *actionSave_Level;
    QAction *actionLoad_Level;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    GraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;
    QDockWidget *treeViewDock;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_2;
    QTreeView *treeView;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents_2;
    QGridLayout *gridLayout_3;
    QTreeWidget *gameObjectList;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_3;
    QGridLayout *gridLayout_4;
    SpriteSetList *listWidget_2;
    QDockWidget *undoViewDock;
    QWidget *dockWidgetContents_6;
    QGridLayout *gridLayout_5;
    QUndoView *undoViewList;

    void setupUi(QMainWindow *ZombieHordeLE)
    {
        if (ZombieHordeLE->objectName().isEmpty())
            ZombieHordeLE->setObjectName(QStringLiteral("ZombieHordeLE"));
        ZombieHordeLE->resize(934, 475);
        QIcon icon;
        icon.addFile(QStringLiteral(":/assets/window_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        ZombieHordeLE->setWindowIcon(icon);
        actionSet_Asset_Path = new QAction(ZombieHordeLE);
        actionSet_Asset_Path->setObjectName(QStringLiteral("actionSet_Asset_Path"));
        actionSet_Asset_Path->setEnabled(true);
        actionSave_Level = new QAction(ZombieHordeLE);
        actionSave_Level->setObjectName(QStringLiteral("actionSave_Level"));
        actionLoad_Level = new QAction(ZombieHordeLE);
        actionLoad_Level->setObjectName(QStringLiteral("actionLoad_Level"));
        centralWidget = new QWidget(ZombieHordeLE);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(5);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(5, 5, 5, 0);
        graphicsView = new GraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        QBrush brush(QColor(208, 208, 208, 255));
        brush.setStyle(Qt::Dense4Pattern);
        graphicsView->setBackgroundBrush(brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::NoBrush);
        graphicsView->setForegroundBrush(brush1);
        graphicsView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);
        graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
        graphicsView->setRubberBandSelectionMode(Qt::IntersectsItemBoundingRect);
        graphicsView->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing|QGraphicsView::DontClipPainter|QGraphicsView::DontSavePainterState);

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        ZombieHordeLE->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ZombieHordeLE);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 934, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        ZombieHordeLE->setMenuBar(menuBar);
        statusBar = new QStatusBar(ZombieHordeLE);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ZombieHordeLE->setStatusBar(statusBar);
        treeViewDock = new QDockWidget(ZombieHordeLE);
        treeViewDock->setObjectName(QStringLiteral("treeViewDock"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout_2 = new QGridLayout(dockWidgetContents);
        gridLayout_2->setSpacing(2);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        treeView = new QTreeView(dockWidgetContents);
        treeView->setObjectName(QStringLiteral("treeView"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy);
        treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);

        gridLayout_2->addWidget(treeView, 0, 0, 1, 1);

        treeViewDock->setWidget(dockWidgetContents);
        ZombieHordeLE->addDockWidget(static_cast<Qt::DockWidgetArea>(1), treeViewDock);
        dockWidget = new QDockWidget(ZombieHordeLE);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        gridLayout_3 = new QGridLayout(dockWidgetContents_2);
        gridLayout_3->setSpacing(2);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(2, 2, 2, 2);
        gameObjectList = new QTreeWidget(dockWidgetContents_2);
        gameObjectList->setObjectName(QStringLiteral("gameObjectList"));
        sizePolicy.setHeightForWidth(gameObjectList->sizePolicy().hasHeightForWidth());
        gameObjectList->setSizePolicy(sizePolicy);
        gameObjectList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        gameObjectList->setProperty("showDropIndicator", QVariant(true));
        gameObjectList->setDragEnabled(true);
        gameObjectList->setDragDropOverwriteMode(true);
        gameObjectList->setDragDropMode(QAbstractItemView::DragDrop);
        gameObjectList->setDefaultDropAction(Qt::MoveAction);
        gameObjectList->setAlternatingRowColors(true);
        gameObjectList->setSelectionMode(QAbstractItemView::ExtendedSelection);
        gameObjectList->setIconSize(QSize(16, 16));
        gameObjectList->setTextElideMode(Qt::ElideRight);
        gameObjectList->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
        gameObjectList->setAnimated(true);
        gameObjectList->setAllColumnsShowFocus(true);
        gameObjectList->setExpandsOnDoubleClick(false);
        gameObjectList->setColumnCount(2);

        gridLayout_3->addWidget(gameObjectList, 0, 0, 1, 1);

        dockWidget->setWidget(dockWidgetContents_2);
        ZombieHordeLE->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);
        dockWidget_2 = new QDockWidget(ZombieHordeLE);
        dockWidget_2->setObjectName(QStringLiteral("dockWidget_2"));
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QStringLiteral("dockWidgetContents_3"));
        gridLayout_4 = new QGridLayout(dockWidgetContents_3);
        gridLayout_4->setSpacing(5);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(5, 5, 5, 5);
        listWidget_2 = new SpriteSetList(dockWidgetContents_3);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        listWidget_2->setAcceptDrops(true);
        listWidget_2->setDragEnabled(true);
        listWidget_2->setDragDropMode(QAbstractItemView::DragDrop);
        listWidget_2->setDefaultDropAction(Qt::TargetMoveAction);

        gridLayout_4->addWidget(listWidget_2, 0, 0, 1, 1);

        dockWidget_2->setWidget(dockWidgetContents_3);
        ZombieHordeLE->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_2);
        undoViewDock = new QDockWidget(ZombieHordeLE);
        undoViewDock->setObjectName(QStringLiteral("undoViewDock"));
        dockWidgetContents_6 = new QWidget();
        dockWidgetContents_6->setObjectName(QStringLiteral("dockWidgetContents_6"));
        gridLayout_5 = new QGridLayout(dockWidgetContents_6);
        gridLayout_5->setSpacing(2);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(2, 2, 2, 2);
        undoViewList = new QUndoView(dockWidgetContents_6);
        undoViewList->setObjectName(QStringLiteral("undoViewList"));

        gridLayout_5->addWidget(undoViewList, 0, 0, 1, 1);

        undoViewDock->setWidget(dockWidgetContents_6);
        ZombieHordeLE->addDockWidget(static_cast<Qt::DockWidgetArea>(2), undoViewDock);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionSet_Asset_Path);
        menuFile->addSeparator();
        menuFile->addAction(actionSave_Level);
        menuFile->addAction(actionLoad_Level);

        retranslateUi(ZombieHordeLE);
        QObject::connect(actionSet_Asset_Path, SIGNAL(triggered()), ZombieHordeLE, SLOT(onSetAssetPath()));
        QObject::connect(actionSave_Level, SIGNAL(triggered()), ZombieHordeLE, SLOT(onSaveLevel()));
        QObject::connect(actionLoad_Level, SIGNAL(triggered()), ZombieHordeLE, SLOT(onLoadLevel()));

        QMetaObject::connectSlotsByName(ZombieHordeLE);
    } // setupUi

    void retranslateUi(QMainWindow *ZombieHordeLE)
    {
        ZombieHordeLE->setWindowTitle(QApplication::translate("ZombieHordeLE", "Zombie Horde Level Editor", Q_NULLPTR));
        actionSet_Asset_Path->setText(QApplication::translate("ZombieHordeLE", "Set Asset Path", Q_NULLPTR));
        actionSave_Level->setText(QApplication::translate("ZombieHordeLE", "Save Level", Q_NULLPTR));
        actionLoad_Level->setText(QApplication::translate("ZombieHordeLE", "Load Level", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("ZombieHordeLE", "File", Q_NULLPTR));
        treeViewDock->setWindowTitle(QApplication::translate("ZombieHordeLE", "Project View", Q_NULLPTR));
        dockWidget->setWindowTitle(QApplication::translate("ZombieHordeLE", "Object List", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = gameObjectList->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("ZombieHordeLE", "Value", Q_NULLPTR));
        ___qtreewidgetitem->setText(0, QApplication::translate("ZombieHordeLE", "Key", Q_NULLPTR));
        dockWidget_2->setWindowTitle(QApplication::translate("ZombieHordeLE", "Sprite Sets", Q_NULLPTR));
        undoViewDock->setWindowTitle(QApplication::translate("ZombieHordeLE", "History View", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ZombieHordeLE: public Ui_ZombieHordeLE {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZOMBIEHORDELE_H
