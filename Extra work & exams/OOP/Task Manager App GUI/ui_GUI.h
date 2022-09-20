/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton;
    QPushButton *pushButton_3;

    void setupUi(QWidget *GUI)
    {
        if (GUI->objectName().isEmpty())
            GUI->setObjectName(QString::fromUtf8("GUI"));
        GUI->resize(400, 300);
        verticalLayout = new QVBoxLayout(GUI);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(GUI);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setMinimumSize(QSize(0, 99));

        verticalLayout->addWidget(listWidget);

        lineEdit = new QLineEdit(GUI);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        pushButton_2 = new QPushButton(GUI);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton_4 = new QPushButton(GUI);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);

        pushButton = new QPushButton(GUI);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_3 = new QPushButton(GUI);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);


        retranslateUi(GUI);

        QMetaObject::connectSlotsByName(GUI);
    } // setupUi

    void retranslateUi(QWidget *GUI)
    {
        GUI->setWindowTitle(QCoreApplication::translate("GUI", "GUI", nullptr));
        pushButton_2->setText(QCoreApplication::translate("GUI", "Start", nullptr));
        pushButton_4->setText(QCoreApplication::translate("GUI", "Add", nullptr));
        pushButton->setText(QCoreApplication::translate("GUI", "Delete", nullptr));
        pushButton_3->setText(QCoreApplication::translate("GUI", "Done", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI: public Ui_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
