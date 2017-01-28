#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>
#include <thermostatmodel.h>
//#include "mainwindow.h"

namespace Ui {
class Dashboard;
}

class Dashboard : public QDialog
{
    Q_OBJECT

public:
    explicit Dashboard (QWidget *parent = 0);
    void setModel(ThermostatModel *newthermostatModel);
    static Dashboard *getInstance();
    ~Dashboard();

signals:
    void loggedIn();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dashboard *ui;
    static Dashboard* instance;
    ThermostatModel *thermostatModel;
};

#endif // DASHBOARD_H
