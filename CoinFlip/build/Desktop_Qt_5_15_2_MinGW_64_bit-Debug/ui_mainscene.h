/********************************************************************************
** Form generated from reading UI file 'mainscene.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINSCENE_H
#define UI_MAINSCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainscene
{
public:
    QAction *actionquit;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;

    void setupUi(QMainWindow *mainscene)
    {
        if (mainscene->objectName().isEmpty())
            mainscene->setObjectName(QString::fromUtf8("mainscene"));
        mainscene->resize(800, 600);
        actionquit = new QAction(mainscene);
        actionquit->setObjectName(QString::fromUtf8("actionquit"));
        centralwidget = new QWidget(mainscene);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        mainscene->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainscene);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        mainscene->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionquit);

        retranslateUi(mainscene);

        QMetaObject::connectSlotsByName(mainscene);
    } // setupUi

    void retranslateUi(QMainWindow *mainscene)
    {
        mainscene->setWindowTitle(QCoreApplication::translate("mainscene", "mainscene", nullptr));
        actionquit->setText(QCoreApplication::translate("mainscene", "\351\200\200\345\207\272", nullptr));
        menu->setTitle(QCoreApplication::translate("mainscene", "\345\274\200\345\247\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainscene: public Ui_mainscene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSCENE_H
