//
// Created by bia on 19/05/2022.
//

#include <QApplication>
#include <QHBoxLayout>
#include <QFormLayout>
#include <iostream>
#include <QMessageBox>
#include "GUI.h"

GUI::GUI(AdminService &administrator_service_,
         UserService &user_service_) :
        administrator_service(administrator_service_),
        user_service(user_service_) {
}

void GUI::init_user() {
    this->setWindowTitle("Life After School - User mode");
    auto *layout = new QHBoxLayout(this);

    // Left side
    auto *left_side = new QWidget();
    auto *vertical_left_side_layout = new QVBoxLayout(left_side);

    // Month dropdown
    this->month_dropdown = new QComboBox();
    vertical_left_side_layout->addWidget(this->month_dropdown);

    // Title
    {
        auto *current_title_widget = new QWidget();
        auto *current_title = new QHBoxLayout(current_title_widget);
        auto *title_label_text = new QLabel("Title:");
        this->title_label = new QLabel();
        current_title->addWidget(title_label_text);
        current_title->addWidget(this->title_label);
        vertical_left_side_layout->addWidget(current_title_widget);
    }

    // Description
    {
        auto *current_description_widget = new QWidget();
        auto *current_description = new QHBoxLayout(current_description_widget);
        auto *description_label_text = new QLabel("Description:");
        this->description_label = new QLabel();
        current_description->addWidget(description_label_text);
        current_description->addWidget(this->description_label);
        vertical_left_side_layout->addWidget(current_description_widget);
    }

    // Start date and time
    {
        auto *current_start_date_time_widget = new QWidget();
        auto *current_start_date_time = new QHBoxLayout(current_start_date_time_widget);
        auto *start_date_time_label_text = new QLabel("Start date and time:");
        this->start_date_time_label = new QLabel();
        current_start_date_time->addWidget(start_date_time_label_text);
        current_start_date_time->addWidget(this->start_date_time_label);
        vertical_left_side_layout->addWidget(current_start_date_time_widget);
    }

    // Participants
    {
        auto *current_participants_widget = new QWidget();
        auto *current_participants = new QHBoxLayout(current_participants_widget);
        auto *participants_label_text = new QLabel("Participants:");
        this->participants_label = new QLabel();
        current_participants->addWidget(participants_label_text);
        current_participants->addWidget(this->participants_label);
        vertical_left_side_layout->addWidget(current_participants_widget);
    }


    // URL
    {
        auto *current_url_widget = new QWidget();
        auto *current_url = new QHBoxLayout(current_url_widget);
        auto *url_label_text = new QLabel("URL:");
        this->url_label = new QLabel();
        current_url->addWidget(url_label_text);
        current_url->addWidget(this->url_label);
        vertical_left_side_layout->addWidget(current_url_widget);
    }

    // Add and next buttons
    {
        auto *add_next_buttons_widget = new QWidget();
        auto *add_next_buttons = new QHBoxLayout(add_next_buttons_widget);
        this->add_event_user = new QPushButton("&Add");
        this->next_event_user = new QPushButton("&Next");
        add_next_buttons->addWidget(this->add_event_user);
        add_next_buttons->addWidget(this->next_event_user);
        vertical_left_side_layout->addWidget(add_next_buttons_widget);
    }

    layout->addWidget(left_side);

    // Right side
    auto *right_side = new QWidget();
    auto *vertical_right_side_layout = new QVBoxLayout(right_side);

    this->events_list_user = new QListWidget();
    vertical_right_side_layout->addWidget(this->events_list_user);
    // Open and Remove buttons
    {
        auto *open_delete_buttons_widget = new QWidget();
        auto *open_delete_buttons = new QHBoxLayout(open_delete_buttons_widget);
        this->open_events_user = new QPushButton("&Open");
        this->delete_event_user = new QPushButton("&Delete");
        open_delete_buttons->addWidget(this->open_events_user);
        open_delete_buttons->addWidget(this->delete_event_user);
        vertical_right_side_layout->addWidget(open_delete_buttons_widget);
    }
    layout->addWidget(right_side);
    this->user_pager_index = -1;
    this->connect_signals_and_slots_user();
    this->populate_month_dropdown();
    this->populate_user_list();
}

