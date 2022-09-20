//
// Created by bia on 02/07/2022.
//

#ifndef WAZE_DRIVERGUI_H
#define WAZE_DRIVERGUI_H

#include <QWidget>
#include "Observer.h"
#include "DriverRepo.h"
#include "ReportRepo.h"


QT_BEGIN_NAMESPACE
namespace Ui { class DriverGUI; }
QT_END_NAMESPACE

class DriverGUI : public QWidget, public Observer {
Q_OBJECT

public:
    explicit DriverGUI(Driver& d, DriverRepo& dRepo, ReportRepo& repo, QWidget *parent = nullptr);

    ~DriverGUI() override;

private:
    Ui::DriverGUI *ui;
    Driver d;
    DriverRepo& dRepo;
    ReportRepo& repo;
    void update() override;
    void populate(int interval);
    void connect();

};


#endif //WAZE_DRIVERGUI_H
