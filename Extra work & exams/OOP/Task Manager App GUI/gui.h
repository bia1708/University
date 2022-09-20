//
// Created by bia on 30/06/2022.
//

#ifndef TASK_MANAGER_GUI_H
#define TASK_MANAGER_GUI_H

#include <QWidget>
#include "Observer.h"
#include "Programmer.h"
#include "ProgrammerRepository.h"
#include "TaskRepository.h"


QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QWidget, public Observer {
Q_OBJECT

public:
    explicit GUI(Programmer* p, ProgrammerRepository &prepo, TaskRepository &trepo, QWidget *parent = nullptr);

    void update() override;

    ~GUI() override;

private:
    Ui::GUI *ui;
    ProgrammerRepository &prepo;
    Programmer *p;
    TaskRepository &trepo;
    void populate();
    void connect();
};

class CustomException : public std::exception {
public:
    char * what () {
        return "Task is not open!";
    }
};

#endif //TASK_MANAGER_GUI_H
