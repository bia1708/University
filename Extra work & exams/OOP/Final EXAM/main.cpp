#include <QApplication>
#include <QPushButton>
#include "usergui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    UserRepo urepo;
    TopicRepo trepo;
    PostRepo repo;

    for(auto u : urepo.getAll()){
        auto* uWin = new UserGUI(&u, urepo, trepo, repo);
        uWin->setWindowTitle(QString::fromStdString(u.getName()));
        uWin->show();
    }

    return QApplication::exec();
}