void GUI::init_admin() {
    this->setWindowTitle("Life After School - Administrator mode");
    auto *layout = new QHBoxLayout(this);

    // Left side: the list of events
    auto left_side = new QWidget();
    auto left_side_layout = new QVBoxLayout(left_side);
    this->events_list_admin = new QListWidget();
    this->events_list_admin->setSelectionMode(QAbstractItemView::SingleSelection);

    this->filter_name = new QLineEdit();

    left_side_layout->addWidget(this->events_list_admin);
    left_side_layout->addWidget(this->filter_name);

    // Right side: Form for event data input + buttons for functionalities
    auto right_side = new QWidget();
    auto vertical_right_side_layout = new QVBoxLayout(right_side);

    // Event data
    auto *event_data = new QWidget();
    auto *event_form = new QFormLayout(event_data);

    // Event title
    this->title_edit = new QLineEdit();
    auto *title_label = new QLabel("&Title:");
    title_label->setBuddy(this->title_edit);

    // Event description
    this->description_edit = new QLineEdit();
    auto *description_label = new QLabel("&Description:");
    description_label->setBuddy(this->description_edit);

    // Event start date and time
    this->start_date_time_edit = new QLineEdit();
    auto *start_date_time_label = new QLabel("&Start date and time:");
    start_date_time_label->setBuddy(this->start_date_time_edit);

    // Event participants
    this->participants_edit = new QLineEdit();
    auto *participants_label = new QLabel("&Participants:");
    participants_label->setBuddy(this->participants_edit);

    // Event URL
    this->url_edit = new QLineEdit();
    auto *url_label = new QLabel("&URL:");
    url_label->setBuddy(this->url_edit);

    // Add all form fields to the form object
    event_form->addRow(title_label, this->title_edit);
    event_form->addRow(description_label, this->description_edit);
    event_form->addRow(start_date_time_label, this->start_date_time_edit);
    event_form->addRow(participants_label, this->participants_edit);
    event_form->addRow(url_label, this->url_edit);

    // Add the form to the right side of the window
    vertical_right_side_layout->addWidget(event_data);

    // Buttons for the functionalities
    auto *buttons = new QWidget();
    auto *horizontal_buttons_layout = new QHBoxLayout(buttons);

    // Add event button
    this->add_event_admin = new QPushButton("Add");
    horizontal_buttons_layout->addWidget(this->add_event_admin);

    // Update event button
    this->update_event_admin = new QPushButton("Update");
    horizontal_buttons_layout->addWidget(this->update_event_admin);

    // Delete event button
    this->delete_event_admin = new QPushButton("Delete");
    horizontal_buttons_layout->addWidget(this->delete_event_admin);

    // Add the buttons to the right side of the window
    vertical_right_side_layout->addWidget(buttons);

    // Add the left and right side of the window to the main window
    layout->addWidget(left_side);
    layout->addWidget(right_side);

    QLinearGradient colorGradient = QLinearGradient(0, 0, QWidget::width(), QWidget::height());
    colorGradient.setSpread(QGradient::RepeatSpread);
    colorGradient.setColorAt(0, QColor(236, 255, 230));
    colorGradient.setColorAt(1, QColor(255, 204, 255,255));
    QBrush colorBrush = QBrush(colorGradient);

    QPalette qPalette;
    qPalette.setBrush(QPalette::Base, colorBrush);
    this->events_list_admin->setPalette(qPalette);

    this->connect_signals_and_slots_admin();
    this->populate_events_list();
}

void GUI::connect_signals_and_slots_admin() {
    QObject::connect(this, &GUI::events_updated_signal_admin,
                     this, &GUI::populate_events_list);
    QObject::connect(this->add_event_admin, &QPushButton::clicked, this,
                     &GUI::add_event_admin_handler);
    QObject::connect(this->update_event_admin, &QPushButton::clicked, this,
                     &GUI::update_event_admin_handler);
    QObject::connect(this->delete_event_admin, &QPushButton::clicked, this,
                     &GUI::delete_event_admin_handler);
    QObject::connect(this->events_list_admin, &QListWidget::currentRowChanged, this,
                     &GUI::load_selected_event_admin_handler);
    QObject::connect(this->filter_name, &QLineEdit::textChanged, this,
                     &GUI::filter_by_name);
}

void GUI::populate_events_list() {
    try {
        this->events_list_admin->blockSignals(true);
        if (this->events_list_admin->count() > 0) {
            this->events_list_admin->clear();
        }

        const auto &events = this->administrator_service.adminGetEventList();
        for (auto &event: events) {
            auto event_string = QString::fromStdString(event.getOutputFormat());
            auto *list_item = new QListWidgetItem(event_string);
            this->events_list_admin->addItem(list_item);
        }

        if (this->events_list_admin->count() > 0) {
            this->events_list_admin->setCurrentRow(0);
        }
        this->events_list_admin->blockSignals(false);
    } catch (AppError &e) {
        this->display_error(e);
    }
}

