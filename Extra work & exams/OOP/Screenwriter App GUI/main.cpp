#include <QApplication>
#include <QPushButton>
#include "writergui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    WriterGUI w;
    w.show();

    return QApplication::exec();
}
