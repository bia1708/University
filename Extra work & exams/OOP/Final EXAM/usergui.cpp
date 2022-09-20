//
// Created by bia on 06/07/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_UserGUI.h" resolved

#include "usergui.h"
#include "ui_UserGUI.h"
#include <iostream>
#include <QMessageBox>

UserGUI::UserGUI(User* u, UserRepo& urepo, TopicRepo& trepo, PostRepo& repo, QWidget *parent) :
        QWidget(parent), ui(new Ui::UserGUI), u(u), urepo(urepo), trepo(trepo), repo(repo) {
    this->repo.addObserver(this);
    this->uname = u->getName();
    ui->setupUi(this);
    this->populate();
    this->connect();

}

UserGUI::~UserGUI() {
    delete ui;
}

void UserGUI::update() {
    this->populate();
}

void UserGUI::connect() {
    QObject::connect(this->ui->pushButton, &QPushButton::pressed, this, [&](){
        int index = this->ui->listWidget_4->currentRow();

        this->trepo.update(this->trepo[index], *u);

        this->ui->listWidget_3->clear();
        for(auto el : this->trepo.getByUser(*u)){
            this->ui->listWidget_3->addItem(QString::fromStdString(el.getName()));
        }
        this->trepo.writeToFile();

//        std::string str = this->ui->lineEdit->text().toStdString();
//        std::vector<User> v;
//        v.emplace_back(*u);
//        Topic t{str, v};
//        this->trepo.update(t, *u);
    });

    QObject::connect(this->ui->pushButton_2, &QPushButton::pressed, this, [&]() {
        std::string str = this->ui->lineEdit_2->text().toStdString();
        if(str.size() < 3){
            auto* win = new QMessageBox;
            win->setText(QString::fromStdString("Too little characters!"));
            win->show();
        } else {

            timestamp t{6, 13};
            Post p{(int) this->repo.getAll().size() + 1, str, t, u->getName()};
            this->repo.add(p);
        this->repo.writeToFile();
        this->repo.notify();
        }
    });

    QObject::connect(this->ui->pushButton_3, &QPushButton::pressed, this, [&]() {
        std::string str = this->ui->lineEdit_2->text().toStdString();
        int index = this->ui->listWidget_2->currentRow();
        QListWidgetItem* i = this->ui->listWidget_2->item(index);
        int id = (int)i->text().toStdString()[0] - 48;

        this->repo[id].setText(str);
        this->repo.writeToFile();

        this->repo.notify();
    });
}

void UserGUI::populate() {
    *this->u = this->urepo.getByName(uname);

    this->ui->listWidget->clear();
    this->ui->listWidget_2->clear();
    this->ui->listWidget_3->clear();

    std::vector<Post> arr;
    for(auto el : this->trepo.getByUser(*u))
        for(auto el1 : this->repo.getByString(el.getName()))
            arr.push_back(el1);

    for(auto el : arr){
        this->ui->listWidget->addItem(QString::fromStdString(std::to_string(el.getId()) + " | " + el.getText() + " | " +
                                                                     std::to_string(el.getDate().day) + "-" + std::to_string(el.getDate().time) + " | " + el.getUser()));
    }

    for(auto el: this->repo.getByUser(*u)){
        this->ui->listWidget_2->addItem(QString::fromStdString(std::to_string(el.getId()) + " | " + el.getText() + " | " +
                                                               std::to_string(el.getDate().day) + "-" + std::to_string(el.getDate().time) + " | " + el.getUser()));
    }

    for(auto el : this->trepo.getByUser(*u)){
        this->ui->listWidget_3->addItem(QString::fromStdString(el.getName()));
    }

    for(auto el : this->trepo.getAll()){
        this->ui->listWidget_4->addItem(QString::fromStdString(el.getName()));
    }
}