void GUI::filter_by_name(const QString &qs) {
    try {
        this->events_list_admin->blockSignals(true);
        std::string s = qs.toStdString(); // this->filter_name->text().toStdString();
        auto events = this->administrator_service.filter(s);
        this->events_list_admin->clear();
        for (auto &event: events) {
            auto event_string = QString::fromStdString(event.getOutputFormat());
            auto *list_item = new QListWidgetItem(event_string);
            this->events_list_admin->addItem(list_item);
        }

        if (this->events_list_admin->count() > 0) {
            this->events_list_admin->setCurrentRow(0);
        }
        this->events_list_admin->blockSignals(false);
    } catch (AppError &e) {
        this->display_error(e);
    }
}

void GUI::add_event_admin_handler() {
    try {
        Date d = {};
        std::vector<std::string> tokens = explode(this->get_start_date_time_admin(), "-");
        d.year = stoi(tokens[0].substr(1));
        d.month = stoi(tokens[1].substr(1));
        d.day = stoi(tokens[2].substr(1));
        d.hour = stoi(tokens[3].substr(1));
        d.minute = stoi(tokens[4].substr(1));
        this->administrator_service.adminAddEvent(
                this->get_title_admin(),
                this->get_description_admin(),
                d,
                this->get_participants_admin(),
                this->get_url_admin()
        );
        emit GUI::events_updated_signal_admin();
    } catch (AppError &e) {
        this->display_error(e);
    } catch (const std::exception &e){
        QMessageBox message_box(this);
        QMessageBox::critical(0, "Error", e.what());
        message_box.open();
    }
}

void GUI::update_event_admin_handler() {
    try {
        Date d = {};
        std::vector<std::string> tokens = explode(this->get_start_date_time_admin(), "-");
        d.year = stoi(tokens[0].substr(1));
        d.month = stoi(tokens[1].substr(1));
        d.day = stoi(tokens[2].substr(1));
        d.hour = stoi(tokens[3].substr(1));
        d.minute = stoi(tokens[4].substr(1));
        this->administrator_service.adminUpdateEvent(
                this->get_title_admin(),
                this->get_description_admin(),
                d,
                this->get_participants_admin(),
                this->get_url_admin()
        );
        emit GUI::events_updated_signal_admin();
    } catch (AppError &e) {
        this->display_error(e);
    } catch (const std::exception &e){
        QMessageBox message_box(this);
        QMessageBox::critical(0, "Error", e.what());
        message_box.open();
    }
}

void GUI::delete_event_admin_handler() {
    try {
        this->administrator_service.adminDeleteEvent(this->get_title_admin());
        emit GUI::events_updated_signal_admin();
    } catch (AppError &e) {
        this->display_error(e);
    }
}

void GUI::load_selected_event_admin_handler() {
    try {
        auto current = this->events_list_admin->currentItem();
        if (current == nullptr) {
            return;
        }
        std::string event_string = current->text().toStdString();
        Event event(event_string);
        this->title_edit->setText(QString::fromStdString(event.getTitle()));
        this->description_edit->setText(QString::fromStdString(event.getTitle()));
        this->start_date_time_edit->setText(QString::fromStdString(getStringFromDate(event.getDate())));
        this->participants_edit->setText(
                QString::fromStdString(std::to_string(event.getNumberOfPeople()))
        );
        this->url_edit->setText(QString::fromStdString(event.getLink()));
    } catch (AppError &e) {
        this->display_error(e);
    }
}

std::string GUI::get_title_admin() const {
    return this->title_edit->text().toStdString();
}

std::string GUI::get_description_admin() const {
    return this->description_edit->text().toStdString();
}

std::string GUI::get_start_date_time_admin() const {
    return this->start_date_time_edit->text().toStdString();
}

int GUI::get_participants_admin() const {
    return std::stoi(this->participants_edit->text().toStdString());
}

std::string GUI::get_url_admin() const {
    return this->url_edit->text().toStdString();
}

