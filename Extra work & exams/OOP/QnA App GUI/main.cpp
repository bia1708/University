#include <QApplication>
#include <QPushButton>
#include "questionsgui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QuestionRepo repo;
    UserRepo urepo;
    AnswerRepo arepo;
    repo[0].setAnswers(2);
    repo[1].setAnswers(2);
    repo[2].setAnswers(1);

    for(int i = 0; i < urepo.getAll().size(); i++){
        auto* qWin = new QuestionsGUI(&urepo[i], urepo, repo, arepo);
        qWin->show();
    }

    return QApplication::exec();
}
