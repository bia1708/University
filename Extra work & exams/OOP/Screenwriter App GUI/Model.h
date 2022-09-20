//
// Created by bia on 04/07/2022.
//

#ifndef SCREENWRITER_MODEL_H
#define SCREENWRITER_MODEL_H


#include <QAbstractTableModel>
#include "IdeaRepo.h"
#include "Writer.h"

class Model : public QAbstractTableModel {
private:
    IdeaRepo& repo;
public:
    explicit Model(IdeaRepo &repo, QObject *parent);

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    void addIdea(const std::string& descr, int act, Writer& w);
};


#endif //SCREENWRITER_MODEL_H
