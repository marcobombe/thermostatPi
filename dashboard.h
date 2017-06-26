#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>
#include <thermostatmodel.h>

namespace Ui {
class Dashboard;
}

class Dashboard : public QDialog
{
    Q_OBJECT

public:
    explicit Dashboard (QWidget *parent = 0);
    void setModel(ThermostatModel *newthermostatModel);
    void updateTemperatureDisplay(float temperature);
    static Dashboard *getInstance();
    ~Dashboard();

signals:
    void loggedIn();

private slots:
    void on_pbLogoff_clicked();
    void on_pbQuit_clicked();

    void on_pbPlus_clicked();

    void on_pbMinus_clicked();

public slots:
    void setValue(int value);

private:
    Ui::Dashboard *ui;
    static Dashboard* instance;
    ThermostatModel *thermostatModel;
};

#endif // DASHBOARD_H
