/********************************************************************************
** Form generated from reading UI file 'GraphUI.ui'
**
** Created: Wed Feb 20 14:52:16 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHUI_H
#define UI_GRAPHUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraphUIClass
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionCheck_paths_between_two_glyphs;
    QAction *actionDelete;
    QAction *actionCopy;
    QAction *actionCut;
    QAction *actionPaste;
    QAction *actionSave;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuDiagram;
    QMenu *menuEdit;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GraphUIClass)
    {
        if (GraphUIClass->objectName().isEmpty())
            GraphUIClass->setObjectName(QString::fromUtf8("GraphUIClass"));
        GraphUIClass->resize(721, 515);
        GraphUIClass->setMouseTracking(false);
        actionOpen = new QAction(GraphUIClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("./Resources/openfile.png");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("Resources/openfile.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionOpen->setIcon(icon);
        actionExit = new QAction(GraphUIClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon1;
        iconThemeName = QString::fromUtf8("./Resources/close.png");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8("Resources/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionExit->setIcon(icon1);
        actionCheck_paths_between_two_glyphs = new QAction(GraphUIClass);
        actionCheck_paths_between_two_glyphs->setObjectName(QString::fromUtf8("actionCheck_paths_between_two_glyphs"));
        QIcon icon2;
        iconThemeName = QString::fromUtf8("./Resources/path.png");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QString::fromUtf8("Resources/path.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionCheck_paths_between_two_glyphs->setIcon(icon2);
        actionDelete = new QAction(GraphUIClass);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("Resources/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete->setIcon(icon3);
        actionCopy = new QAction(GraphUIClass);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("Resources/copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopy->setIcon(icon4);
        actionCut = new QAction(GraphUIClass);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("Resources/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCut->setIcon(icon5);
        actionPaste = new QAction(GraphUIClass);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("Resources/paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPaste->setIcon(icon6);
        actionSave = new QAction(GraphUIClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("Resources/savefile.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon7);
        centralWidget = new QWidget(GraphUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        GraphUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GraphUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 721, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuDiagram = new QMenu(menuBar);
        menuDiagram->setObjectName(QString::fromUtf8("menuDiagram"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        GraphUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GraphUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        GraphUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GraphUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GraphUIClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuDiagram->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuDiagram->addAction(actionCheck_paths_between_two_glyphs);
        menuEdit->addAction(actionDelete);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionPaste);

        retranslateUi(GraphUIClass);

        QMetaObject::connectSlotsByName(GraphUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *GraphUIClass)
    {
        GraphUIClass->setWindowTitle(QApplication::translate("GraphUIClass", "Activity Diagram Drawing Tool", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("GraphUIClass", "Open", 0, QApplication::UnicodeUTF8));
        actionOpen->setShortcut(QApplication::translate("GraphUIClass", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("GraphUIClass", "Exit", 0, QApplication::UnicodeUTF8));
        actionExit->setShortcut(QApplication::translate("GraphUIClass", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        actionCheck_paths_between_two_glyphs->setText(QApplication::translate("GraphUIClass", "Check paths between two glyphs", 0, QApplication::UnicodeUTF8));
        actionCheck_paths_between_two_glyphs->setShortcut(QApplication::translate("GraphUIClass", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        actionDelete->setText(QApplication::translate("GraphUIClass", "Delete", 0, QApplication::UnicodeUTF8));
        actionDelete->setShortcut(QApplication::translate("GraphUIClass", "Del", 0, QApplication::UnicodeUTF8));
        actionCopy->setText(QApplication::translate("GraphUIClass", "Copy", 0, QApplication::UnicodeUTF8));
        actionCopy->setShortcut(QApplication::translate("GraphUIClass", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        actionCut->setText(QApplication::translate("GraphUIClass", "Cut", 0, QApplication::UnicodeUTF8));
        actionCut->setShortcut(QApplication::translate("GraphUIClass", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        actionPaste->setText(QApplication::translate("GraphUIClass", "Paste", 0, QApplication::UnicodeUTF8));
        actionPaste->setShortcut(QApplication::translate("GraphUIClass", "Ctrl+V", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("GraphUIClass", "Save", 0, QApplication::UnicodeUTF8));
        actionSave->setShortcut(QApplication::translate("GraphUIClass", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("GraphUIClass", "File", 0, QApplication::UnicodeUTF8));
        menuDiagram->setTitle(QApplication::translate("GraphUIClass", "Diagram", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("GraphUIClass", "Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GraphUIClass: public Ui_GraphUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHUI_H
