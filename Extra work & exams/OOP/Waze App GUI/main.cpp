#include <QApplication>
#include <QPushButton>
#include "drivergui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    DriverRepo dRepo;
    ReportRepo repo;

    for(auto d : dRepo.getAll()){
        auto dWin = new DriverGUI(d, dRepo, repo);
        dWin->setWindowTitle(QString::fromStdString(d.getName()));
        dWin->show();
    }

    return QApplication::exec();
}

// TODO: make input files, connect buttons.