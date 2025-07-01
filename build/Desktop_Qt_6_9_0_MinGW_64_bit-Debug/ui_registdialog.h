/********************************************************************************
** Form generated from reading UI file 'registdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTDIALOG_H
#define UI_REGISTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegistDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QLabel *err_tip;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *password_1;
    QLineEdit *password_2;
    QHBoxLayout *horizontalLayout;
    QLabel *confirmed_1;
    QLineEdit *confirmed_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *email;
    QLineEdit *email_edit;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *lineEdit;
    QPushButton *qpush;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *login_back;

    void setupUi(QDialog *RegistDialog)
    {
        if (RegistDialog->objectName().isEmpty())
            RegistDialog->setObjectName("RegistDialog");
        RegistDialog->resize(321, 456);
        verticalLayout_2 = new QVBoxLayout(RegistDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        widget = new QWidget(RegistDialog);
        widget->setObjectName("widget");

        verticalLayout->addWidget(widget);

        err_tip = new QLabel(RegistDialog);
        err_tip->setObjectName("err_tip");
        err_tip->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        err_tip->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(err_tip);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(RegistDialog);
        label->setObjectName("label");

        horizontalLayout_3->addWidget(label);

        lineEdit_2 = new QLineEdit(RegistDialog);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setMinimumSize(QSize(80, 0));

        horizontalLayout_3->addWidget(lineEdit_2);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        password_1 = new QLabel(RegistDialog);
        password_1->setObjectName("password_1");

        horizontalLayout_2->addWidget(password_1);

        password_2 = new QLineEdit(RegistDialog);
        password_2->setObjectName("password_2");
        password_2->setMinimumSize(QSize(80, 0));

        horizontalLayout_2->addWidget(password_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        confirmed_1 = new QLabel(RegistDialog);
        confirmed_1->setObjectName("confirmed_1");

        horizontalLayout->addWidget(confirmed_1);

        confirmed_2 = new QLineEdit(RegistDialog);
        confirmed_2->setObjectName("confirmed_2");
        confirmed_2->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(confirmed_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        email = new QLabel(RegistDialog);
        email->setObjectName("email");

        horizontalLayout_4->addWidget(email);

        email_edit = new QLineEdit(RegistDialog);
        email_edit->setObjectName("email_edit");
        email_edit->setMinimumSize(QSize(80, 0));

        horizontalLayout_4->addWidget(email_edit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        lineEdit = new QLineEdit(RegistDialog);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout_6->addWidget(lineEdit);

        qpush = new QPushButton(RegistDialog);
        qpush->setObjectName("qpush");

        horizontalLayout_6->addWidget(qpush);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        login_back = new QPushButton(RegistDialog);
        login_back->setObjectName("login_back");

        horizontalLayout_7->addWidget(login_back);


        verticalLayout->addLayout(horizontalLayout_7);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(RegistDialog);

        QMetaObject::connectSlotsByName(RegistDialog);
    } // setupUi

    void retranslateUi(QDialog *RegistDialog)
    {
        RegistDialog->setWindowTitle(QCoreApplication::translate("RegistDialog", "Dialog", nullptr));
        err_tip->setText(QCoreApplication::translate("RegistDialog", "\351\224\231\350\257\257\346\217\220\347\244\272", nullptr));
        label->setText(QCoreApplication::translate("RegistDialog", "\347\224\250\346\210\267\345\220\215", nullptr));
        password_1->setText(QCoreApplication::translate("RegistDialog", "\345\257\206\347\240\201", nullptr));
        confirmed_1->setText(QCoreApplication::translate("RegistDialog", "\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        email->setText(QCoreApplication::translate("RegistDialog", "\346\263\250\345\206\214\351\202\256\347\256\261", nullptr));
        qpush->setText(QCoreApplication::translate("RegistDialog", "\350\216\267\345\217\226\351\252\214\350\257\201\347\240\201", nullptr));
        login_back->setText(QCoreApplication::translate("RegistDialog", "\350\277\224\345\233\236\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegistDialog: public Ui_RegistDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTDIALOG_H
