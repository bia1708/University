/********************************************************************************
** Form generated from reading UI file 'writergui.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WRITERGUI_H
#define UI_WRITERGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WriterGUI
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;

    void setupUi(QWidget *WriterGUI)
    {
        if (WriterGUI->objectName().isEmpty())
            WriterGUI->setObjectName(QString::fromUtf8("WriterGUI"));
        WriterGUI->resize(400, 373);
        verticalLayout = new QVBoxLayout(WriterGUI);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableView = new QTableView(WriterGUI);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        pushButton_2 = new QPushButton(WriterGUI);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(WriterGUI);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        lineEdit = new QLineEdit(WriterGUI);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(WriterGUI);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        verticalLayout->addWidget(lineEdit_2);

        pushButton = new QPushButton(WriterGUI);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(WriterGUI);

        QMetaObject::connectSlotsByName(WriterGUI);
    } // setupUi

    void retranslateUi(QWidget *WriterGUI)
    {
        WriterGUI->setWindowTitle(QCoreApplication::translate("WriterGUI", "WriterGUI", nullptr));
        pushButton_2->setText(QCoreApplication::translate("WriterGUI", "Accept", nullptr));
        pushButton_3->setText(QCoreApplication::translate("WriterGUI", "Develop", nullptr));
        pushButton->setText(QCoreApplication::translate("WriterGUI", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WriterGUI: public Ui_WriterGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WRITERGUI_H
