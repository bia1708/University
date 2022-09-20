//
// Created by bia on 05/07/2022.
//

#ifndef QNA_QUESTIONSGUI_H
#define QNA_QUESTIONSGUI_H

#include <QWidget>
#include "Observer.h"
#include "UserRepo.h"
#include "QuestionRepo.h"
#include "AnswerRepo.h"
#include <exception>


QT_BEGIN_NAMESPACE
namespace Ui { class QuestionsGUI; }
QT_END_NAMESPACE

class QuestionsGUI : public QWidget, public Observer {
Q_OBJECT

public:
    explicit QuestionsGUI(User* u, UserRepo& urepo, QuestionRepo& repo, AnswerRepo& arepo, QWidget *parent = nullptr);

    ~QuestionsGUI() override;

    void update() override;

private:
    Ui::QuestionsGUI *ui;
    User* u;
    UserRepo& urepo;
    QuestionRepo& repo;
    AnswerRepo& arepo;
    void populate();
    void connect();
};


#endif //QNA_QUESTIONSGUI_H
