//
// Created by bia on 04/07/2022.
//

#ifndef SCREENWRITER_WRITERGUI_H
#define SCREENWRITER_WRITERGUI_H

#include <QWidget>
#include "WriterRepo.h"
#include "Model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WriterGUI; }
QT_END_NAMESPACE

class WriterGUI : public QWidget {
Q_OBJECT

public:
    explicit WriterGUI(Writer& w, Model& model, QWidget *parent = nullptr);

    ~WriterGUI() override;

private:
    Ui::WriterGUI *ui;
    Writer& w;
    Model& model;

public slots:
    void clickedRow(QModelIndex index);
    void clickedResolve();
    void clickedRemove();


};


#endif //SCREENWRITER_WRITERGUI_H
