#include <QApplication>
#include <QPushButton>
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repository repo;
    repo.readFromFile();
    GUI* gui = new GUI{repo, nullptr};
    gui->show();
    return QApplication::exec();
}
