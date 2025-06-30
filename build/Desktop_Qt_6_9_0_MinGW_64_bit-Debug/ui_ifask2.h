/********************************************************************************
** Form generated from reading UI file 'ifask2.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IFASK2_H
#define UI_IFASK2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ifask2
{
public:
    QWidget *ssda;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ifask2)
    {
        if (ifask2->objectName().isEmpty())
            ifask2->setObjectName("ifask2");
        ifask2->resize(300, 500);
        ifask2->setMinimumSize(QSize(300, 500));
        ifask2->setMaximumSize(QSize(400, 500));
        ssda = new QWidget(ifask2);
        ssda->setObjectName("ssda");
        ssda->setEnabled(false);
        ifask2->setCentralWidget(ssda);
        menubar = new QMenuBar(ifask2);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 300, 25));
        ifask2->setMenuBar(menubar);
        statusbar = new QStatusBar(ifask2);
        statusbar->setObjectName("statusbar");
        ifask2->setStatusBar(statusbar);

        retranslateUi(ifask2);

        QMetaObject::connectSlotsByName(ifask2);
    } // setupUi

    void retranslateUi(QMainWindow *ifask2)
    {
        ifask2->setWindowTitle(QCoreApplication::translate("ifask2", "panchat", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ifask2: public Ui_ifask2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IFASK2_H
