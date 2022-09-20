//
// Created by bia on 04/07/2022.
//

#include "Model.h"
#include "AppError.h"

Model::Model(IdeaRepo &repo, QObject *parent) : QAbstractTableModel(parent), repo(repo) {}


int Model::rowCount(const QModelIndex &parent) const {
    return this->repo.getAll().size();
}

int Model::columnCount(const QModelIndex &parent) const {
    return 4;
}

QVariant Model::data(const QModelIndex &index, int role) const {
    if(role == Qt::DisplayRole){
        auto idea = this->repo.getAll()[index.row()];
        switch(index.column()){
            case 0: return QString::fromStdString(idea.getDescription());
            case 1: return QString::fromStdString(idea.getStatus());
            case 2: return QString::fromStdString(idea.getCreator());
            case 3: return QString::fromStdString(std::to_string(idea.getAct()));
        }
    }

    return{};
}

void Model::addIdea(const std::string& descr, int act, Writer &w) {
    this->beginResetModel();
    try {
        Idea i{descr, "proposed", w.getName(), act};
        this->repo.add(i);
        this->endResetModel();
    } catch(AppError& e){
        this->endResetModel();
        throw e;
    }
}
