//
// Created by bia on 19/05/2022.
//

#ifndef A11_12_BIA1708_GUI_H
#define A11_12_BIA1708_GUI_H


#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include "AdministratorService.h"
#include "UserService.h"
#include "exceptions.h"
#include <stdlib.h>

class GUI : public QWidget {
Q_OBJECT
    AdminService &administrator_service;
    UserService &user_service;
    // admin
    QListWidget *events_list_admin{};
    QLineEdit *title_edit{};
    QLineEdit *description_edit{};
    QLineEdit *start_date_time_edit{};
    QLineEdit *participants_edit{};
    QLineEdit *url_edit{};
    QLineEdit *filter_name{};
    QPushButton *add_event_admin{};
    QPushButton *update_event_admin{};
    QPushButton *delete_event_admin{};

    // user
    int user_pager_index{};
    QComboBox *month_dropdown{};
    QLabel *title_label{};
    QLabel *description_label{};
    QLabel *start_date_time_label{};
    QLabel *participants_label{};
    QLabel *url_label{};
    QPushButton *add_event_user{};
    QPushButton *next_event_user{};
    QListWidget *events_list_user{};
    QPushButton *open_events_user{};
    QPushButton *delete_event_user{};

    void connect_signals_and_slots_admin();
    void connect_signals_and_slots_user();
    void populate_events_list();
    void filter_by_name(const QString &);
    void add_event_admin_handler();
    void update_event_admin_handler();
    void delete_event_admin_handler();
    void load_selected_event_admin_handler();
    std::string get_title_admin() const;
    std::string get_description_admin() const;
    std::string get_start_date_time_admin() const;
    int get_participants_admin() const;
    std::string get_url_admin() const;
    //user
    void populate_user_list();
    void populate_month_dropdown();
    void add_event_user_handler();
    void load_current_event_user_handler();
    void next_event_user_handler();
    void month_changed_user_handler();
    void delete_event_user_handler();
    void open_user_list_handler();

    void display_error(AppError &e);
signals:
    void events_updated_signal_admin();
    void events_updated_signal_user();
    void user_pager_index_updated_signal();

public:
    explicit GUI(AdminService &administrator_service,
                 UserService &user_service);
    void init_admin();
    void init_user();

};


#endif //A11_12_BIA1708_GUI_H
