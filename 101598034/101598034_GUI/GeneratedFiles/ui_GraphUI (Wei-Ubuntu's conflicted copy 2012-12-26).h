/********************************************************************************
** Form generated from reading UI file 'GraphUI.ui'
**
** Created: Sat Dec 22 22:08:48 2012
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
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuDiagram;
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
        GraphUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GraphUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        GraphUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GraphUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GraphUIClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuDiagram->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuDiagram->addAction(actionCheck_paths_between_two_glyphs);

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
        menuFile->setTitle(QApplication::translate("GraphUIClass", "File", 0, QApplication::UnicodeUTF8));
        menuDiagram->setTitle(QApplication::translate("GraphUIClass", "Diagram", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GraphUIClass: public Ui_GraphUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHUI_H
