//
// Created by bia on 26/05/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GUI.h" resolved

#include "gui.h"
#include "ui_GUI.h"


GUI::GUI(Repository repo, QWidget *parent) :
        QWidget(parent), ui(new Ui::GUI), repo(repo) {
    ui->setupUi(this);
    this->repo = repo;

    this->writeWidget();
    this->connectAll();
}

GUI::~GUI() {
    delete ui;
}

void GUI::writeWidget() {
    this->ui->listWidget->clear();
    std::vector<Document> vector = this->repo.getAll();
    for (int i = 0; i < vector.size(); ++i) {
        auto *item = new QListWidgetItem;
        std::string keywords = "";
        for(auto keyword: vector[i].getKeywords())
            keywords += keyword + " ";
        QString string (QString::fromStdString(vector[i].getName()) + " " +
                        QString::fromStdString(keywords) + " " + QString::fromStdString(vector[i].getContent()));
        item->setText(string);
        this->ui->listWidget->addItem(item);
    }
}

void GUI::connectAll() {
    connect(this->ui->lineEdit, &QLineEdit::textChanged, this, &GUI::filter);
}

void GUI::filter() {
    this->ui->listWidget->clear();
    std::string input = this->ui->lineEdit->text().toStdString();
    std::vector<Document> vector = this->repo.filterList(input);
    for (int i = 0; i < vector.size(); ++i) {
        auto *item = new QListWidgetItem;
        std::string keywords = "";
        for(auto keyword: vector[i].getKeywords()) {
            keywords += keyword + " ";
        }
        QString string (QString::fromStdString(vector[i].getName()) + " " +
                        QString::fromStdString(keywords) + " " + QString::fromStdString(vector[i].getContent()));
        item->setText(string);
        this->ui->listWidget->addItem(item);
    }
}

