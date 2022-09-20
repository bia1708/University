//
// Created by bia on 02/07/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DriverGUI.h" resolved

#include "drivergui.h"
#include "ui_DriverGUI.h"
#include <iostream>
#include <utility>

DriverGUI::DriverGUI(Driver& d, DriverRepo& dRepo, ReportRepo& repo, QWidget *parent) :
        QWidget(parent), ui(new Ui::DriverGUI), d(d), dRepo(dRepo), repo(repo) {
    this->repo.addObserver(this);
    ui->setupUi(this);
    this->ui->label->setText(QString::fromStdString("Location: " + std::to_string(d.getLocation().lat) + ", " +
                                     std::to_string(d.getLocation().lng) + " | Score: " + std::to_string(d.getScore()) +
                                     " | Status: " + d.getStatus()));
    if(d.getStatus() == "baby")
        this->setStyleSheet("background-color: darkCyan");
    else if(d.getStatus() == "grown-up")
        this->setStyleSheet("background-color: darkGreen");
    else this->setStyleSheet("background-color: darkMagenta");

    this->populate(10);
    this->connect();
}

DriverGUI::~DriverGUI() {
    delete ui;
}

void DriverGUI::update() {
    this->populate(10);

    this->ui->label->setText(QString::fromStdString("Location: " + std::to_string(this->d.getLocation().lat) + ", " +
                                                    std::to_string(this->d.getLocation().lng) + " | Score: " +
                                                    std::to_string(this->d.getScore()) +
                                                    " | Status: " + this->d.getStatus()));
    if (this->d.getStatus() == "baby")
        this->setStyleSheet("background-color: darkCyan");
    else if (this->d.getStatus() == "grown-up")
        this->setStyleSheet("background-color: darkGreen");
    else this->setStyleSheet("background-color: darkMagenta");

    this->ui->horizontalSlider->setTickPosition(QSlider::TicksLeft);
}

void DriverGUI::populate(int interval) {
    this->ui->listWidget->clear();

    for(int i = 0; i < this->repo.getAll().size(); i++) {
        std::string val;

        if (this->repo[i].isValidated())
            val = "true";
        else val = "false";

        if (abs(this->repo[i].getLocation().lat - d.getLocation().lat) <= interval ||
            abs(this->repo[i].getLocation().lng - d.getLocation().lng) <= interval)
            this->ui->listWidget->addItem(
                    QString::fromStdString(this->repo[i].getDescription() + " " + this->repo[i].getReporter() + " " +
                                           std::to_string(this->repo[i].getLocation().lat) + " " +
                                           std::to_string(this->repo[i].getLocation().lng) + " " + val));
    }
}

void DriverGUI::connect() {
    QObject::connect(this->ui->horizontalSlider, &QSlider::valueChanged, this, [&](){
        this->populate(this->ui->horizontalSlider->value());
    } );
    this->ui->horizontalSlider->setTickInterval(5);


    QObject::connect(this->ui->pushButton_2, &QPushButton::pressed, this, [&]() {
        std::string descr;
        descr = this->ui->lineEdit->text().toStdString();

        int lat, lng;
        lat = std::stoi(this->ui->lineEdit_2->text().toStdString());
        lng = std::stoi(this->ui->lineEdit_3->text().toStdString());

        if(!descr.empty()){
            location l{lat, lng};
            Report r{descr, this->d.getName(), l, false};
            this->repo.add(r);
            this->repo.writeToFile();
            this->repo.notify();
        }
    });

    QObject::connect(this->ui->listWidget, &QListWidget::itemSelectionChanged, this, [&](){
        int index = this->ui->listWidget->currentRow();

        if(this->repo[index].isValidated() || this->repo[index].getReporter() == this->d.getName())
            this->ui->pushButton->setDisabled(true);
        else this->ui->pushButton->setEnabled(true);
    });

    QObject::connect(this->ui->pushButton, &QPushButton::pressed, this, [&]() {
        int index = this->ui->listWidget->currentRow();

        int crt = this->repo[index].getValue();
        this->repo[index].setValue(crt + 1);

        if(this->repo[index].getValue() == 2) {
            int dindex = 0;
            for(int i = 0; i < this->dRepo.getAll().size(); i++)
                if(this->repo[index].getReporter() == this->dRepo[i].getName()) {
                    dindex = i;
                    break;
                }

            crt = this->dRepo[dindex].getScore();
            this->dRepo[dindex].setScore(crt + 1);

            if(this->dRepo[dindex].getScore() >= 10)
                this->dRepo[dindex].setStatus("grown-up");
            else if(this->dRepo[dindex].getScore() >= 15)
                this->dRepo[dindex].setStatus("knight");

            std::cout << this->dRepo[dindex].getStatus();

//            this->dRepo.writeToFile();

            this->repo[index].setValidated(true);
//            this->repo.writeToFile();
            this->repo.notify();
        }
    });
}

