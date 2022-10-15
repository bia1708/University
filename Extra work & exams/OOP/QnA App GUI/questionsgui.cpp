//
// Created by bia on 05/07/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QuestionsGUI.h" resolved

#include "questionsgui.h"
#include "ui_QuestionsGUI.h"
#include <QMessageBox>
#include <iostream>

QuestionsGUI::QuestionsGUI(User* u, UserRepo& urepo, QuestionRepo& repo, AnswerRepo& arepo, QWidget *parent) :
        QWidget(parent), ui(new Ui::QuestionsGUI), u(u), urepo(urepo), repo(repo), arepo(arepo) {
    ui->setupUi(this);
    this->repo.addObserver(this);
    this->setWindowTitle(QString::fromStdString(u->getName()));

    this->populate();
    this->connect();
}

QuestionsGUI::~QuestionsGUI() {
    delete ui;
}

void QuestionsGUI::populate() {
    this->ui->listWidget->clear();
    this->ui->spinBox->clear();

    this->repo.sort();
    for(auto q : this->repo.getAll()) {
        auto *i = new QListWidgetItem(QString::fromStdString(std::to_string(q.getId()) + " | " + q.getText()
                                                             + " | Posted by: " + q.getCreator() + " | Answers : " +
                                                             std::to_string(q.getAnswers())));
        if (q.getCreator() == u->getName()) {
            i->setBackground(QBrush(QColor(212,175,55)));
        }
        this->ui->listWidget->addItem(i);
    }
}

void QuestionsGUI::connect() {
    QObject::connect(this->ui->pushButton, &QPushButton::pressed, this, [&]() {
        try {
            std::string text = this->ui->lineEdit->text().toStdString();
            if(text.empty())
                throw std::exception();
            Question q{(int) this->repo.getAll().size() + 1, text, u->getName()};
            this->repo.add(q);
//       this->repo.writeToFile();
        } catch (std::exception& e){
            auto* popup = new QMessageBox;
            popup->setText("Description can't be emtpy!");
            popup->show();
        }
    });

    QObject::connect(this->ui->listWidget, &QListWidget::itemSelectionChanged, this, [&]() {
        std::string line = this->ui->listWidget->item(this->ui->listWidget->currentRow())->text().toStdString();
        int id = (int)line[0] - 48;

        if(this->repo[id].getCreator() == u->getName())
            this->ui->pushButton_2->setDisabled(true);
        else this->ui->pushButton_2->setEnabled(true);


        this->ui->listWidget_2->clear();
        for(auto a: this->arepo.getById(id)) {
            auto *i = new QListWidgetItem(QString::fromStdString(
                    std::to_string(a.getId()) + " | " + a.getText() + " | Posted by: " +
                    a.getAName() + " | Upvotes: " + std::to_string(a.getVotes())));
            if (a.getAName() == u->getName()) {
                i->setBackground(QBrush(QColor(126,176,76)));
            }
            this->ui->listWidget_2->addItem(i);
        }
    });

    QObject::connect(this->ui->pushButton_2, &QPushButton::pressed, this, [&]() {
        try {
            std::string text = this->ui->lineEdit_2->text().toStdString();
            if(text.empty())
                throw std::exception();

            Answer a{(int) this->repo.getAll().size() + 1, this->ui->listWidget->currentRow() + 1, u->getName(), text, 0};
            this->arepo.add(a);
            this->repo[this->ui->listWidget->currentRow()].setAnswers(this->repo[this->ui->listWidget->currentRow()].getAnswers() + 1);
            this->repo.notify();
//       this->arepo.writeToFile();
        } catch (std::exception& e){
            auto* popup = new QMessageBox;
            popup->setText("Description can't be emtpy!");
            popup->show();
        }
    });

    QObject::connect(this->ui->listWidget_2, &QListWidget::itemSelectionChanged, this, [&]() {
        this->ui->spinBox->clear();
        std::string line = this->ui->listWidget_2->item(this->ui->listWidget_2->currentRow())->text().toStdString();
        int aId = (int)line[0] - 48;
        this->ui->spinBox->setValue(this->arepo[aId - 1].getVotes());
    });

    QObject::connect(this->ui->spinBox, &QSpinBox::valueChanged, this, [&]() {
        std::string line = this->ui->listWidget_2->item(this->ui->listWidget_2->currentRow())->text().toStdString();
        int aId = (int)line[0] - 48;
        this->arepo[aId - 1].setVotes(this->ui->spinBox->value());

        this->repo.notify();
    });
}

void QuestionsGUI::update() {
    this->populate();
}