void GUI::connect_signals_and_slots_user() {
    QObject::connect(this, &GUI::events_updated_signal_user, this, &GUI::populate_user_list);
    QObject::connect(this->add_event_user, &QPushButton::clicked, this, &GUI::add_event_user_handler);
    QObject::connect(this, &GUI::user_pager_index_updated_signal, this,
                     &GUI::load_current_event_user_handler);
    QObject::connect(this->next_event_user, &QPushButton::clicked, this,
                     &GUI::next_event_user_handler);
    QObject::connect(this->month_dropdown, &QComboBox::currentTextChanged, this,
                     &GUI::month_changed_user_handler);
    QObject::connect(this->delete_event_user, &QPushButton::clicked, this,
                     &GUI::delete_event_user_handler);
    QObject::connect(this->open_events_user, &QPushButton::clicked, this,
                     &GUI::open_user_list_handler);
}

void GUI::add_event_user_handler() {
    try {
        if (this->month_dropdown->currentText().isEmpty()) {
            return;
        }
        Event event = this->user_service.getCurrentEvent();
        this->user_service.addInterest(event);
        emit GUI::events_updated_signal_user();
    } catch (AppError &e) {
        this->display_error(e);
    } catch (const std::exception &e){
        QMessageBox message_box(this);
        QMessageBox::critical(0, "Error", e.what());
        message_box.open();
    }
}

void GUI::populate_user_list() {
    try {
        this->events_list_user->blockSignals(true);
        if (this->events_list_user->count() > 0) {
            this->events_list_user->clear();
        }

        const auto &events = this->user_service.getInterests();
        for (auto &event: events) {
            auto event_string = QString::fromStdString(event.getOutputFormat());
            auto *list_item = new QListWidgetItem(event_string);
            this->events_list_user->addItem(list_item);
        }

        if (this->events_list_user->count() > 0) {
            this->events_list_user->setCurrentRow(0);
        }
        this->events_list_user->blockSignals(false);
    } catch (AppError &e) {
        this->display_error(e);
    }
}

void GUI::populate_month_dropdown() {
    try {
        if (this->month_dropdown->count() > 0) {
            this->month_dropdown->clear();
        }

        auto months = this->user_service.getAllMonths();
        for (auto &month: months) {
            auto option = QString::fromStdString(std::to_string(month));
            this->month_dropdown->addItem(option);
        }

        if (this->month_dropdown->count() > 0) {
            this->month_dropdown->setCurrentIndex(0);
            this->user_pager_index = 0;
            emit GUI::user_pager_index_updated_signal();
        }
    } catch (AppError &e) {
        this->display_error(e);
    }
}

void GUI::load_current_event_user_handler() {
    try {
        int month = this->month_dropdown->currentText().toInt();
//        this->user_service.filterByMonth(month);
        Event event = this->user_service.getEventsByMonth()[this->user_pager_index];

        this->title_label->setText(QString::fromStdString(event.getTitle()));
        this->description_label->setText(QString::fromStdString(event.getDescription()));
        this->start_date_time_label->setText(
                QString::fromStdString(getStringFromDate(event.getDate())));
        this->participants_label->setText(
                QString::fromStdString(std::to_string(event.getNumberOfPeople()))
        );
        this->url_label->setText(QString::fromStdString(event.getLink()));
    } catch (AppError &e) {
        this->display_error(e);
    }
}

void GUI::display_error(AppError &e) {
    QMessageBox message_box(this);
    QMessageBox::critical(0, "Error", e.what());
    message_box.open();
}

void GUI::next_event_user_handler() {
    try {
        ++this->user_pager_index;
        int month = this->month_dropdown->currentText().toInt() - 1;
//        this->user_service.filterByMonth(month);
        this->user_service.goToNextEvent();
        if (this->user_pager_index ==
            (int) this->user_service.getEventsByMonth().size()) {
            this->user_pager_index = 0;
        }
        emit GUI::user_pager_index_updated_signal();
    } catch (AppError &e) {
        this->display_error(e);
    }
}

void GUI::month_changed_user_handler() {
    this->user_pager_index = 0;
    int month = this->month_dropdown->currentText().toInt();
    this->user_service.filterByMonth(month);
    emit GUI::user_pager_index_updated_signal();
}

void GUI::delete_event_user_handler() {
    try {
        auto current = this->events_list_user->currentItem();
        if (current == nullptr) {
            return;
        }
        std::string event_string = current->text().toStdString();
        Event event(event_string);
        this->user_service.deleteInterest(event.getTitle());
        emit GUI::events_updated_signal_user();
    } catch (AppError &e) {
        this->display_error(e);
    }
}

void GUI::open_user_list_handler() {
    try {
        this->user_service.openInterestListInApp();
    } catch (AppError &e) {
        this->display_error(e);
    }
}
