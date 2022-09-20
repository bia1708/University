/********************************************************************************
** Form generated from reading UI file 'usergui.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERGUI_H
#define UI_USERGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserGUI
{
public:
    QListWidget *listWidget;
    QListWidget *listWidget_2;
    QListWidget *listWidget_3;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_3;
    QListWidget *listWidget_4;

    void setupUi(QWidget *UserGUI)
    {
        if (UserGUI->objectName().isEmpty())
            UserGUI->setObjectName(QString::fromUtf8("UserGUI"));
        UserGUI->resize(504, 398);
        listWidget = new QListWidget(UserGUI);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(0, 31, 151, 191));
        listWidget_2 = new QListWidget(UserGUI);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));
        listWidget_2->setGeometry(QRect(160, 31, 171, 191));
        listWidget_3 = new QListWidget(UserGUI);
        listWidget_3->setObjectName(QString::fromUtf8("listWidget_3"));
        listWidget_3->setGeometry(QRect(340, 30, 161, 191));
        pushButton = new QPushButton(UserGUI);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(380, 360, 83, 29));
        lineEdit = new QLineEdit(UserGUI);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(360, 320, 113, 28));
        lineEdit_2 = new QLineEdit(UserGUI);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(190, 240, 113, 28));
        pushButton_2 = new QPushButton(UserGUI);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(200, 280, 83, 29));
        lineEdit_3 = new QLineEdit(UserGUI);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(190, 320, 113, 28));
        pushButton_3 = new QPushButton(UserGUI);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(210, 360, 83, 29));
        listWidget_4 = new QListWidget(UserGUI);
        listWidget_4->setObjectName(QString::fromUtf8("listWidget_4"));
        listWidget_4->setGeometry(QRect(340, 240, 151, 71));

        retranslateUi(UserGUI);

        QMetaObject::connectSlotsByName(UserGUI);
    } // setupUi

    void retranslateUi(QWidget *UserGUI)
    {
        UserGUI->setWindowTitle(QCoreApplication::translate("UserGUI", "UserGUI", nullptr));
        pushButton->setText(QCoreApplication::translate("UserGUI", "Subscribe", nullptr));
        pushButton_2->setText(QCoreApplication::translate("UserGUI", "Post", nullptr));
        pushButton_3->setText(QCoreApplication::translate("UserGUI", "Update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserGUI: public Ui_UserGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERGUI_H
