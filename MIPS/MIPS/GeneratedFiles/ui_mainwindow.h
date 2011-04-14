/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Apr 14 11:02:13 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QScrollArea>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionBack;
    QAction *actionForward;
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QAction *actionActualSize;
    QAction *actionAbout;
    QAction *actionFitSize;
    QAction *actionRename;
    QAction *actionMark;
    QAction *actionSave;
    QAction *actionGauss;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Edit;
    QMenu *menu_Preview;
    QMenu *menu_Sharpening;
    QMenu *menu_Smoothness;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QTreeView *treeView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(467, 340);
        actionBack = new QAction(MainWindow);
        actionBack->setObjectName(QString::fromUtf8("actionBack"));
        actionBack->setCheckable(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/MIPS/images/previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBack->setIcon(icon);
        actionForward = new QAction(MainWindow);
        actionForward->setObjectName(QString::fromUtf8("actionForward"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/MIPS/images/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionForward->setIcon(icon1);
        actionZoomIn = new QAction(MainWindow);
        actionZoomIn->setObjectName(QString::fromUtf8("actionZoomIn"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/MIPS/images/zoomin.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoomIn->setIcon(icon2);
        actionZoomOut = new QAction(MainWindow);
        actionZoomOut->setObjectName(QString::fromUtf8("actionZoomOut"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/MIPS/images/zoomout.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoomOut->setIcon(icon3);
        actionActualSize = new QAction(MainWindow);
        actionActualSize->setObjectName(QString::fromUtf8("actionActualSize"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/MIPS/images/actualsize.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionActualSize->setIcon(icon4);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/MIPS/images/about.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon5);
        actionFitSize = new QAction(MainWindow);
        actionFitSize->setObjectName(QString::fromUtf8("actionFitSize"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/MIPS/images/fitsize.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFitSize->setIcon(icon6);
        actionRename = new QAction(MainWindow);
        actionRename->setObjectName(QString::fromUtf8("actionRename"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/MIPS/images/rename.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionRename->setIcon(icon7);
        actionMark = new QAction(MainWindow);
        actionMark->setObjectName(QString::fromUtf8("actionMark"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/MIPS/images/mark.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMark->setIcon(icon8);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/MIPS/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon9);
        actionGauss = new QAction(MainWindow);
        actionGauss->setObjectName(QString::fromUtf8("actionGauss"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 172, 241));
        scrollAreaWidgetContents->setAutoFillBackground(true);
        horizontalLayout = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setScaledContents(true);

        horizontalLayout->addWidget(label);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 467, 23));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_Edit = new QMenu(menuBar);
        menu_Edit->setObjectName(QString::fromUtf8("menu_Edit"));
        menu_Preview = new QMenu(menuBar);
        menu_Preview->setObjectName(QString::fromUtf8("menu_Preview"));
        menu_Sharpening = new QMenu(menuBar);
        menu_Sharpening->setObjectName(QString::fromUtf8("menu_Sharpening"));
        menu_Smoothness = new QMenu(menuBar);
        menu_Smoothness->setObjectName(QString::fromUtf8("menu_Smoothness"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setFocusPolicy(Qt::NoFocus);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        treeView = new QTreeView(dockWidgetContents);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        verticalLayout->addWidget(treeView);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Edit->menuAction());
        menuBar->addAction(menu_Preview->menuAction());
        menuBar->addAction(menu_Sharpening->menuAction());
        menuBar->addAction(menu_Smoothness->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menu_File->addAction(actionSave);
        menu_Edit->addAction(actionRename);
        menu_Edit->addAction(actionMark);
        menu_Preview->addAction(actionBack);
        menu_Preview->addAction(actionForward);
        menu_Preview->addAction(actionZoomIn);
        menu_Preview->addAction(actionZoomOut);
        menu_Preview->addAction(actionActualSize);
        menu_Preview->addAction(actionFitSize);
        menu_Smoothness->addAction(actionGauss);
        menuHelp->addAction(actionAbout);
        mainToolBar->addAction(actionBack);
        mainToolBar->addAction(actionForward);
        mainToolBar->addAction(actionZoomIn);
        mainToolBar->addAction(actionZoomOut);
        mainToolBar->addAction(actionActualSize);
        mainToolBar->addAction(actionFitSize);
        mainToolBar->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionBack->setText(QApplication::translate("MainWindow", "Back", 0, QApplication::UnicodeUTF8));
        actionBack->setShortcut(QApplication::translate("MainWindow", "Up", 0, QApplication::UnicodeUTF8));
        actionForward->setText(QApplication::translate("MainWindow", "Forward", 0, QApplication::UnicodeUTF8));
        actionForward->setShortcut(QApplication::translate("MainWindow", "Down", 0, QApplication::UnicodeUTF8));
        actionZoomIn->setText(QApplication::translate("MainWindow", "ZoomIn", 0, QApplication::UnicodeUTF8));
        actionZoomIn->setShortcut(QApplication::translate("MainWindow", "+", 0, QApplication::UnicodeUTF8));
        actionZoomOut->setText(QApplication::translate("MainWindow", "ZoomOut", 0, QApplication::UnicodeUTF8));
        actionZoomOut->setShortcut(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        actionActualSize->setText(QApplication::translate("MainWindow", "ActualSize", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionActualSize->setToolTip(QApplication::translate("MainWindow", "ActualSize", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionAbout->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", 0, QApplication::UnicodeUTF8));
        actionFitSize->setText(QApplication::translate("MainWindow", "FitSize", 0, QApplication::UnicodeUTF8));
        actionRename->setText(QApplication::translate("MainWindow", "Rename", 0, QApplication::UnicodeUTF8));
        actionMark->setText(QApplication::translate("MainWindow", "Mark", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
        actionGauss->setText(QApplication::translate("MainWindow", "Gauss", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menu_Edit->setTitle(QApplication::translate("MainWindow", "&Edit", 0, QApplication::UnicodeUTF8));
        menu_Preview->setTitle(QApplication::translate("MainWindow", "&Preview", 0, QApplication::UnicodeUTF8));
        menu_Sharpening->setTitle(QApplication::translate("MainWindow", "&Sharpening", 0, QApplication::UnicodeUTF8));
        menu_Smoothness->setTitle(QApplication::translate("MainWindow", "S&moothness", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
