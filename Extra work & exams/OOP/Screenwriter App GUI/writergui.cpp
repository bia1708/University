//
// Created by bia on 04/07/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_WriterGUI.h" resolved

#include "writergui.h"
#include "ui_WriterGUI.h"
#include "AppError.h"


WriterGUI::WriterGUI(Writer& w, Model& model, QWidget *parent) :
        QWidget(parent), ui(new Ui::WriterGUI), w(w), model(model) {
    ui->setupUi(this);
    this->ui->tableView->setModel(&this->model);
    this->setWindowTitle(QString::fromStdString(w.getName()));
}

WriterGUI::~WriterGUI() {
    delete ui;
}

void WriterGUI::clickedRow(QModelIndex index) {
    try {
        this->ui->tableView->selectRow(index.row());
    } catch (AppError &e) {
        WriterGUI::printError(e);
    }
}

void WriterGUI::clickedResolve() {
    try {
        auto index = this->ui->tableView->selectionModel()->currentIndex();
        index = this->model.index(index.row(), 0);
//        auto description = this->issuesModel.data(index, Qt::DisplayRole).toString();
//        this->issuesModel.resolveIssue(description.toStdString(), this->user);
//        std::cerr << "resolve\n";
    } catch (AppError &e) {
        ProgrammerWindow::printError(e);
    }
}

void WriterGUI::clickedRemove() {

}

