//
// Created by bia on 06/07/2022.
//

#ifndef E_RETAKE_BIA1708_USERGUI_H
#define E_RETAKE_BIA1708_USERGUI_H

#include <QWidget>
#include "UserRepo.h"
#include "Topics.h"
#include "PostRepo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UserGUI; }
QT_END_NAMESPACE

class UserGUI : public QWidget, public Observer{
Q_OBJECT

public:
    explicit UserGUI(User* u, UserRepo& urepo, TopicRepo& trepo, PostRepo& repo, QWidget *parent = nullptr);

    ~UserGUI() override;

private:
    Ui::UserGUI *ui;
    User* u;
    std::string uname;
    UserRepo& urepo;
    TopicRepo& trepo;
    PostRepo& repo;

    void populate();
    void connect();
    void update() override;
};


#endif //E_RETAKE_BIA1708_USERGUI_H
