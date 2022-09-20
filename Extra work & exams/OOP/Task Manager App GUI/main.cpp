#include <QApplication>
#include <QPushButton>
#include "gui.h"
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    TaskRepository trepo;
    ProgrammerRepository prepo;

    for(auto prog : prepo.getAll()) {
        auto* gui = new GUI(&prog, prepo, trepo);
        gui->setWindowTitle(prog.getName().c_str());
        gui->show();
    }

    return QApplication::exec();
}
