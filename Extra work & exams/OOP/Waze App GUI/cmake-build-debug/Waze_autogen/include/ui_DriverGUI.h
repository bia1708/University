/********************************************************************************
** Form generated from reading UI file 'drivergui.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRIVERGUI_H
#define UI_DRIVERGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DriverGUI
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSlider *horizontalSlider;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QListWidget *listWidget;

    void setupUi(QWidget *DriverGUI)
    {
        if (DriverGUI->objectName().isEmpty())
            DriverGUI->setObjectName(QString::fromUtf8("DriverGUI"));
        DriverGUI->resize(488, 439);
        label = new QLabel(DriverGUI);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 10, 291, 20));
        lineEdit = new QLineEdit(DriverGUI);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(140, 310, 113, 28));
        pushButton = new QPushButton(DriverGUI);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 270, 83, 29));
        pushButton_2 = new QPushButton(DriverGUI);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(280, 390, 83, 29));
        horizontalSlider = new QSlider(DriverGUI);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(150, 240, 160, 18));
        horizontalSlider->setOrientation(Qt::Horizontal);
        lineEdit_2 = new QLineEdit(DriverGUI);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(140, 350, 113, 28));
        lineEdit_3 = new QLineEdit(DriverGUI);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(140, 390, 113, 28));
        label_2 = new QLabel(DriverGUI);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(42, 310, 81, 20));
        label_3 = new QLabel(DriverGUI);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(42, 350, 81, 20));
        label_4 = new QLabel(DriverGUI);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(42, 390, 81, 20));
        listWidget = new QListWidget(DriverGUI);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 40, 461, 192));

        retranslateUi(DriverGUI);

        QMetaObject::connectSlotsByName(DriverGUI);
    } // setupUi

    void retranslateUi(QWidget *DriverGUI)
    {
        DriverGUI->setWindowTitle(QCoreApplication::translate("DriverGUI", "DriverGUI", nullptr));
        label->setText(QCoreApplication::translate("DriverGUI", "TextLabel", nullptr));
        pushButton->setText(QCoreApplication::translate("DriverGUI", "Validate", nullptr));
        pushButton_2->setText(QCoreApplication::translate("DriverGUI", "Save", nullptr));
        label_2->setText(QCoreApplication::translate("DriverGUI", "Description", nullptr));
        label_3->setText(QCoreApplication::translate("DriverGUI", "Latitude", nullptr));
        label_4->setText(QCoreApplication::translate("DriverGUI", "Longitude", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DriverGUI: public Ui_DriverGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRIVERGUI_H
