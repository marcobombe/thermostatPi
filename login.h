#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <thermostatmodel.h>
//#include "mainwindow.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    void setModel(ThermostatModel *newthermostatModel);
    //void setMainWindow(QWidget *mainwindow);
    static Login *getInstance();
    ~Login();

signals:
    void loggedIn();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Login *ui;
    static Login* instance;
    ThermostatModel *thermostatModel;
    bool verifyPassword();
    //QWidget *mainwindow;
};

#endif // LOGIN_H
