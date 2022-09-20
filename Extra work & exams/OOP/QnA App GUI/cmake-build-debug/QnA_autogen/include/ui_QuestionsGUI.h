/********************************************************************************
** Form generated from reading UI file 'questionsgui.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUESTIONSGUI_H
#define UI_QUESTIONSGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuestionsGUI
{
public:
    QListWidget *listWidget;
    QListWidget *listWidget_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_2;
    QSpinBox *spinBox;

    void setupUi(QWidget *QuestionsGUI)
    {
        if (QuestionsGUI->objectName().isEmpty())
            QuestionsGUI->setObjectName(QString::fromUtf8("QuestionsGUI"));
        QuestionsGUI->resize(541, 343);
        listWidget = new QListWidget(QuestionsGUI);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(11, 11, 256, 192));
        listWidget_2 = new QListWidget(QuestionsGUI);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));
        listWidget_2->setGeometry(QRect(274, 11, 256, 192));
        lineEdit = new QLineEdit(QuestionsGUI);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(20, 260, 113, 28));
        pushButton = new QPushButton(QuestionsGUI);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(140, 260, 111, 29));
        lineEdit_2 = new QLineEdit(QuestionsGUI);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(20, 300, 113, 28));
        pushButton_2 = new QPushButton(QuestionsGUI);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(140, 300, 111, 29));
        spinBox = new QSpinBox(QuestionsGUI);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(20, 220, 48, 29));

        retranslateUi(QuestionsGUI);

        QMetaObject::connectSlotsByName(QuestionsGUI);
    } // setupUi

    void retranslateUi(QWidget *QuestionsGUI)
    {
        QuestionsGUI->setWindowTitle(QCoreApplication::translate("QuestionsGUI", "QuestionsGUI", nullptr));
        pushButton->setText(QCoreApplication::translate("QuestionsGUI", "Add Question", nullptr));
        pushButton_2->setText(QCoreApplication::translate("QuestionsGUI", "Add Answer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QuestionsGUI: public Ui_QuestionsGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUESTIONSGUI_H
