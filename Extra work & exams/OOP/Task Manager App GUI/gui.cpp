//
// Created by bia on 30/06/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GUI.h" resolved

#include "gui.h"
#include "ui_GUI.h"
#include <iostream>
#include <QMessageBox>

GUI::GUI(Programmer* p, ProgrammerRepository &prepo, TaskRepository &trepo, QWidget *parent) :
        QWidget(parent), ui(new Ui::GUI), p(p), prepo(prepo), trepo(trepo) {
    ui->setupUi(this);
    this->trepo.addObserver(this);
    this->populate();
    this->connect();
}

GUI::~GUI() {
    delete ui;
}

void GUI::populate() {
    this->ui->listWidget->clear();
    this->trepo.sort();
    for(auto elem : this->trepo.getAll()){
        if(elem.getStatus() == " open")
            this->ui->listWidget->addItem(QString::fromStdString("0 | " + elem.getDescription() + " | " + elem.getStatus()));
        else this->ui->listWidget->addItem(QString::fromStdString(std::to_string(elem.getId()) + " | " + elem.getDescription() + " | " + elem.getStatus()));
    }
}

void GUI::connect() {
    QObject::connect(this->ui->listWidget, &QListWidget::itemSelectionChanged, this, [&]() {
        int index = this->ui->listWidget->currentRow();
        if(this->trepo[index].getStatus() == " open")
            this->ui->pushButton_2->setEnabled(true);
//        else
//            this->ui->pushButton_2->setDisabled(true);

        if(this->trepo[index].getStatus() != " in progress")
            this->ui->pushButton_3->setDisabled(true);
        else {
            if (this->trepo[index].getId() == this->p->getId())
                this->ui->pushButton_3->setEnabled(true);
            else
                this->ui->pushButton_3->setDisabled(true);
        }
    });

    QObject::connect(this->ui->pushButton_4, &QPushButton::clicked, this, [&]() {
        this->trepo.add(Task(this->ui->lineEdit->text().toStdString(), " open", 0));
        this->trepo.writeToFile();
        this->trepo.sort();
    });

    QObject::connect(this->ui->pushButton, &QPushButton::clicked, this, [&]() {
        int index = this->ui->listWidget->currentRow();
        this->trepo.remove(index);
        this->trepo.writeToFile();
        this->trepo.sort();
    });
    QObject::connect(this->ui->pushButton_2, &QPushButton::clicked, this, [&]() {
        int index = this->ui->listWidget->currentRow();

        if(this->trepo[index].getStatus() != " open")
            try {
                throw CustomException();
            } catch(CustomException c) {
                QMessageBox* win = new QMessageBox;
                win->setText(c.what());
                win->show();
            }
        else {

            this->ui->listWidget->item(index)->setText(
                    this->ui->listWidget->item(index)->text() + QString::fromStdString(" | " + p->getName()));

//        this->ui->listWidget->removeItemWidget(this->ui->listWidget->item(index));
//        this->ui->listWidget->addItem(QString::fromStdString(std::to_string(this->trepo[index].getId()) + " | " + this->trepo[index].getDescription() + " | " + this->trepo[index].getStatus() + " | " + p->getName()));
            this->trepo[index].setStatus(" in progress");
            this->trepo[index].setId(this->p->getId());
            this->trepo.notify();
            this->trepo.writeToFile();
        }
    });
    QObject::connect(this->ui->pushButton_3, &QPushButton::clicked, this, [&]() {
        int index = this->ui->listWidget->currentRow();
        this->trepo[index].setStatus(" closed");
        this->trepo.notify();
        this->trepo.writeToFile();
    });
}

void GUI::update() {
    this->populate();
}
