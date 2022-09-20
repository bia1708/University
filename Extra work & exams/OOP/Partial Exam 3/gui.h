//
// Created by bia on 26/05/2022.
//

#ifndef T3_BIA1708_GUI_H
#define T3_BIA1708_GUI_H

#include <QWidget>
#include "Repository.h"


QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QWidget {
Q_OBJECT

public:
    explicit GUI(Repository repo, QWidget *parent = nullptr);

    ~GUI() override;

private:
    Ui::GUI *ui;
    Repository repo;

    void writeWidget();
    void connectAll();
    void filter();
};


#endif //T3_BIA1708_GUI_H
